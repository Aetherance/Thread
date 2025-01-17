#include<iostream>
#include<thread>
using namespace std;

void A(int a,int b)
{
    cout<<a+b;
}

int main()
{
    thread t1(A,10,20);
    t1.join();

    return 0;
}