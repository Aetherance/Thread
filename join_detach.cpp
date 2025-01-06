#include<iostream>
#include<pthread.h>
using namespace std;
void pthread_test()
{
    cout<<"test()调用"<<endl;
}
int main()
{
    pthread_t ptd;
    pthread_create(&ptd,NULL,(void*(*)(void*))pthread_test,NULL);
    pthread_detach(ptd);
    pthread_join(ptd,NULL);

    // pthread_exit(0);
}