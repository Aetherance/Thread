#include<iostream>
#include<thread>

using namespace std;
int main()
{
    int b = 20;
    int a = 10;
    [a](int b) -> void {
        cout<<"'b' = "<<b<<" "<<"'a' = "<<" "<<a<<endl;
        cout<<"This is Lambda"<<endl;
    }(a);

    thread t1{
        [](){
            cout<<"匿名线程调用"<<endl;
        }
    };
    t1.join();

    return 0;
}