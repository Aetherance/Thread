#include"threadpool"

int main() {
    threadpool pool(100);

    for(int i = 0;i<10;i++) {
        pool.submit([i](){
            cout<<"Task Test "<< i + 1 <<endl;
        });
    }

    pool.stop();
    cout<<"stoped";
    return 0;
}