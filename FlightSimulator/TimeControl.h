#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <ctime>
#include "StateElements.h"
#include "Timer.h"
constexpr std::chrono::seconds J2000Epoch = std::chrono::seconds(946684801ll);
class TimeController : public Timer
{
public:
  TimeController();
  TimeController(double const &);
  TimeDelta const& Stop() override;
  inline double GetCount() const {
    return sec_elapsed;
  }
  double const& GetScale() const { return time_scale; }
  void SetScale(double const& scale) { time_scale = scale; }
  void DisplayDate();
  TimeStamp const& GetDate() const;
  ~TimeController() {}
private:
  TimeStamp sim_date;
  double sec_elapsed = 0.1;
  double time_scale  = 1.0;
};

