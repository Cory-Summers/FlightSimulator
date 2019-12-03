#pragma once
#include "Object.h"
#include "GlobalIDManager.h"
#include <memory>
#include "planet-class.h"
/*
namespace Kepler {
  class ObjectFactory
  {
  public:
    template<typename T, typename ... TArgs>
    std::shared_ptr<ObjectBase> Create(ETS::GlobalIDManager &, TArgs ... args);

  protected:

  };
  template<typename T, typename ...TArgs>
  inline std::shared_ptr<ObjectBase> ObjectFactory::Create(ETS::GlobalIDManager & , TArgs ...args)
  {
    std::shared_ptr<ObjectBase> temp_object;
    temp_object = std::make_shared<T>(TArgs);
    temp_object->Initialize();
    return temp_object;
  }

}
template<typename T, typename ... TArgs>
inline std::shared_ptr<Kepler::ObjectBase> Kepler::ObjectFactory::Create<Kepler::Planet, TArgs...>(ETS::GlobalIDManager&, TArgs ...args) {
  std::shared_ptr<Kepler::Planet> temp_planet;
  temp_planet = std::make_shared<Kepler::Planet>(TArgs);
  return temp_planet;
}
*/