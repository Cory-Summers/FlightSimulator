#include "Simulation.h"
#include "ObjectFactory.h"
#include <fstream>
MVC::Simulation::Simulation()
  : m_natural_body(),
    m_art_body(),
    m_star(),
    m_time(1.0)
{
}

void MVC::Simulation::Initialize()
{
  for (auto& b : m_natural_body)
    b->Initialize();
  for (auto& s : m_art_body)
    s->Initialize();
  m_star->Initialize();
}

void MVC::Simulation::Update()
{
  double dt = m_time.GetCount();
  {
    std::unique_lock<std::mutex> lock(cncr_ctrl->natural_mutex);
    cncr_ctrl->cv_natural.wait(lock, [this]() {return true; });
    for (auto& b : m_natural_body)
      b->Update(dt);
    cncr_ctrl->cv_natural.notify_one();
  }
  for (auto& s : m_art_body)
    s->Update(dt);
  m_star->Update(dt);
}

void MVC::Simulation::LateUpdate()
{
  object_ptr ptr = m_natural_body[0];
  Physics::StateVector vector;
  if (m_time.CheckLateUpdate()) {
    m_time.DisplayDate();
    vector = ptr->GetVector();
    std::cout << counter << " " << vector << std::endl;
    counter = 0;
  }

}

void MVC::Simulation::Main()
{
  while (running) {
    m_time.Start();
    Update();
    LateUpdate();
    counter += 1;
    m_time.Stop();
  }
}

void MVC::Simulation::Cycle(size_t i)
{
  while (i != 0)
  {
    Update();
    LateUpdate();
    ++counter;
    --i;
  }

}

void MVC::Simulation::AddBody(object_ptr const& object)
{
  m_natural_body.emplace_back(object);
}

void MVC::Simulation::BuildFromFile(std::string const& file_name)
{
  std::ifstream json_file(file_name);
  JSON j_data   = JSON::parse(json_file);
  JSON j_star   = j_data["Star"];
  JSON j_planet = j_data["Planets"];
  m_star = Kepler::ObjectFactory::StarFactory(j_star);
  for (auto p : j_planet)
  {
    Kepler::planet_ptr temp = Kepler::ObjectFactory::PlanetFactory(p);
    temp->SetParent(m_star.get());
    m_natural_body.push_back(temp);
  }

}
