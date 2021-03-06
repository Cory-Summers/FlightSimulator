#include "TimeControl.h"

#include <iostream>
using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using TimeStamp = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;
using TimeDelta = std::chrono::nanoseconds;
TimeController::TimeController() :
  time_scale(1.0),
  sim_date(J2000Epoch),
  MAX_SCALE(1e7),
  Timer()
{
}

TimeController::TimeController(double const& val) :
  time_scale(val),
  sim_date(J2000Epoch)
{
  start = end = TimePoint();
  delta_t = TimeDelta();
}

TimeDelta const& TimeController::Stop()
{
  this->end = std::chrono::steady_clock::now();
  delta_t = this->end - this->start;
  sec_elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(delta_t).count() * time_scale;
  sim_date += std::chrono::nanoseconds(static_cast<int64_t>(delta_t.count() * time_scale));
  late_delta += delta_t;
  return delta_t;
}


void TimeController::IncreaseScale()
{
  if (time_scale != MAX_SCALE)
  {
    time_scale *= 10.0;
  }
}

void TimeController::DecreaseScale()
{
  if (time_scale != 1.0)
  {
    time_scale /= 10.0;
    std::cout << "Scale: " << time_scale << '\n';
  }
}

void TimeController::DisplayDate()
{
  std::chrono::time_point<std::chrono::system_clock> time_ref = std::chrono::time_point_cast<std::chrono::seconds>(GetDate());
  std::time_t current = std::chrono::system_clock::to_time_t(time_ref);
  auto local = gmtime(&current);
  local->tm_isdst = -1;
  auto utc = mktime(local);
  std::cout << ctime(&utc);
}

TimeStamp const& TimeController::GetDate() const
{
  return sim_date;
}
