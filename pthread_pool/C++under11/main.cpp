#include<iostream>
#include"threadpool"
#include<unistd.h>
using namespace std;

int main() {
    threadpool pool(16);

    for(int i = 0;i<200;i++) {
        pool.submit([i]() {
            printf("Task %02d is running on thread %ld\n",i,pthread_self());
            sleep(1);
        });
    }

    pool.stop();

    return 0;
}