#include<iostream>
#include<thread>
#include<future>

using namespace std;

int func() {
    return 10;
}

int main() {

    thread task([]() {
        cout<<"hello"<<endl;
        return 10;
    });

    task.join();

    return 0;
}