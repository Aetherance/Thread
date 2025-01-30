#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

void* a(void *) {
    cout<<a;
    return nullptr;
}

int main() {
    pthread_t t;
    pthread_create(&t,NULL,a,NULL);

    sleep(1);

    pthread_join(t,NULL);
    pthread_join(t,nullptr);
    
    return 0;
}