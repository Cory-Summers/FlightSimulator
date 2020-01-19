#include "Simulation.h"
#include "Simulation/ObjectFactory.h"
#include "application.h"
#include <fstream>
#include <algorithm>
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
  m_time.SetScale(1e3);
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
  /*object_ptr ptr = m_natural_body[0];
  Physics::StateVector vector;
  if (m_time.CheckLateUpdate()) {
    m_time.DisplayDate();
    vector = ptr->GetVector();
    std::cout << counter << " " << vector << std::endl;
    counter = 0;
  }*/

}

void MVC::Simulation::Main()
{
  while (running) {
    m_time.Start();
    if (m_msg_mutex.try_lock())
    {
      if (!m_msg_queue.empty())
        ReadMessage();
      else
        m_msg_mutex.unlock();
    }
    Update();
    LateUpdate();
    counter += 1;
    m_time.Stop();
  }
}

void MVC::Simulation::SendMessage(SimMessage const& msg)
{
  std::unique_lock<std::mutex> lock(m_msg_mutex);
  m_msg_queue.push(msg);
}

void MVC::Simulation::ReadMessage()
{ 
  SimMessage msg = m_msg_queue.front();
  m_msg_queue.pop();
  m_msg_mutex.unlock();
  DispatchMessage(msg);
}

void MVC::Simulation::DispatchMessage(SimMessage const& msg)
{
  switch (msg.type)
  {
  case MT_TIME:
    switch (msg.hparam)
    {
    case TP_INCR_SP:
      m_time.IncreaseScale();
      break;
    case TP_DECR_SP:
      m_time.DecreaseScale();
      break;
    }
    break;
  }
}

void MVC::Simulation::Cycle(size_t i)
{
  while (i != 0)
  {
    if (m_msg_mutex.try_lock())
    {
      if(!m_msg_queue.empty())
        ReadMessage();
    }
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
  std::sort(m_natural_body.begin(), m_natural_body.end(), [](object_ptr a, object_ptr b) { return a->GetID().id < b->GetID().id;  });
}

MVC::Simulation::object_ptr MVC::Simulation::GetBody(size_t pos)
{
  std::unique_lock<std::mutex> lock(cncr_ctrl->natural_mutex);
  auto temp = m_natural_body[pos];
  return temp;
}
