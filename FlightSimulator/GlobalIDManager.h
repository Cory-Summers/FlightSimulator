#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <memory>
#include <map>
#include "IDGenerator.h"
enum class TypeTag {
  PlayerMade = 0,
  Planet = 1
};
namespace Kepler {
  class ObjectBase;
}
namespace ETS {
  class GlobalIDManager
  {
    using MapField  = std::pair<uint64_t, std::weak_ptr<Kepler::ObjectBase>>;
    using ObjectMap = std::map<uint64_t, std::weak_ptr<Kepler::ObjectBase>>;
  public:
    GlobalIDManager();
    void Add(std::shared_ptr<Kepler::ObjectBase> const&);
    bool Remove(ETS::IDField const&);
    Kepler::ObjectBase* Find(ETS::IDField const&);
    inline void LoadIDs(std::array<uint64_t, 32> const& vals) { m_generator.LoadValues(vals); }
  protected:
    inline ObjectMap& Lookup(ETS::IDField const&);
  private:
    std::array<std::map<uint64_t, std::weak_ptr<Kepler::ObjectBase>>, 32> m_id_fields;
    ETS::IDGenerator m_generator;
  };
};

