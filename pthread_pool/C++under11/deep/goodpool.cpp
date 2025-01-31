#include<iostream>
#include <queue>
#include <vector>
#include <pthread.h>
#include <unistd.h>  // 用于usleep
using namespace std;

class Task {
public:
    virtual ~Task() {}
    virtual void run() = 0;
};

class ThreadPool {
public:
    explicit ThreadPool(size_t thread_num) 
        : stop(false), pending_tasks(0), running_tasks(0) {
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&task_cond, NULL);
        pthread_cond_init(&complete_cond, NULL);

        threads.reserve(thread_num);
        for (size_t i = 0; i < thread_num; ++i) {
            pthread_t thread;
            pthread_create(&thread, NULL, workerEntry, this);
            threads.push_back(thread);
        }
    }

    ~ThreadPool() {
        shutdown();
    }

    void enqueue(Task* task) {
        pthread_mutex_lock(&mutex);
        task_queue.push(task);
        pending_tasks++;
        pthread_cond_signal(&task_cond);
        pthread_mutex_unlock(&mutex);
    }

    void waitAll() {
        pthread_mutex_lock(&mutex);
        while (pending_tasks > 0 || running_tasks > 0) {
            pthread_cond_wait(&complete_cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }

    void shutdown() {
        if (stop) return;

        pthread_mutex_lock(&mutex);
        stop = true;
        pthread_mutex_unlock(&mutex);

        pthread_cond_broadcast(&task_cond);

        for (size_t i = 0; i < threads.size(); ++i) {
            pthread_join(threads[i], NULL);
        }

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&task_cond);
        pthread_cond_destroy(&complete_cond);
    }

private:
    static void* workerEntry(void* arg) {
        ThreadPool* pool = static_cast<ThreadPool*>(arg);
        pool->worker();
        return NULL;
    }

    void worker() {
        while (true) {
            printf("Thread %lu started\n", pthread_self());
            pthread_mutex_lock(&mutex);
            
            // 等待任务或停止信号
            while (task_queue.empty() && !stop) {
                pthread_cond_wait(&task_cond, &mutex);
            }
            
            // 退出条件：停止且队列为空
            if (stop && task_queue.empty()) {
                pthread_mutex_unlock(&mutex);
                printf("Thread %lu exiting\n", pthread_self());
                break;
            }
            
            // 取出任务
            Task* task = task_queue.front();
            task_queue.pop();
            pending_tasks--;
            running_tasks++;
            
            pthread_mutex_unlock(&mutex);
            
            // 执行任务
            task->run();
            delete task;
            
            // 更新状态
            pthread_mutex_lock(&mutex);
            running_tasks--;
            const bool all_done = (pending_tasks == 0 && running_tasks == 0);
            pthread_mutex_unlock(&mutex);
            
            if (all_done) {
                pthread_cond_signal(&complete_cond);
            }
        }
    }

    std::vector<pthread_t> threads;
    std::queue<Task*> task_queue;
    
    pthread_mutex_t mutex;
    pthread_cond_t task_cond;
    pthread_cond_t complete_cond;
    
    bool stop;
    size_t pending_tasks;
    size_t running_tasks;
};

// 使用示例
class PrintTask : public Task {
public:
    PrintTask(int id) : task_id(id) {}
    virtual void run() {
        usleep(100000); // 模拟耗时操作
        printf("Task %d executed by thread %lu\n", 
              task_id, (unsigned long)pthread_self());
    }
private:
    int task_id;
};

int main() {
    {
        ThreadPool pool(100);
        
        // 提交任务
        for (int i = 0; i < 100; ++i) {
            pool.enqueue(new PrintTask(i));
        }
        
        printf("All tasks submitted\n");
        pool.waitAll();
        printf("All tasks completed\n");
        
        // 析构时自动调用shutdown()
    } // 此处pool离开作用域
    
    printf("Thread pool destroyed\n");
    return 0;
}