#include <iostream>
#include <immintrin.h>
#include <string>
#include <vector>
int main()
{
  std::vector<std::string> names = { "star", "planet", "moon", "spacecraft", "misc", "debris" };
  std::vector<unsigned int> output;
  for(auto & n : names ){
    unsigned int val = 0;
    for(char & c : n)
      val = _mm_crc32_u8(val, c);
    output.push_back(val);
  }
  for(auto & o : output)
  {
    printf("%0x ", o);
  }
  std::cout << '\n';
}