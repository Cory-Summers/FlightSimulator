// FlightSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "application.h"

int main()
{
  Application _application;
  _application.Initialize();
  _application.Loop();
  return 0;
}
