// Copyright 2018 All Rights Reserved.
// Author: codevil.w.m@gmail.com (M W)
#include <stdio.h>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <future>
// #include <function>
#include <condition_variable>
#include <time.h>
template <typename R, typename ...Args>
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
#ifdef USE_FUNC
            std::function<R(Args...)> job = _job_queue->front();
#elif defined USE_PT
            std::packaged_task<R(Args...)> job(std::move(_job_queue->front()));
#endif
            _job_queue->pop();
#ifdef USE_PT
            job(9);
#elif defined USE_FUNC
            job();
#endif
        }
    }
#ifdef USE_FUNC
    bool init(std::mutex* m, std::condition_variable* con,
              std::queue<std::function<R(Args...)>>* jq, int* g_done) {
#elif defined USE_PT
    bool init(std::mutex* m, std::condition_variable* con,
              std::queue<std::packaged_task<R(Args...)>>* jq, int* g_done) {
#endif
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
#ifdef USE_FUNC
    std::queue<std::function<R(Args...)>>* _job_queue;
#elif defined USE_PT
    std::queue<std::packaged_task<R(Args...)>>* _job_queue;
#endif
    std::vector<std::thread> _t_pool; 
    std::mutex* _mutex;
    std::condition_variable* _cond;
    int* _done;
    //volatile int* _done;
};
void work() {
   printf("current work %d\n", std::this_thread::get_id()); 
}
int work2(int) {
    return rand();

}

int main() {
    srand(time(NULL));
#ifdef USE_FUNC
    std::queue<std::function<void(void)>> g_job_queue; 
    ThreadPool<void, void> tp(10);
#elif defined USE_PT
    std::queue<std::packaged_task<int(int)>> g_job_queue; 
    ThreadPool<int, int> tp(10);
#endif
    std::mutex m;
    std::condition_variable cond;
    int done = 0;
    if (!tp.init(&m, &cond, &g_job_queue, &done)) {
        printf("thread pool init failed.\n");
        return -1;
    }
    std::vector<std::future<int>> res_vec;
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lg(m);
#ifdef USE_FUNC
        g_job_queue.push(std::function<void()>(work));
#elif defined USE_PT
        std::packaged_task<int(int)> task(work2);
        res_vec.push_back(std::move(task.get_future()));
        g_job_queue.push(std::move(task));
#endif
        if (g_job_queue.size() == 1) {
            cond.notify_all();
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    done = 1;
    cond.notify_all();
    tp.stop();
    for (int i = 0; i < res_vec.size(); ++i) {
        printf("%d\t%d\n", i, res_vec[i].get());
    }
    printf("done\n");
    return 0;
}

/* vim: set expandtab ts=2 sw=2 sts=2 tw=80: */
