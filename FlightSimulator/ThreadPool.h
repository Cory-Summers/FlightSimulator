#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <utility>
template<typename T, typename ... TArgs>
class ThreadPool
{
  using func_type = std::function<T(TArgs...)>;
  using tuple_type = std::tuple<TArgs...>;
public:
  ThreadPool() :
    m_pool(),
    max_concurrent(std::thread::hardware_concurrency()),
    terminate_pool(0),
    busy(0),
    queue_mutex(),
    cv_task(),
    cv_finish()
  {
    for (int i = 0; i < max_concurrent; i++)
    {
      m_pool.push_back(std::thread(&ThreadPool::InfiniteLoop, this));
    }
  }
  virtual void Add(std::function<T(TArgs...)> func, TArgs... parameters)
  {
    std::tuple<TArgs...> tup = std::make_tuple(parameters...);
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      job_queue.push(std::make_pair(func, tup));

    }
    cv_task.notify_one();
  }
  void WaitFinished()
  {
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      cv_finish.wait(lock, [this]() { return job_queue.empty(); });
    }
  }
protected:
  virtual void InfiniteLoop()
  {
    while (true)
    {
      std::pair<std::function<T(TArgs...)>, std::tuple<TArgs...>> job;
      {
        std::unique_lock<std::mutex> lock(queue_mutex);
        cv_task.wait(lock, [this] {return !job_queue.empty() || terminate_pool; });
        job = std::move(job_queue.front());
        job_queue.pop();
      }
      std::apply(job.first, job.second);
      cv_finish.notify_one();
    }
  }
  size_t max_concurrent;
private:
  std::vector<std::thread> m_pool;
  std::mutex queue_mutex;
  std::queue<std::pair<std::function<T(TArgs...)>, std::tuple<TArgs...>>> job_queue;
  std::condition_variable cv_task;
  std::condition_variable cv_finish;
  int busy = 0;
  bool terminate_pool = 0;
};