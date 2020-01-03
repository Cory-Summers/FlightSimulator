#pragma once
#include <array>
#include <string>
struct PlanetData
{
  std::string name;
  std::array<double,6> state;
  double mass;
  double radius;
  double mu;
};