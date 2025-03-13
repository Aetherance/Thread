#include<iostream>
#include"threadpool.h"
#include<unistd.h>

void func(int num) {
    printf("hello %d\n",num);
}

void func2(double num) {
    printf("hello i am func 2 %lf\n",num);
}

void func3() {
    printf("hello func3!\n");
}

void func4(int num ,double num2) {
    printf("hello %d %lf\n",num,num2);
}

int main() {
    threadpool pool(32);

    pool.enqueue(func,10);
    pool.enqueue(func2,6.824);
    pool.enqueue(func3);
    pool.enqueue(func4,1,3.14);

    return 0;
}