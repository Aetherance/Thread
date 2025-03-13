#include<iostream>
using namespace std;

template<class ... Args>
void func(Args && ... args) {
    (cout<<...<<args);
}

int main() {

    func("Hello World!\n","想传几个传几个\n");

    return 0;
}