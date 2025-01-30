#include <pthread.h>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>
#include <unistd.h>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    // 添加任务
    void enqueue(std::function<void()> task);

private:
    static void* worker(void* arg);  // 线程执行的任务
    void threadLoop();  // 线程的循环体

    size_t numThreads;
    std::vector<pthread_t> threads;
    std::queue<std::function<void()>> taskQueue;
    pthread_mutex_t queueMutex;
    pthread_cond_t queueCond;
    pthread_cond_t doneCond;
    bool stop;  // 是否停止线程池
    int activeTasks;  // 当前活跃的任务数量
};

ThreadPool::ThreadPool(size_t numThreads) : numThreads(numThreads), stop(false), activeTasks(0) {
    pthread_mutex_init(&queueMutex, nullptr);
    pthread_cond_init(&queueCond, nullptr);
    pthread_cond_init(&doneCond, nullptr);

    threads.resize(numThreads);
    for (size_t i = 0; i < numThreads; ++i) {
        if (pthread_create(&threads[i], nullptr, &ThreadPool::worker, this) != 0) {
            std::cerr << "Failed to create thread!" << std::endl;
            exit(1);
        }
    }
}

ThreadPool::~ThreadPool() {
    {
        // 锁住任务队列并设置停止标志
        pthread_mutex_lock(&queueMutex);
        stop = true;
        pthread_cond_broadcast(&queueCond);  // 通知所有线程退出
        pthread_mutex_unlock(&queueMutex);
    }

    // 等待所有任务完成
    pthread_mutex_lock(&queueMutex);
    while (activeTasks > 0) {
        pthread_cond_wait(&doneCond, &queueMutex);  // 等待直到所有任务完成
    }
    pthread_mutex_unlock(&queueMutex);

    // 等待所有线程结束
    for (auto& thread : threads) {
        pthread_join(thread, nullptr);
    }

    pthread_mutex_destroy(&queueMutex);
    pthread_cond_destroy(&queueCond);
    pthread_cond_destroy(&doneCond);
}

void ThreadPool::enqueue(std::function<void()> task) {
    pthread_mutex_lock(&queueMutex);
    taskQueue.push(task);
    activeTasks++;  // 增加任务计数
    pthread_cond_signal(&queueCond);  // 唤醒一个线程
    pthread_mutex_unlock(&queueMutex);
}

void* ThreadPool::worker(void* arg) {
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    pool->threadLoop();
    return nullptr;
}

void ThreadPool::threadLoop() {
    while (true) {
        std::function<void()> task;
        pthread_mutex_lock(&queueMutex);

        // 等待有任务或者线程池关闭
        while (taskQueue.empty() && !stop) {
            pthread_cond_wait(&queueCond, &queueMutex);
        }

        if (stop && taskQueue.empty()) {
            pthread_mutex_unlock(&queueMutex);
            break;  // 如果线程池关闭且任务队列为空，则退出线程
        }

        task = taskQueue.front();
        taskQueue.pop();
        pthread_mutex_unlock(&queueMutex);

        // 执行任务
        task();

        // 完成一个任务，减少任务计数
        pthread_mutex_lock(&queueMutex);
        activeTasks--;
        if (activeTasks == 0) {
            pthread_cond_signal(&doneCond);  // 如果所有任务完成，唤醒主线程
        }
        pthread_mutex_unlock(&queueMutex);
    }
}

void sampleTask(int id) {
    std::cout << "Task " << id << " is being executed by thread " << pthread_self() << std::endl;
    sleep(1);  // 模拟任务执行的延迟
}

int main() {
    ThreadPool pool(4);  // 创建一个包含4个线程的线程池

    // 向线程池提交10个任务
    // for (int i = 0; i < 10; ++i) {
    //     pool.enqueue([i](){ sampleTask(i); });
    // }

    // 主线程等待一段时间让所有任务完成
    std::cout << "Waiting for all tasks to complete..." << std::endl;
    // sleep(5);

    return 0;
}
