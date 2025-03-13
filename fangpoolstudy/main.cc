#include<iostream>
#include"threadpool.h"
using namespace std;

int main() {
    threadpool pool;

    pool.enqueue([]() {
        cout<<"Hello world!";
    });

    return 0;
}