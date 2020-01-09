#pragma once
#include "Timer.h"
class FrameTimer :
  public Timer
{
public:
  FrameTimer(unsigned int interval = 1e4);
  virtual TimeDelta const& Stop() override;
private:
  TimeDelta frame_interval;
};

