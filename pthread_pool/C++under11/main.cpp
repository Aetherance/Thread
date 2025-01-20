#include<iostream>
#include"threadpool.h"
using namespace std;

int main()
{
    threadpool pool(60);

    pool.TaskSubmit([](){
        cout<<"TASK A"<<endl;
    });

    pool.TaskSubmit([](){
        cout<<"TASK B"<<endl;
    });

    // pool.TaskSubmit([](){
    //     cout<<"TASK C"<<endl;
    // });

    // pool.TaskSubmit([](){
    //     cout<<"TASK D"<<endl;
    // });

    // pool.TaskSubmit([](){
    //     cout<<"TASK E"<<endl;
    // });

    pool.Stop();

    return 0;
}