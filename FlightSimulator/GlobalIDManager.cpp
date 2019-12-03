#include "GlobalIDManager.h"
#include "Object.h"
namespace ETS {
  GlobalIDManager::GlobalIDManager() :
    m_id_fields(),
    m_generator()
  {
  }

  void GlobalIDManager::Add(std::shared_ptr<Kepler::ObjectBase> const& object)
  {
    const IDField id = object->GetID();
    if ((m_id_fields[id.type]).find(id.id_num) != m_id_fields[id.type].end()) throw;
    m_id_fields[id.type].insert(MapField(id.id_num, std::weak_ptr<Kepler::ObjectBase>(object)));
  }

  bool GlobalIDManager::Remove(IDField const& id)
  {
    return m_id_fields[id.type].erase(id.id_num);
  }

  Kepler::ObjectBase* GlobalIDManager::Find(IDField const& id)
  {
    auto temp = m_id_fields[id.type].find(id.id_num);
    if (temp == m_id_fields[id.type].end())
      return nullptr;
    if (temp->second.expired())
      return nullptr;
    return temp->second.lock().get();
  }

  inline GlobalIDManager::ObjectMap& GlobalIDManager::Lookup(IDField const& id)
  {
    return m_id_fields[id.type];
  }
}