#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "StateElements.h"
#include "Object.h"
#include "IDGenerator.h"
class VectorPool
{

  using unique_lock  = std::unique_lock<std::mutex>;
  using state_ptr    = std::shared_ptr<Physics::StateVector>;
  using st_vector = std::vector<Physics::StateVector>;
public:
  VectorPool();
  state_ptr Assign();
  state_ptr Assign(Physics::StateVector const &);
  state_ptr Assign(Kepler::ObjectBase&);
  Physics::StateVector Read(size_t const &);
  st_vector GetData();
private:
  std::vector<state_ptr> m_pool;
  std::vector<ETS::IDField> m_id_pool;
  std::mutex m_mutex;
  std::condition_variable m_cv;
};

