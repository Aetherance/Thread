# 线程学习笔记
# 为什么要使用线程
1. 线程之间共享全局区和堆内存，这使线程之间的信息共享较进程之间更为方便，代价更小。
2. 创建进程时使用的系统调用`fork()`代价高，创建线程使用的系统调用`clone()`比`fork()`通常快10倍不止。

# 线程共享的属性
1. 全局内存
2. 进程ID 父进程ID
3. 进程组ID与会话ID
4. 控制终端
5. 打开的文件描述符
6. 信号处置
7. 某些时候的栈 (?)
8. ...
每个线程都有存放局部变量的私有栈。

# Pthreads函数返回值
与传统函数返回-1代表失败不同的是，所有的Pthreads函数都是返回正值表示失败。

# 创建线程
程序启动时，一个进程中只有一条称为*主线程*的线程。

调用`pthread_create()`将创建一个线程。

`pthread_create()`的第一个参数是一个指向`pthread_t`类型的指针,线程ID将被写入该类型中

第二个参数是一个 const pthread _attr_t类型的指针 用于定制不同的线程属性，通常直接设为`NULL`

第三个参数是一个函数指针，指向线程的start函数。线程从此函数开始运行。

第四个函数是一个指向start函数参数的指针。

# 终止线程
- 主线程调用`main`函数中的`return`语句会终止所有线程
- 任意线程调用`exit()`语句会终止所有线程
- 线程执行`start`函数的`return`语句只会终止调用的线程自身
- 线程调用`pthread_exit()`语句`只`会终止调用的线程自身，不论这个线进程是不是主线程
- 调用`pthread_cancle()`取消线程

# 线程ID
在pthread函数中,线程ID由`pthread_t`定义。

`pthread_t`是一种*不透明数据类型* 在Linux实现中,pthread_t是无符号长整形,而在其他实现中有可能是指针或者结构体。

因此，对于pthread_t的比较，应该使用pthread_equal函数而不是C语言中的`==`等操作符。

# join线程
函数`pthread_join`会等待一个线程，直至其终止。线程终止时会立即返回。这种操作被称为*连接*

若函数`pthread_join`的第二个参数`retval`为一非空指针，将会保存线程终止时返回值的拷贝。即保存了线程调用`return`或`pthread_exit`时所指定的值

向函数`pthread_join`传入已经join过的线程id的结果未知

调用`pthread_join`的线程会阻塞，直到对应线程执行完毕 相当于对进程使用`wait()`系统调用 不同的是，`wait()`只能由父进程调用

# 分离线程
线程具有可连接和已分离两个状态。调用`pthread_detach()`可以使线程分离，即使其不可连接。

线程一旦处于分离状态，便不能再调用join来与其连接，也不能再重使其返回可连接状态。`pthread_detach()`的调用是不可逆的。

不论线程是否已分离，调用`exit()`或主进程执行`return`时，所有线程都会立即终止。

# 线程属性
利用`pthread_create()`的第二个参数可以设置线程的属性。

# 互斥量
为了防止两个线程同时对某一共享资源进行修改，或者同时对其进行读写操作，要使用互斥量来确保同时只有一个线程访问共享资源。

例如，对于一个线程AB都可访问的全局变量，线程A在访问时将其‘锁’住，可以防止B访问，减少错误的发生。

# 多线程使用笔记

## create

在多线程的使用中，可能会出现主线程先结束使其他线程也终止的情况

```cpp
void* thread_func(void *)
{
    cout<<"func()调用  线程ID -> "<<pthread_self()<<endl;
    return NULL;
}
int main()
{
    thread_func(NULL);
    pthread_t ptd;
    pthread_create(&ptd,NULL,thread_func,NULL);

    return 0;
}
```

只输出了主线程的调用

需要让主线程'等待'其他线程结束。 可以使用 `pthread_join()`或让主线程sleep 使用while()等待也是可行的 

```cpp
void* thread_func(void *)
{
    cout<<"func()调用  线程ID -> "<<pthread_self()<<endl;
    return NULL;
}
int main()
{
    thread_func(NULL);
    pthread_t ptd;
    pthread_create(&ptd,NULL,thread_func,NULL);
    
    pthread_join(ptd,NULL);
    //sleep(3);
    //while(1);

    return 0;
}
```

也可以调用`pthread_exit`让主线程退出，其他线程会继续运行。

```cpp
void* thread_func(void *)
{
    cout<<"func()调用  线程ID -> "<<pthread_self()<<endl;
    return NULL;
}
int main()
{
    thread_func(NULL);
    pthread_t ptd;
    pthread_create(&ptd,NULL,thread_func,NULL);   
    
    pthread_exit(0);
}
```

## join和detach

```cpp
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
```

一个已经detach的线程是无法join的

```cpp
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
```