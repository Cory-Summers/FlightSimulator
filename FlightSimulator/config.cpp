#include "config.h"

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