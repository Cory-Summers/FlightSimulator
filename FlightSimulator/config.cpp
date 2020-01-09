#include "config.h"

cfg::Master::Master()
{
}

cfg::Master::Master(std::string const& file_name)
  : window(LoadWindowConfig(file_name))
  , graphics(LoadGraphicConfig(file_name))
{
}

cfg::Window cfg::LoadWindowConfig(std::string file_name)
{
  std::ifstream file;
  JSON json;
  cfg::Window temp;
  try {
    file.open(file_name);
  }
  catch (const std::ifstream::failure & e) {
    std::cout << "Failure to Open Config File - " << file_name << "!\n";
  }
  json = JSON::parse(file);
  auto win = json["window"];
  for (auto& c : win)
    std::cout << c << ' ';
  temp = {
    win["width"].get<uint32_t>(),
    win["height"].get<uint32_t>(),
    win["attributes"].get<uint32_t>(),
    win["fov"].get<float>()
  };
  file.close();
  return temp;
}

cfg::Graphics cfg::LoadGraphicConfig(std::string file_name)
{
  std::ifstream file;
  Graphics temp;
  JSON json;
  try {
    file.open(file_name);
  }
  catch (const std::ifstream::failure & e) {
    std::cout << "Failure to Open Config File - " << file_name << "!\n";
  }
  json = JSON::parse(file);
  auto graphic = json["graphics"];
  temp = { graphic["fps"].get<unsigned int>() };
  return temp;
}
