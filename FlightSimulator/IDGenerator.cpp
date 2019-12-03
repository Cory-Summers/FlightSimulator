#include "IDGenerator.h"
namespace ETS {
  IDGenerator::IDGenerator() :
    m_global_id()
  {
    m_global_id.fill(1);
  }

  void IDGenerator::LoadValues(std::array<uint64_t, 32> const& values)
  {
    m_global_id = values;
  }
};