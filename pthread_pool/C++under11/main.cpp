#include"threadpool"

int main() {
    threadpool pool(4);

    for(int i = 0;i<100;i++) {
        pool.submit([i](){
            cout<<"Task Test "<< i + 1 <<endl;
        });
    }

    sleep(1);
    pool.stop();
    return 0;
}