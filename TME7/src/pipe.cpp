#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>

//g++ -o pipe pipe.cpp
//./pipe /bin/cat pipe.cpp \| /usr/bin/wc -l

void myexec(int argc2,char* argv2[]){
execv(argv2[0],argv2);
}

int main(int argc,char* argv[]){
    //diviser 分割|的命令行参数
    char* parametre1[argc];
    char* parametre2[argc];
    //initialisation  初始化
    memset(parametre1,0,argc*sizeof(char*));
    memset(parametre2,0,argc*sizeof(char*));
    int argument = 1;
    for(;argument<argc;argument++){
        //!strcmp if equal,retourn 0 ->false. !false -> true
        //分割参数行
        if(!strcmp(argv[argument],"|")){
            argument++;
            break;
        }
        else{
            parametre1[argument-1] = parametre2[argument];
        }
    }
    //les parametre after |
    for (int i=0; argument < argc ; i++,argument++) {
         parametre2[i] = argv[argument];
         }

    int tube[2];
    pid_t pid;
    //fork et tube
    pipe(tube);
    pid = fork();
    //fork->fils
    if(pid == 0){
        //第一个 fils，将标准输出重定向到写端
        //first fils,standout normal -> tube write
     dup2(tube[1],STDOUT_FILENO);
//我们不再需要管道的两个端
     close(tube[0]);
     close(tube[1]);


    }
    pid = fork();
    //2ieme fils
    if(pid == 0){
        dup2(tube[0],STDIN_FILENO);
        close(tube[0]);
        close(tube[1]);

    }
    close(tube[0]);
    close(tube[1]);
    //fils ferme
    wait(0);
    wait(0);


    return 0;
}