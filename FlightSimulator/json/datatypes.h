#pragma once
#ifdef __cplusplus
  #include "cyrus-container.h"
  #include <stack>
  #include <list>
  #include <memory>
  typedef cyrus::Data Data_t;
  typedef cyrus::Container Head_t;
  typedef std::stack<cyrus::Data *> Stack_t;
  using section_ptr = std::shared_ptr<cyrus::Section>;
#else
  typedef void Data_t;
  typedef void Head_t;
  typedef void Stack_t;
#endif