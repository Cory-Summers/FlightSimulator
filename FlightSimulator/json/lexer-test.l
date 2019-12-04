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
FLOAT_NUM [-+]?[0-9]*\.([0-9]*)([eE][-+]?[0-9]+)?[f]?
STRING    (\"[^\"\\]*(\\.[^\"\\]*)*\")
NAME (\"[^\"\\]*(\\.[^\"\\]*)*\":)
BREAKS [,:]
INTEGERS [-+]?[\d]*
SCOPE [\[\]{}]
%%
{FLOAT_NUM} {
  double val = ConverterD(yytext);
  printf("FLOAT> %s : %f\n", yytext, val);
}
{INTEGERS} {
  ScopeShift();
  printf("INTEGER> %s\n", yytext);
}
{STRING} {
  ScopeShift();
  printf("STRING> %s\n", yytext);
}
{NAME} {
  ScopeShift();
  printf("NAME> %s\n", yytext);
}
{BREAKS} {
  ScopeShift();
  printf("BREAK> %c\n", *yytext); }

{SCOPE} { printf("SCOPE> %c\n", *yytext); }
[ \t\n]+ ;
%%
int yywrap() { return 1;}
int main(int argc, char **argv)
{
	if (argc > 1)
		yyin = fopen(argv[1], "r");
	else
		yyin = stdin;
	if(yyin != NULL){
		yylex();
	} else {
		printf("Failure to open file \"%s\"!\n", argv[1]);
	}
}
