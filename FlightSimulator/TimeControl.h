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

  double const& GetScale() const { return time_scale; }
  void SetScale(double const& scale) { time_scale = scale; }
  void IncreaseScale();
  void DecreaseScale();
  void DisplayDate();
  TimeStamp const& GetDate() const;
  ~TimeController() {}
private:
  TimeStamp sim_date;
  double time_scale  = 1.0;
  const double MAX_SCALE = 1e8;

};

