#include<iostream>
#include"threadpool"
#include<sstream>
#include<chrono>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;
using namespace chrono;

// 祖传代码
cpp_int c(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * c(n - 1);
}

void Task(int n) {
    ostringstream oss;
    oss<<c(n);
    char * result = new char[204800];
    strcpy(result,oss.str().c_str());
    printf("%d 的阶乘是 \n %s\n\n",n,result);
    delete[] result;
}

int main()
{
    auto start = high_resolution_clock::now();
    threadpool pool(24);

    
    for(int i = 1;i<=1000;i++) {
        pool.submit([i]() {
            Task(i);
        });
    }

    pool.stop();
    auto end = high_resolution_clock::now();
    auto mstime = duration_cast<microseconds>(end - start);
    auto stime = duration_cast<seconds>(end - start);
    cout<<"共用时 "<<mstime.count()<<" ms"<<endl;
    cout<<"约 "<<stime.count()<<" s"<<endl;
    
    return 0;
}