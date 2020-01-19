#pragma once
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
namespace MVC::Render {
  template<typename T, typename Key = int64_t>
  class ObjectPool
  {
    using ret_ptr = std::weak_ptr<T>;
    using size_type = size_t;
    using object_type = std::shared_ptr<T>;
    using object_iter = typename std::list<object_type>::iterator;
    using const_iter = typename std::list<object_type>::const_iterator;
    using lock_type = std::unique_lock<std::mutex>;

  public:
    ObjectPool();
    ret_ptr   Retrieve();
    template<typename ... TArgs>
    ret_ptr     Retrieve(TArgs&&...);
    size_type   Release(ret_ptr);
    size_type   Available() const;
    ret_ptr     Add(object_type&);
    object_iter begin() { return m_pool.begin(); }
    object_iter end() { return m_pool.end(); }
    const_iter  cbegin()   const { return m_pool.cbegin(); };
    const_iter  cend()     const { return m_pool.cend(); };
    size_type   Size()     const { return m_pool.size(); }
    size_type   Capacity() const { return m_pool.size() + m_available.size(); }
  private:
    std::list<object_type> m_pool;
    std::list<object_type> m_available;
    std::mutex m_mutex;
  };

  template<typename T, typename Key>
  inline ObjectPool<T, Key>::ObjectPool()
    : m_pool(),
      m_available(),
      m_mutex()
  {
  }

  template<typename T, typename Key>
  inline std::weak_ptr<T> ObjectPool<T, Key>::Retrieve()
  {
    lock_type lock(m_mutex);
    if (!m_available.empty())
    {
      auto temp = m_available.front();
      m_pool.push_back(temp);
      m_available.pop_front();
      return std::weak_ptr<T>(temp);
    }
    else
    {
      object_type temp = std::make_shared<T>();
      m_pool.push_back(temp);
      return std::weak_ptr<T>(temp);
    }
  }

  template<typename T, typename Key>
  inline size_t ObjectPool<T, Key>::Release(ret_ptr data)
  {
    lock_type lock(m_mutex);
    *data.lock() = T();
    m_available.push_back(data.lock());
    m_pool.remove(data.lock());
    return m_pool.size();
  }

  template<typename T, typename Key>
  inline size_t ObjectPool<T, Key>::Available() const
  {
    return static_cast<size_type>(m_available.size());
  }

  template<typename T, typename Key>
  inline std::weak_ptr<T> ObjectPool<T, Key>::Add(object_type& obj)
  {
    lock_type lock(m_mutex);
    m_pool.push_back(obj);
    return std::weak_ptr(obj);
  }


  template<typename T, typename Key>
  template<typename ...TArgs>
  inline std::weak_ptr<T> ObjectPool<T, Key>::Retrieve(TArgs&& ... args)
  {
    lock_type lock(m_mutex);
    if (!m_available.empty())
    {
      auto temp = std::m_available.front();
      m_pool.push_back(temp);
      m_available.pop_front();
      *(temp.get()) = T(std::forward<TArgs>(args)...);
      return std::weak_ptr<T>(temp);
    }
    else
    {
      object_type temp = std::make_shared<T>(args...);
      m_pool.push_back(temp);
      return std::weak_ptr<T>(temp);
    }
  }

}

