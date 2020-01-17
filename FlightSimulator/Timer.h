#pragma once
#include <chrono>
  class Timer
  {
  protected:
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    using TimeStamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
    using TimeDelta = std::chrono::nanoseconds;
  public:
    Timer();
    inline void Start() { this->start = std::chrono::steady_clock::now(); }
    virtual TimeDelta const& Stop();
    inline double GetCount() const {
      return sec_elapsed;
    }
    void SetLateInterval(TimeDelta const& interval) { late_interval = interval; }
    bool CheckLateUpdate();

  protected:
    TimePoint start;
    TimePoint end;
    TimeDelta delta_t;
    TimeDelta late_delta;
    TimeDelta late_interval;
    double sec_elapsed;
};