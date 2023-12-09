#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>
#include "rsleep.h"
using namespace std;
//combat
int PV = 3;
void handler (int sig){
    if(sig == SIGUSR1){
        PV--;
        printf("Attaque recue par %d;PV restants %d \n",getpid(),PV);
        if(PV == 0){
            printf("Plus de vie pour %d;mort du processus \n",getpid());
            exit(1);
        }
    }
}
void attaque(pid_t adversaire){
    signal(SIGUSR1,handler);
    if(kill(adversaire,SIGUSR1)<0){
        printf("Detection de mort de l'adversaire de  %d; \n",adversaire);
        exit(0);
    }
    randsleep();
}
void defense(){
    signal(SIGUSR1,SIG_IGN);
    randsleep();
}
void combat(pid_t adversaire){
    while(1){
        defense();
        attaque(adversaire);
    }
}

//void randsleep() {
//    // 生成一个随机数
//    int r = rand();
//
//    // 计算一个0到1之间的随机比例
//    double ratio = (double)r / (double) RAND_MAX;
//
//    // 定义一个timespec结构体来存储我们想要休眠的时间
//    struct timespec tosleep;
//
//    // 设置秒数为0，因为我们只考虑纳秒
//    tosleep.tv_sec =0;
//
//    // 300 million nanoseconds = 0.3 seconds，加上0到0.7秒的随机值，使总的休眠时间在0.3到1秒之间
//    tosleep.tv_nsec = 300000000 + ratio*7000000000;
//
//    // 定义另一个timespec结构体来存储剩余的休眠时间，如果nanosleep被中断
//    struct timespec remain;
//
//    // 使用nanosleep函数进行休眠，如果休眠被中断，比如由于信号，nanosleep会返回非0值，并设置remain为剩余的休眠时间
//    while ( nanosleep(&tosleep, &remain) != 0 ) {
//        // 如果nanosleep被中断，将剩余的休眠时间赋给tosleep，然后再次尝试休眠，直到完全休眠完指定的时间
//        tosleep = remain;
//    }
//}
// V1
// 函数定义: 等待特定的子进程结束
pid_t wait_till_pid(pid_t pid) {
    // 无限循环直到找到指定的子进程PID或发生错误
    while (true) {
        // 使用wait函数等待任何子进程结束
        // wait函数返回结束的子进程的PID，或在出错时返回-1
        pid_t p = wait(nullptr);

        // 如果发生错误(p == -1) 或者结束的子进程的PID与我们要查找的PID匹配
        if (p == -1 || p == pid) {
            // 返回找到的子进程的PID或错误代码(-1)
            return p;
        }
    }
}
// V2 : 使用信号机制的版本
pid_t wait_till_pid(pid_t pid, int sec) {
    // 定义一个静态布尔变量，用于检测是否已收到SIGALRM信号（定时器超时）
    static bool timeout = false;

    // 注册一个信号处理函数，当接收到SIGALRM信号时，打印消息并设置timeout为true
    signal(SIGALRM, [](int) { std::cout << "received SIGALRM" << std::endl; timeout = true; });

    // 注册一个信号处理函数，当接收到SIGCHLD信号（子进程状态改变）时，打印消息
    signal(SIGCHLD, [](int) { std::cout << "received SIGCHLD" << std::endl; });

    // 设置一个定时器，sec秒后发送SIGALRM信号
    alarm(sec);

    // 定义一个信号集合
    sigset_t set;
    // 初始化信号集合，包括所有已知的信号
    sigfillset(&set);
    // 从信号集合中删除SIGALRM和SIGCHLD，这样它们就不会被阻塞
    sigdelset(&set, SIGALRM);
    sigdelset(&set, SIGCHLD);

    // 无限循环，等待信号或条件满足
    while (true) {
        std::cout << "waiting..." << std::endl;

        // 暂停程序，直到接收到一个信号
        sigsuspend(&set);

        // 如果接收到的是SIGALRM信号，打印消息并返回-1
        if (timeout) {
            std::cout << "Alarm wins" << std::endl;
            return -1;
        } else {
            // 如果没有超时，则使用wait函数等待子进程结束，并获取其PID
            pid_t p = wait(nullptr);
            std::cout << "wait answered " << p << std::endl;

            // 如果结束的子进程PID与我们要查找的PID匹配，取消定时器
            if (p == pid) {
                alarm(0);
            }

            // 如果wait函数返回错误或找到的PID与我们要查找的PID匹配，返回该PID
            if (p == -1 || p == pid) {
                return p;
            }
        }
    }
}

int main () {
    //fork()
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;

    int nbfils = 0;
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
        if(fork()!=0){nbfils++;
            break;}else{nbfils = 0;}
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
                nbfils = 0;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}else{
                nbfils++;
            }
		}
	}
    for(int i=0;i<nbfils;i++){
        int status;
        int pid = wait(&status);
        std::cout<<"detection par " << getpid() << "de fin du fils de pid = " << pid << endl;
    }
    std::cout << "Fin du processus " << getpid() << std::endl;

    //signal
    pid_t pid2 =fork();
    if (pid2==0) {

        sleep(5);
    } else {
        signal(SIGINT,[](int){});
        pid_t res = wait_till_pid(pid2,3);
        std::cout << "wait gave :" << res << std::endl;
    }

    //combat

    pid_t pere = getpid();
    pid_t pid = fork();
    srand(pid);
    if(pid == 0){
        combat(pere);
    }else{
        combat(pid);
    }

	return 0;
}
