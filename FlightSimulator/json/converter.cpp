#include "converter.h"
#include <sstream>

double _ConverterD(char *);
int64_t _ConverterLL(char *);

extern "C" double ConverterD(char * str) { return _ConverterD(str); }
extern "C" int64_t ConverterLL(char * str) { return _ConverterLL(str); }
double _ConverterD(char * in)
{
  std::stringstream data(in);
  double out;
  data >> out;
  return out;
}
int64_t _ConverterLL(char * in){
  std::stringstream data(in);
  int64_t out;
  data >> out;
  return out;
}