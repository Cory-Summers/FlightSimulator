#include "FrameTimer.h"
#include <thread>
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using TimeStamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
using TimeDelta = std::chrono::nanoseconds;
FrameTimer::FrameTimer(unsigned int fps)
  : frame_interval(std::chrono::duration_cast<TimeDelta>(std::chrono::seconds(1)) / fps)
{
  Start();
  
}

TimeDelta const& FrameTimer::Stop()
{
  TimeDelta period = frame_interval;
  this->end = std::chrono::steady_clock::now();
  delta_t = this->end - this->start;
  late_delta += delta_t;
  if (delta_t < frame_interval)
  {
    period -= delta_t;
    std::this_thread::sleep_for(period);
  }
  return delta_t;
}
