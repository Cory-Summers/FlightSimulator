#pragma once
#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#define CONFIG_FILE "config.json"
namespace cfg {
  using JSON = nlohmann::json;
  struct Window
  {
    uint32_t x;
    uint32_t y;
    uint32_t attr;
    float fov;
  };
  Window LoadWindowConfig(std::string file_name);
}