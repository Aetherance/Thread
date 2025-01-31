#include<iostream>
#include"threadpool.h"
using namespace std;

int main()
{
    threadpool pool(20);

    for(int i = 0;i < 100 ; i++) {
        pool.TaskSubmit([i](){
            cout<<"TASK "<<i<<endl;
        });
    }

    // sleep(1);
    pool.Stop();
    // sleep(1000);

    return 0;
}