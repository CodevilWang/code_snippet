// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
// #include <function>
#include <condition_variable>
class ThreadPool {
public:
    ThreadPool(uint32_t size) : _pool_size(size) {}
    ~ThreadPool() {}
    void thread_job() {
        while (true) {
            std::unique_lock<std::mutex> lg(*_mutex);
            _cond->wait(lg, [&]{return !_job_queue->empty() || *_done;});
            if (*_done) {
                break;
            }
            // while (_job_queue->empty()) {
            //     _cond->wait(lg);
            // }
            std::function<void(void)> job = _job_queue->front();
            _job_queue->pop();
            job();
        }
    }
    bool init(std::mutex* m, std::condition_variable* con,
              std::queue<std::function<void(void)>>* jq, int* g_done) {
        if (!m or !con) {
            return false;
        }
        _mutex = m;
        _cond = con;
        _job_queue = jq;
        _done = g_done;
        printf("in init funciton.\n");
        for (int i = 0; i < _pool_size; ++i) {
            _t_pool.push_back(std::thread(&ThreadPool::thread_job, this));
            // _t_pool.emplace_back(ThreadPool::thread_job, this);
        }
        return true;
    }
    bool stop() {
        for (int i = 0; i < _pool_size; ++i) {
            _t_pool[i].join();
        }
        return true;
    }
private:
    uint32_t _pool_size;
    std::queue<std::function<void()>>* _job_queue;
    std::vector<std::thread> _t_pool; 
    std::mutex* _mutex;
    std::condition_variable* _cond;
    int* _done;
    //volatile int* _done;
};
void work() {
   printf("current work %d\n", std::this_thread::get_id()); 
}

int main() {
    std::queue<std::function<void(void)>> g_job_queue; 
    ThreadPool tp(10);
    std::mutex m;
    std::condition_variable cond;
    int done = 0;
    if (!tp.init(&m, &cond, &g_job_queue, &done)) {
        printf("thread pool init failed.\n");
        return -1;
    }
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lg(m);
        g_job_queue.push(std::function<void()>(work));
        if (g_job_queue.size() == 1) {
            cond.notify_all();
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    done = 1;
    cond.notify_all();
    tp.stop();
    printf("done\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
