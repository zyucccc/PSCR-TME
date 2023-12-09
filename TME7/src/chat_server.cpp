#include "chat_common.h"
#include <iostream>
#include <unistd.h>

int flag = 0;

struct user{
    char* name;
    struct myshm * shm;
}*users[MAX_USERS];
//？il manque la partie signal
using namespace std;
int main(int argc, char *argv[]){
    if (argc < 2) {
        perror("error parametre");
        return -1;
    }
    int fd;
    //point 指针 指向内存空间
    struct myshm *my_shm;
    //共享内存名字来自命令行
char * memoire_name = argv[1];
    void * addr;
    //打开共享内存块
    fd = shm_open(memoire_name,O_CREAT|O_EXCL|O_RDWR,0666);
    //验证
     if (fd < 0) {
         perror("shm_open");
         return 1;
         }
     //改变内存区域大小
    if(ftruncate(fd, sizeof(struct myshm)) == -1) {
         perror("ftruncate my_shm");
         exit(EXIT_FAILURE);
         }
    //映射内存
    //在共享内存中定义变量
    my_shm = (struct myshm*) mmap(nullptr, sizeof(struct myshm), PROT_READ | PROT_WRITE, MAP_SHARED , fd, 0);
    if (my_shm == MAP_FAILED) {
         perror("mmap erreur");
         exit(1);
         }
    //initialisation
    my_shm->read = 0;
    my_shm->write = 0;
    my_shm->nb = 0;
//    ?? deprecated in osx?
    sem_init(&(my_shm->sem), 1, 1);
    //initialisation tableau
    for(int i=0; i<MAX_USERS; i++){
         users[i] = NULL;
         }
    while(!flag){
        //等待信号量
        sem_wait(&(my_shm->sem));
        //如果 read 指针和 write 指针不在一个地方，证明有一个消息没有读
        if(my_shm->read != my_shm->write || my_shm->nb == MAX_MESS){
            //存储 message
            struct message message = my_shm->messages[my_shm->read];
            switch (message.type) {
                case 0:{//connexion
//                    当客户端想要连接到服务器时，它会在共享内存中放置一条类型为“连接”的消息（type 字段设置为特定值，通常是 0）。
//                    服务器检测到这种类型的消息后，会执行相应的连接逻辑，比如在内部数据结构中记录新客户端的信息。
                    char *username;
                    int user_shm;
                    int i = 0;
                    //找到第一个 tableau 里的空位
                    while(i< MAX_USERS && users[i] != NULL) i++;
                    if(i == MAX_USERS){
                        perror("erreur tableau");
                        exit(1);
                    }
                    //分配内存
                    users[i] = (struct user*)malloc(sizeof(struct user));
                    //ajoute user
                    users[i]->name = (char *)malloc((strlen(message.content) + 1) * sizeof(char));
                    strcpy(users[i]->name, message.content);
                    users[i]->name[strlen(message.content)] = '\0';
                    printf("Connexion de %s\n", users[i]->name);
                    //加入用户的 id
                    username = message.content;
                    user_shm = shm_open(username,O_CREAT|O_RDWR,0666);
                    users[i]->shm = (struct myshm*) mmap(nullptr, sizeof(struct myshm), PROT_READ | PROT_WRITE, MAP_SHARED , user_shm, 0);

                  break;
                }
                case 1:{//diffusion
                    int time;
//                    当客户端发送消息时，它会在共享内存中放置一条类型为“消息广播”的消息（type 字段设置为另一个特定值，通常是 1）。
//                    服务器读取到这种类型的消息后，会将消息内容广播给所有连接的客户端或执行其他相关逻辑
                   for(int i = 0;i< MAX_USERS;i++){
                       //parcourir tous les users
                       if(users[i] != NULL){
                           struct message msg;
                           struct myshm * shm = users[i]->shm;
                           time ++;
                           //复制消息 用来发送
                           msg.type = 1;
                           strcpy(msg.content,message.content);
                           sem_wait(&(shm->sem));//wait semaphore for writing
                           while (shm->nb == MAX_MESS) {
                               // 如果共享内存中的消息已满，等待
                               sem_post(&(shm->sem));  // 释放信号量
                               sleep(1);  // 等待一秒
                               sem_wait(&(shm->sem));  // 再次尝试获取信号量
                           }
                           //写入消息 writing message
                           shm->messages[shm->write] = msg;  // 在共享内存中写入消息
                           shm->write = (shm->write + 1) % MAX_MESS;  // 更新写指针
                           shm->nb++;  // 增加消息计数

                           sem_post(&(shm->sem));//释放信号量
                       }
                   }

                }
                case 2 :{//deconnexion
                    int i =0;
//                    当客户端想要断开连接时，它会在共享内存中放置一条类型为“断开连接”的消息（type 字段设置为又一个特定值，通常是 2）。
//                    服务器在识别到这种类型的消息后，会从其内部数据结构中移除相应的客户端信息，并执行清理工作
                    while(i<MAX_USERS && (users[i] == NULL || strcmp(users[i]->name, message.content)!= 0)) i++;
                    //寻找 username 符合 message 的用户
                     if(i == MAX_USERS){
                         perror("Something went wrong! L’user n’existe pas!");
                         exit(EXIT_FAILURE);
                         }
//                   free resource
                    free(users[i]->name);
                     munmap(users[i]->shm, sizeof(struct myshm));
                     free(users[i]);
                     users[i] = NULL;
                     break;


                }
            }
        }


    }
    //close
    sem_close(&(my_shm->sem));
    munmap(my_shm, sizeof(struct myshm));
    shm_unlink(memoire_name);
    return 0;
}