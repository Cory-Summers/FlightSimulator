#include "Timer.h"
#include <iostream>
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using TimeStamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
using TimeDelta = std::chrono::nanoseconds;

constexpr TimeDelta second = std::chrono::seconds(1);
Timer::Timer()
  : start()
  , end()
  , delta_t()
  , late_delta()
  , late_interval(std::chrono::seconds(1))
{
}

TimeDelta const& Timer::Stop()
{
  this->end = std::chrono::steady_clock::now();
  delta_t = this->end - this->start;
  late_delta += delta_t;
  return delta_t;
}


bool Timer::CheckLateUpdate()
{
  if (late_delta > late_interval) {
    late_delta -= late_interval;
    return true;
  }
  return false;
}
