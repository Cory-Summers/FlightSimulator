#include "VectorPool.h"

using state_ptr = std::shared_ptr<Physics::StateVector>;
using lock_guard = std::lock_guard<std::mutex>;
using unique_lock = std::unique_lock<std::mutex>;
using st_vector = std::vector<Physics::StateVector>;
VectorPool::VectorPool()
{
}

state_ptr VectorPool::Assign()
{
  return Assign(Physics::StateVector());
}

state_ptr VectorPool::Assign(Physics::StateVector const & vector)
{
  lock_guard lock(m_mutex);
  m_pool.push_back(std::make_shared<Physics::StateVector>(vector));
  state_ptr temp = m_pool.back();
  m_cv.notify_one();
  return temp;
}

state_ptr VectorPool::Assign(Kepler::ObjectBase& obj) 
{
  auto variable = Assign();
  obj.SetVector(*variable);
  return variable;
}

Physics::StateVector VectorPool::Read(size_t const & index)
{
  lock_guard lock(m_mutex);
  if (index >= m_pool.size())
    throw std::out_of_range("VectorPool::Read() : index out of range");
  return *(m_pool[index].get());
}

st_vector VectorPool::GetData()
{
  st_vector ret_vect(m_pool.size());
  lock_guard lock(m_mutex);
  return ret_vect;
}

