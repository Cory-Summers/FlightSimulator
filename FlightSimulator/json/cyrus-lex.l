%{
#include "converter.h"
#include <stdio.h>
#include <string.h>
int scope = 0;
void ScopeShift()
{
  for(int i = 0; i < scope; i++)
    printf("\t");
}
%}
FLOAT_NUM [-+]?[0-9]*\.([0-9]*)([eE][-+]?[0-9]+)?[fF]?
STRING    (\"[^\"\\]*(\\.[^\"\\]*)*\")
BREAKS [,:]
INTEGERS [-+]?[\d]*
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
  yylval.sval = strdup(yytext);
  return STRING;
}
{BREAKS} { return *yytext; }

{SCOPE} { return *yytext; }
[ \t\n]+ ;
%%
int yywrap() { return 1;}