#include "StarSystem.h"
#define _CRT_SECURE_NO_WARNINGS
#include "planet-class.h"
Celestial::StarSystem::StarSystem() :
  StarSystem(nullptr)
{
}

Celestial::StarSystem::StarSystem(std::shared_ptr<Celestial::Star> star) :
  m_star(star),
  m_natural_body(),
  m_artifical_satellite(),
  m_time(),
  orbit_pool()
{
}

Celestial::StarSystem::StarSystem(std::shared_ptr<Celestial::Star> star, std::initializer_list<object_ptr> const& planets) :
  m_star(star),
  m_natural_body(planets),
  m_artifical_satellite(),
  m_time(),
  orbit_pool()
{
}

void Celestial::StarSystem::AddBody(std::initializer_list<object_ptr> const& list)
{
  for (auto& b : list)
    m_natural_body.emplace_back(b);
}

void Celestial::StarSystem::AddBody(object_ptr const& object)
{
  m_natural_body.emplace_back(object);
}

void Celestial::StarSystem::AddCraft(std::initializer_list<object_ptr> const& list)
{
  for (auto& c : list)
    m_artifical_satellite.emplace_back(c);
}

void Celestial::StarSystem::AddCraft(object_ptr const& craft)
{
  m_artifical_satellite.emplace_back(craft);
}

void Celestial::StarSystem::Initialize()
{
  m_time.SetScale(1e7);
  for (auto& b : m_natural_body)
    b->Initialize();
  for (auto& s : m_artifical_satellite)
    s->Initialize();
  m_star->Initialize();
}

void Celestial::StarSystem::Update()
{
  double dt = m_time.GetCount();
  /*
  for (auto& b : m_natural_body)
    orbit_pool.Add(&Kepler::CalculateMovement, (Kepler::ObjectBase *)b.get(), dt);
  orbit_pool.WaitFinished();
  */
  ///*
  {
    std::unique_lock<std::mutex> lock(m_natural_mutex);
    m_cv_natural.wait(lock, [this]() {return true; });
      for (auto& b : m_natural_body)
        b->Update(dt);
    m_cv_natural.notify_one();
  }
  //*/
  for (auto& s : m_artifical_satellite)
    s->Update(dt);
  m_star->Update(dt);
}
  
void Celestial::StarSystem::MainLoop()
{
  while (running) {
    m_time.Start();
    Update();
    LateUpdate();
    counter += 1;
    m_time.Stop();
  }
}

void Celestial::StarSystem::LateUpdate()
{
  object_ptr ptr = m_natural_body[1];
  Physics::StateVector vector;
  if (m_time.CheckLateUpdate()) {
    DisplayDate();
    vector = ptr->GetVector();
    std::cout << counter<< " " << vector << std::endl;
    counter = 0;
  }
}

void Celestial::StarSystem::Cycle(size_t i)
{
  Update();
  LateUpdate();
  counter += 1;
}

void Celestial::StarSystem::SetStar(std::shared_ptr<Celestial::Star> const & star)
{
  this->m_star = star;
  for (auto& b : m_natural_body) {
    b->SetParent(m_star.get());
  }
  for (auto& c : m_artifical_satellite) {
    c->SetParent(m_star.get());
  }
}

Kepler::ObjectBase* Celestial::StarSystem::GetObjectByName(std::string const&)
{
  return nullptr;
}

void Celestial::StarSystem::DisplayDate()
{
  std::chrono::time_point<std::chrono::system_clock> time_ref = std::chrono::time_point_cast<std::chrono::seconds>(m_time.GetDate());
  std::time_t current = std::chrono::system_clock::to_time_t(time_ref);
  auto local = *std::gmtime(&current);
  local.tm_isdst = -1;
  auto utc = std::mktime(&local);
  std::cout << std::ctime(&utc);
}
