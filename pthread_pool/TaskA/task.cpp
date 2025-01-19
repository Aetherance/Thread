#include<iostream>
#include"threadpool.h"
using namespace std;

unsigned long long Fact(int n) {
    if(n<=1)return 1;
    return n * Fact(n-1);
}

int main()
{
    threadpool pool(6);
    
    // for(int i = 1;i<20;i++) {
    //     pool.TaskSubmit(
    //         [i]() {
    //             cout<<i<<endl;;
    //         }
    //     );
    // }

    pool.Stop();

    return 0;
}