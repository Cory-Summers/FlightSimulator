#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include "StateElements.h"
constexpr std::chrono::seconds J2000Epoch = std::chrono::seconds(946684801ll);
class TimeController
{
  using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
  using TimeStamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
  using TimeDelta = std::chrono::nanoseconds;
public:
  TimeController();
  inline void Start() { this->start = std::chrono::steady_clock::now(); }
  TimeDelta const& Stop();
  inline double GetCount() const {
    return sec_elapsed;
  }
  double const& GetScale() const { return time_scale; }
  void SetScale(double const& scale) { time_scale = scale; }
  bool CheckLateUpdate();
  TimeStamp const& GetDate() const;
  ~TimeController() {}
private:

  TimePoint start;
  TimePoint end;
  TimeDelta delta_t;
  TimeStamp sim_date;
  TimeDelta late_delta;
  double sec_elapsed = 0.1;
  double time_scale = 1.0;
};

