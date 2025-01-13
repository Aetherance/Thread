#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;
int value = 0;
void func()
{
    cout<<"func()调用"<<endl;
    value = 1;
    cout<<"v1->"<<value<<endl;
}

void func2()
{
    cout<<"func2()调用"<<endl;
    value = 2;
    cout<<"v2->"<<value<<endl;
}

int main()
{
    pthread_t ptd1,ptd2;
    pthread_create(&ptd1,NULL,(void*(*)(void*))func,NULL);
    pthread_create(&ptd2,NULL,(void*(*)(void*))func2,NULL);

    sleep(1);
    cout<<value<<endl;
    pthread_exit(NULL);
}
