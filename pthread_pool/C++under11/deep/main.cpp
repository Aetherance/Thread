// #include"1.hpp"
// #include<iostream>
// #include<unistd.h>
// using namespace std;


// class MyTask : public Task {
// public:
//     explicit MyTask(int id) : task_id(id) {}
    
//     virtual void run() {
//         usleep(100000); // 模拟耗时操作
//         printf("Task %d done\n", task_id);
//     }
// private:
//     int task_id;
// };

// int main() {
//     ThreadPool*pool = new ThreadPool(100);
    
//     // 添加100个任务
//     for (int i = 0; i < 5; ++i) {
//         pool->enqueue(new MyTask(i));
//     }
    
//     printf("All tasks enqueued\n");
//     pool->waitAll();  // 等待全部完成
//     printf("All tasks completed\n");
    
//     delete pool;


// }