#pragma once
#include <list>
#include <memory>
#include <cstdint>
namespace cyrus{
  class Data;
  using data_ptr = std::shared_ptr<Data>;
  using string_ref = std::string const &;
  class Section;
  enum class DataType
  {
    invalid    = 0,
    string     = 1,
    integer    = 2,
    floatpres  = 3,
    boolean    = 4,
    array      = 5,
    subsection = 6
  };
  struct Data
  { 
    Data();
    Data(string_ref dat) : name(dat) {}
    DataType type;
    DataType const & GetType() const { return type; }
    std::string name;
  };
  struct StringData : public Data
  {
    StringData() : StringData(std::string(), std::string()) {}
    StringData(string_ref id, std::string const & dat) : data(dat) { name = id; type = DataType::string; }
    std::string data;
  };
  struct IntegerData : public Data
  {
    IntegerData() : IntegerData(std::string(), int64_t()) {}
    IntegerData(string_ref id, int64_t const & dat) : data(dat) { name = id; type = DataType::integer; }
    int64_t data;
  };
  struct FloatingData : public Data
  {
    FloatingData() : FloatingData(std::string(), double()) {}
    FloatingData(string_ref id, double const & dat) : data(dat) { name = id;  type = DataType::floatpres; }
    double data;
  };
  struct BooleanData : public Data
  {
    BooleanData() : BooleanData(std::string(), bool()) {}
    BooleanData(string_ref id, bool const & dat) : data(dat) { name = id;  type = DataType::boolean; }
    bool data;
  };
  struct ArrayData : public Data
  {
    ArrayData() {}
    ArrayData(string_ref id, std::list<data_ptr> const & list, DataType dat_type) : data(list), array_type(dat_type) { name = id;  type = DataType::array;}
    std::list<data_ptr> data;
    DataType array_type;
  };
  struct SectionData : public Data
  {
    SectionData() {}
    SectionData(string_ref id, std::shared_ptr<Section> const & ref) : data(ref) { name = id; type = DataType::subsection; }
    std::shared_ptr<Section> data;
  };
};