#include<iostream>
#include<filesystem>
using namespace std;
using namespace filesystem;

int main()
{
    path root("/");

    for(auto & entry : directory_iterator(root)) {
        cout<<entry;
    }

    


    return 0;
}