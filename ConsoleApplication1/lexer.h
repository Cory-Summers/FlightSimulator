#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <stack>
#include <string>
#include <vector>
#include <cstdint>
#include <functional>
#include <algorithm>
namespace Cyrus {
  template<typename lval_t>
  using func_decl = std::function<void(lval_t, lval_t)>;
  using shared_str = std::shared_ptr<std::string>;

  template<typename lval_t>
  struct RegexAction {
    RegexAction();
    RegexAction(std::regex, std::function<void(lval_t, lval_t)>);
    RegexAction(std::regex, std::function<void(lval_t, lval_t)>, int64_t);

    std::regex    pattern;
    std::function<void(lval_t, lval_t)> action;
    int64_t value;
  protected:
    bool assigned;
  };
  template<typename lval_t>
  struct TOKEN {
    int64_t type;
    lval_t  lval;
  };
  template<typename lval_t>
  class Lexer
  {
    using TOKEN_T = TOKEN<lval_t>;
  public:
    Lexer();
    Lexer(std::string const&);
    Lexer(std::ifstream&);
    virtual void Compile(std::vector<Cyrus::RegexAction<lval_t>> &);
    virtual TOKEN_T Read();
    ~Lexer() {}
  private:
    shared_str CopyFileContents();

    TOKEN_T m_currentToken;
    std::shared_ptr<std::ifstream> m_inFile;
    std::vector<RegexAction<lval_t>> m_regToken;
    std::shared_ptr<std::string> m_filestr;
    struct Flags
    {
      int8_t compiled : 1;
    };
  };

  template<typename lval_t>
  inline Lexer<lval_t>::Lexer()
  {
  }

  template<typename lval_t>
  inline Lexer<lval_t>::Lexer(std::string const& file_name)
    : m_inFile(std::make_shared<std::ifstream>(file_name.c_str())),
      m_filestr(CopyFileContents())

  {
  }

  template<typename lval_t>
  inline Lexer<lval_t>::Lexer(std::ifstream& file)
    : m_inFile(std::make_shared(file)),
    m_filestr(CopyFileContents())
  {
  }

  template<typename lval_t>
  inline void Lexer<lval_t>::Compile(std::vector<Cyrus::RegexAction<lval_t>>& token_types)
  {
    m_regToken = token_types;
  }
  template<typename lval_t>
  inline TOKEN<lval_t> Lexer<lval_t>::Read()
  {
    return TOKEN<lval_t>();
  }

  template<typename lval_t>
  inline shared_str Lexer<lval_t>::CopyFileContents()
  {
    shared_str temp_str = std::make_shared<std::string>();
    m_inFile->seekg(0, std::ios::end);
    temp_str->reserve(m_inFile->tellg());
    m_inFile->seekg(0, std::ios::beg);
    temp_str->assign((std::istreambuf_iterator<char>(*(m_inFile.get()))),
      std::istreambuf_iterator<char>());
    return shared_str();
  }

  template<typename lval_t>
  inline RegexAction<lval_t>::RegexAction()
    : pattern(),
    action(),
    value(),
    assigned(false)
  {
  }

  template<typename lval_t>
  inline RegexAction<lval_t>::RegexAction(std::regex reg, std::function<void(lval_t, lval_t)> func)
    : pattern(reg),
      action(func),
      assigned(false)
  {
  }

  template<typename lval_t>
  inline RegexAction<lval_t>::RegexAction(std::regex reg, std::function<void(lval_t, lval_t)> func, int64_t val)
    : pattern(reg),
    action(func),
    value(val),
    assigned(true)
  {
  }

};