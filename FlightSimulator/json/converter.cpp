#include "converter.h"
#include <sstream>
#include <algorithm>
#include <string>
double _ConverterD(char *);
int64_t _ConverterLL(char *);
char * _RemoveQuotes(char * str);

extern "C" double ConverterD(char * str) { return _ConverterD(str); }
extern "C" int64_t ConverterLL(char * str) { return _ConverterLL(str); }
extern "C" char * RemoveQuotes(char * str) { return _RemoveQuotes(str); }
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
char * _RemoveQuotes(char * str)
{
  std::string s;
  s = str;
  char * sub_string = nullptr;
  s.erase(
    std::remove( s.begin(), s.end(), '\"' ),
    s.end()
    );
  free(str);
  sub_string = (char *)malloc(sizeof(char) * (s.length() + 1));
  s.copy(sub_string, s.size() + 1);
  sub_string[s.size()] = '\0';
  return sub_string;
}