#include "crc32-const.h"
#include <iostream>
uint32_t CRC32RT(std::string const& str){
  uint32_t hash = 0xFFFFFFFF;
  for (const char& c : str)
  {
    hash = (hash >> 8) ^ crc_table[(hash & 0xff) ^ static_cast<uint8_t>(c)];
  }
  return ~hash;
}