#pragma once
#include <cstdint>
#include <array>
namespace ETS {
  union IDField {
    struct {
      uint16_t type : 6;
      uint64_t id_num : 58;
    };
    uint64_t id;
  };
  class IDGenerator
  {
  public:
    IDGenerator();
    const uint64_t GetGlobalID(IDField const& id) {
      return m_global_id[id.type]++;
    }
    void LoadValues(std::array<uint64_t, 32> const&);
  protected:
    std::array<uint64_t, 32> m_global_id;
  };
};