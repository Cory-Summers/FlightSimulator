// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lexer.h"
#include "lexer-vals.h"
namespace Cyrus {
  typedef struct Lexem {
    double      dval;
    int64_t     ival;
    std::string sval;
  };
};
auto float_act   = [](Cyrus::Lexem val, Cyrus::Lexem rhs) { val.sval = rhs.sval; std::cout << "Float> " << rhs.sval << '\n'; };
auto integer_act = [](Cyrus::Lexem val, Cyrus::Lexem rhs) { val.ival = rhs.ival; std::cout << "Integer> " << rhs.ival << '\n'; };
int main()
{
  std::vector<Cyrus::RegexAction<Cyrus::Lexem>> lexemes = {
    Cyrus::RegexAction<Cyrus::Lexem>(
      std::regex("^[-+]?[0-9]*\.([0-9]*)([eE][-+]?[0-9]+)?[fF]?"), 
      Cyrus::func_decl<Cyrus::Lexem>(float_act),
      FLOATS),
    Cyrus::RegexAction<Cyrus::Lexem>(
      std::regex("^(\"[^\"\\]*(\\.[^\"\\]*)*\")"),
      Cyrus::func_decl<Cyrus::Lexem>(integer_act),
      INTEGER),
    Cyrus::RegexAction<Cyrus::Lexem>(
      std::regex("^\["),
      Cyrus::func_decl<Cyrus::Lexem>(),
      LPCHAR),
    Cyrus::RegexAction<Cyrus::Lexem>(
      std::regex("^[\[\]{}:]"),
      Cyrus::func_decl<Cyrus::Lexem>(),
      LPCHAR),
    Cyrus::RegexAction<Cyrus::Lexem>(
      std::regex("^[ \n\t]"),
      Cyrus::func_decl<Cyrus::Lexem>(),
      NOACT)
    };
  Cyrus::Lexer<Cyrus::Lexem> lexer("planets.cyrus");

  std::cout << "Hello World!\n";
}

