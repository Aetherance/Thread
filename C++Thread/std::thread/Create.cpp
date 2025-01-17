#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;

void A()
{
    cout<<"A线程"<<endl;
}

int main()
{
    thread t(A);
    // t.join();
    t.detach();

    sleep(1);

    return 0;
}