#include<iostream>
#include<thread>
using namespace std;

void A()
{
    cout<<"A"<<endl;
}

void B()
{
    cout<<"B"<<endl;
}

int main()
{
    thread t1(B);
    t1.join();

    auto func = []() -> void {
        cout<<"func"<<endl;
    };

    func();

    return 0;
}