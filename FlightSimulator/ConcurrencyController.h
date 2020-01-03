#pragma once
#include <mutex>
#include <condition_variable>
#include <functional>
namespace MVC {
  class ConcurrencyController
  {
  public:
    ConcurrencyController();
    std::condition_variable cv_star;
    std::condition_variable cv_natural;
    std::mutex star_mutex;
    std::mutex natural_mutex;
    
  };
  typedef ConcurrencyController ConcurContr;
}