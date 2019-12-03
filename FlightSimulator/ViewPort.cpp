#include "ViewPort.h"
#include <Windows.h>
#include "kepler-physics.h"
const sf::Color TRANSPARENT_C = sf::Color(0, 0, 0, 0);
Application::ViewPort::ViewPort() :
  m_window(new sf::RenderWindow),
  m_view(new sf::View()),
  m_system(nullptr),
  running(true)
{
}

Application::ViewPort::ViewPort(Celestial::StarSystem& system) :
  m_window(new sf::RenderWindow),
  m_view(new sf::View()),
  m_system(&system)
{
}

void Application::ViewPort::Initialize()
{

  SetProcessDPIAware();
  m_window->create(sf::VideoMode(1980, 1080), "System Viewer");
  m_view->setSize(2880e0, 1440e0);
  m_view->setCenter(0,0);
  sf::RectangleShape * rect = new sf::RectangleShape(sf::Vector2f(2000, 2000));
  rect->setPosition(-1000, -1000);
  rect->setFillColor(sf::Color(0,0,0x80));
  natural_objects.push_back(rect);
  m_window->setView(*m_view);
  m_window->setFramerateLimit(204);
  m_system->Initialize();
  CreateSpheres();
  m_time = &(m_system->GetTimeController());
  //for(auto & n : m_system->m_natural_body)
    //CreateNaturalOrbit(*n);
}

void Application::ViewPort::Run()
{
  m_system->MainLoop();
} 

void Application::ViewPort::Render()
{
  m_window->clear(background_color);
  UpdateSpheres();
  Draw();
  m_window->display();
}

void Application::ViewPort::Draw()
{

    for (auto& n : natural_objects)
      m_window->draw(*n);
    for (auto& p : natural_sphere)
      m_window->draw(*p);
}

void Application::ViewPort::Poll()
{
  while (m_window->pollEvent(m_event_handler)) {
    switch (m_event_handler.type) {
    case sf::Event::Closed:
      m_window->close();
      break;
    case sf::Event::Resized:
      m_window->setView(*m_view);
      break;
    case sf::Event::MouseWheelMoved:
      Zoom();
      break; 
    case sf::Event::KeyPressed:
      KeyboardEvent();
      break;
    }
    
  }
}

void Application::ViewPort::CreateSpheres()
{
  for (auto& c : m_system->m_natural_body)
  {
    natural_sphere.push_back(new sf::CircleShape(5));
    natural_vectors.push_back(&(c->m_st_vector));
  }
}

void Application::ViewPort::UpdateSpheres()
{
  const float width = (m_view->getSize().y);
  sf::Vector2f position;

  {
    std::unique_lock<std::mutex> lock(m_system->m_natural_mutex);
    m_system->m_cv_natural.wait(lock, []() {return true; });
    for (int i = 0; i < m_system->m_natural_body.size(); i++)
    {
      position = { (float)(width * natural_vectors[i]->p.x / scale), 
                   (float)(width * -natural_vectors[i]->p.y / scale) };
      natural_sphere[i]->setPosition(position);
    }
  }
}

void Application::ViewPort::KeyboardEvent()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    std::cout << "Left\n";
    m_view->move(-10, 0);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    std::cout << "Right\n";
    m_view->move(10, 0);
  } 
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    std::cout << "Up\n";
    m_view->move(0, -10);
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    std::cout << "Left\n";
    m_view->move(0, 10);
  }
}

void Application::ViewPort::Zoom()
{
  m_view->zoom(1.0f + .1f * m_event_handler.mouseWheel.delta);
  m_window->setView(*m_view);
}

void Application::ViewPort::CreateNaturalOrbit(Kepler::ObjectBase& orbit)
{
  Physics::OrbitState state(orbit.GetVector(), orbit.GetParent()->GetMu());
  std::cout << state.eccentricity << '\n';
  sf::CircleShape* temp = new sf::CircleShape((m_window->getSize().y) * (state.semi_major * .5 / scale), 32);
  temp->setFillColor(sf::Color::Transparent);
  temp->setOutlineColor(sf::Color::White);
  temp->setScale(sf::Vector2f(1.0f, 1.0f - static_cast<float>(state.eccentricity)));
  temp->setOutlineThickness(1.0f);
  temp->setOrigin(temp->getGlobalBounds().width / 2, temp->getGlobalBounds().height / 2);
  temp->setPosition(0, 0);
  natural_objects.push_back(temp);
}

void Application::ViewPort::MainLoop()
{
  std::thread sim_loop(&Celestial::StarSystem::MainLoop, m_system);
  while (m_window->isOpen()) {
    Poll();
    Render();
  }
}

Application::ViewPort::~ViewPort()
{
}
