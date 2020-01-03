// FlightSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include <iostream>
#include <string>
#include <vector>
#include "Star.h"
#include "TimeControl.h"
#include "planet-class.h"
#include "StarSystem.h"
#include "ViewPort.h"
#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>
#include "application.h"

int main()
{
  Application _application;
  _application.Initialize();
  _application.Loop();
  return 0;
}
