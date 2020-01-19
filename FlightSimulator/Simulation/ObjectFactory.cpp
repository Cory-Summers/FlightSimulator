#include "ObjectFactory.h"
#include "../Utility/crc32-const.h"
#include <array>
using namespace Kepler;
/*
const std::array<uint32_t,8> name_table = {
  CRC32_STR("name"),
  CRC32_STR("position"),
  CRC32_STR("velocity"),
  CRC32_STR("radius"),
  CRC32_STR("mass"),
  CRC32_STR("mu"),
  CRC32_STR("ID"),
  CRC32_STR("moon")
};*/
template<typename T, size_t size>
std::array<T, size> GetJSONArray(JSON::value_type& arr)
{
  std::array<T, size> data;
  for (size_t i = 0; i < size; ++i)
  {
    data[i] = arr.at(i).get<double>();
  }
  return data;
}
star_ptr Kepler::ObjectFactory::StarFactory(JSON& data)
{
  
  star_ptr temp = std::make_shared<Kepler::Star>();
  for (auto it = data.begin(); it != data.end(); ++it) 
  {
    switch (CRC32RT(it.key()))
    {
      case (uint32_t)CRC32("name"):
        temp->m_name = it.value().get<std::string>();
        break;
      case (uint32_t)CRC32("position"):
        temp->m_st_vector.p = Vector3D(GetJSONArray<double, 3>(it.value()));
        break;
      case (uint32_t)CRC32("velocity"):
        temp->m_st_vector.v = Vector3D(GetJSONArray<double, 3>(it.value()));
        break;
      case (uint32_t)CRC32("radius"):
        temp->m_radius = it.value().get<double>();
        break;
      case (uint32_t)CRC32("mass"):
        temp->m_mass = it.value().get<double>();
        break;
      case (uint32_t)CRC32("mu"):
        temp->mu = it.value().get<double>();
        break;
      case CRC32("ID"):
        temp->m_id.id = it.value().get<uint64_t>();
        break;
      default:
        std::cout << "Invalid JSON data> " << it.key() << " " << it.value() << "\n";
        break;
    }
  }
  return temp;
}
planet_ptr Kepler::ObjectFactory::PlanetFactory(JSON& data)
{
  planet_ptr temp = std::make_shared<Kepler::Planet>();
  for (auto it = data.begin(); it != data.end(); ++it)
  {
    switch (CRC32RT(it.key()))
    {
    case CRC32("name"):
      temp->m_name = it.value().get<std::string>();
      break;
    case CRC32("position"):
      temp->m_st_vector.p = Vector3D(GetJSONArray<double, 3>(it.value()));
      break;
    case CRC32("velocity"):
      temp->m_st_vector.v = Vector3D(GetJSONArray<double, 3>(it.value()));
      break;
    case CRC32("radius"):
      temp->m_radius = it.value().get<double>();
      break;
    case CRC32("mass"):
      temp->m_mass = it.value().get<double>();
      break;
    case CRC32("mu"):
      temp->mu = it.value().get<double>();
      break;
    case CRC32("ID"):
      temp->m_id.id = it.value().get<uint64_t>();
      break;
    default:
      std::cout << "Invalid JSON data> " << it.key() << " " << it.value() << "\n";
      break;
    }
  }
  return temp;
}
