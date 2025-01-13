#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;
void* A(void *)
{
    // pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL); // 不可取消
    while (1)
        cout<<"A is doing something"<<endl;
    
    return NULL;
}

int main()
{
    pthread_t ptd1,ptd2;
    pthread_create(&ptd1,NULL,A,NULL);

    sleep(3);

    pthread_cancel(ptd1);

    pthread_join(ptd1,NULL);
    return 0;
}