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
  struct Graphics
  {
    unsigned int fps_limit = 60;
  };
  struct Master
  {
    Master();
    Master(std::string const&);
    Window   window;
    Graphics graphics;
  };
  Window   LoadWindowConfig(std::string file_name);
  Graphics LoadGraphicConfig(std::string file_name);
}