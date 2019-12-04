%{
#include "cyrus-reader.tab.hpp"
#include <iostream>
#include <string>
#include <sstream>
std::stringstream converter;
%}
BREAKS "\{"|"\}"|","|"\""|":"
INTEGERS [-+]?[\d]*

%option c++
%%
([0-9]+|([0-9]*\.[0-9]+)([eE][+-]?[0-9]+)?) {
  converter << yytext;
  converter >> yylval.dval; 
  return FLOAT;
}

INTEGERS {
  converter << yytext;
  converter >> yylval.ival;
  return INTEGER;
}
("[^\"\\]*(\\.[^\"\\]*)*") {
  if(string != nullptr)
  {
    delete yylval.string;
  }
  yylval.stringval = new std::string(yytext);
  return STRING;
}
BREAKS { return *yytext; }
[ \t\n] ;

"PLANETS" |
"STAR" {
  yylval.stringval = new std::string(yytext);
  return SECTION_ID; 
}

%%
int yywrap() { return 1;}
