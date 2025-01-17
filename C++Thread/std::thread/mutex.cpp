#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex mtx;

void A()
{
    mtx.lock();
    cout<<"A 线程调用"<<endl;
    mtx.unlock();
}

void B()
{
    mtx.lock();
    cout<<"B 线程调用"<<endl;
    mtx.unlock();
}

int main()
{
    thread t1(A),t2(B);

    t1.join();
    t2.join();

    return 0;
}