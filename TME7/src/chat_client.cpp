#include "chat_common.h"
#include <iostream>
#include <unistd.h>
int flag =0;
struct myshm *shm_receive, *shm_send;
//handle thread
void *writer(void* arg){
     while(!flag){
         struct message msg;
           msg.type = 1;//发送消息
         fgets(msg.content, TAILLE_MESS, stdin);// 从标准输入读取消息内容 从 stdin 读取储存到 msg.content
        if(flag) break;
        //多个客户端 所以等待发送消息
        sem_wait(&(shm_send->sem));
        //达到最大消息 然后 bloquer ，跟 server 一样
        while(shm_send->nb == MAX_MESS){
             sem_post(&(shm_send->sem));
             sleep(1);
             sem_wait(&(shm_send->sem));
             }
//        填入消息
         shm_send->messages[shm_send->write] = msg;
        //指针向前进
         shm_send->write = (shm_send->write + 1) % MAX_MESS;
         //添加次数
         shm_send->nb++;
         sem_post(&(shm_send->sem));
         }
     pthread_exit(NULL);
     return NULL;
     }

void *reader(void* arg){
    while(!flag){
        sem_wait(&(shm_receive->sem)); // 等待信号量以获取对共享内存的访问权限

        // 检查是否有至少一条消息写入共享内存 跟 server 一样，如果 read 指针跟 write 指针不一样，证明有消息没读
        if(shm_receive->read != shm_receive->write || shm_receive->nb == MAX_MESS){
            // 从共享内存中读取当前读取位置的消息
            struct message message = shm_receive->messages[shm_receive->read];
            // 更新read指针，如果达到数组末尾则循环回到开始
            shm_receive->read = (shm_receive->read + 1) % MAX_MESS;
            //nb 消息计数
            shm_receive->nb--; // 减少共享内存中的消息计数
        }
        sem_post(&(shm_receive->sem)); // 释放信号量，允许其他进程或线程访问共享内存
    }
    pthread_exit(NULL); // 线程退出
    return NULL;
}



using namespace std;
//shm_client（客户端共享内存）:
//在客户端程序中，shm_client 用于接收来自服务器的消息。客户端只有一个读取线程（reader 函数）访问这个共享内存区域，所以对 shm_client 的访问相对来说是单线程的。

//shm_pere（服务器共享内存）:
//shm_pere 是客户端用来向服务器发送消息的共享内存区域。客户端的写入线程（writer 函数）会向这个内存区域写入数据。
//由于服务器可能同时处理来自多个客户端的写入请求，因此对 shm_pere 的访问需要更严格的同步机制。这就是为什么在写入操作中显著地使用了信号量机制。
int main(int argc, char *argv[]){
    if (argc < 3) {
        perror("error parametre");
        return -1;
    }
    //thread
    pthread_t threads[2];
    struct message msg;

    //2 memoire partage 1 pour receive message 1 pour send
    char * name_receive = argv[1];
    char * name_send = argv[2];
    int id_shm_receive = shm_open(name_receive, O_RDWR | O_CREAT, 0666);
    if (id_shm_receive < 0) {
        perror("shm_open");
        return 1;
    }
    //shm_open 创建或打开一个POSIX共享内存对象,返回一个文件描述符
    int id_shm_send = shm_open(name_send, O_RDWR | O_CREAT, 0666);
    if (id_shm_send < 0) {
        perror("shm_open");
        return 1;
    }
    ftruncate(id_shm_receive, sizeof(struct myshm));
    //receive == client，要读取   send == server，要发送，客户端不需要在对 server 的共享内存进行操作
//    客户端初始客户端的 服务端初始服务端的
//    ftruncate(id_shm_send, sizeof(struct myshm));
    //映射内存
    //shm_receive 指针 指向内存空间
//    struct myshm *shm_receive, *shm_send;
    shm_receive = (struct myshm*) mmap(nullptr, sizeof(struct myshm), PROT_READ | PROT_WRITE, MAP_SHARED , id_shm_receive, 0);
    shm_send = (struct myshm*) mmap(nullptr, sizeof(struct myshm), PROT_READ | PROT_WRITE, MAP_SHARED , id_shm_send, 0);
//    initialisation
    shm_receive->read = 0;
    shm_receive->write = 0;
    shm_receive->nb = 0;
//    ?? deprecated in osx?
    sem_init(&(shm_receive->sem), 1, 1);


    //发送消息给服务器==shm_send, envoyer message à server
    msg.type = 0;
    //链接 名字 connexion name
    strcpy(msg.content, argv[1]);
    //发送前检查 semaphore
    sem_wait(&(shm_send->sem));
    shm_send->messages[shm_send->write] = msg;
    shm_send->write = (shm_send->write + 1) % MAX_MESS;
    shm_send->nb++;
    sem_post(&(shm_send->sem));
    //std::thread 提供了更现代、更易于使用的线程管理方式，而 pthread_create 提供了更多的控制和灵活性，但使用起来更复杂。
    //thread
    pthread_create(&(threads[0]), NULL, reader, NULL);
    pthread_create(&(threads[1]), NULL, writer, NULL);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    //解除链接
//    write 指针：
//    write 指针用于指示下一个可写入消息的位置。当一个新消息需要被添加到队列或共享内存时，它被写入 write 指针当前指向的位置。
//    每当一个新消息被写入，write 指针随后会更新（通常向前移动一位）。这确保了每个新消息都被写入一个空闲的位置，而不会覆盖已有的消息。
//    read 指针：
//    read 指针用于指示下一个可读取消息的位置。当从队列或共享内存中读取消息时，从 read 指针当前指向的位置读取。
//    每当一个消息被读取，read 指针会更新（通常向前移动一位），以便下次读取新的消息。
    msg.type = 2;
    sem_wait(&(shm_send->sem));
    shm_send->messages[shm_send->write] = msg;
    shm_send->write = (shm_send->write + 1) % MAX_MESS;
    shm_send->nb++;
    sem_post(&(shm_send->sem));
    //close,liberer les ressources
    sem_close(&(shm_receive->sem));
    munmap(shm_receive, sizeof(struct myshm));
    shm_unlink(name_receive);

    return 0;

}