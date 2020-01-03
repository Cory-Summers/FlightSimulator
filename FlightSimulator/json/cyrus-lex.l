%{

  #ifdef __cplusplus 
    extern "C" {
  #endif
#define YY_DECL int yylex()
#include "cyrus-reader.tab.hpp"
#ifdef __cplusplus
  }
#endif
#define _CRT_NONSTDC_NO_DEPRECATE
#include "datatypes.h"
#include "converter.h"
#include <stdio.h>
#include <string.h>
#define  YY_NO_UNISTD_H
#ifndef _CRT_SECURE_NO_WARNINGS
  #define _CRT_SECURE_NO_WARNINGS
#endif

int scope = 0;
void ScopeShift()
{
  for(int i = 0; i < scope; i++)
    printf("\t");
}
typedef void uData;

%}
%option never-interactive
FLOAT_NUM [-+]?[0-9]*\.([0-9]*)([eE][-+]?[0-9]+)?[fF]?
STRING    (\"[^\"\\]*(\\.[^\"\\]*)*\")
BREAKS [,:$]
INTEGERS [-+]?[0-9]*
SCOPE [\[\]{}]
%%
{FLOAT_NUM} {
  yylval.dval = ConverterD(yytext);
  return FLOAT;
}
{INTEGERS} {
  yylval.ival = ConverterLL(yytext);
  return INTEGER;
}
{STRING} {
  char * str = malloc(sizeof(char) *(strlen(yytext) + 1));
  strcpy(str, yytext);
  str[strlen(yytext) + 1] = '\0';
  yylval.sval = str;
  return STRING;
}
{BREAKS} { return *yytext; }

{SCOPE} { return *yytext; }
[ \t\n]+ ;
%%
int yywrap() { return 1;}