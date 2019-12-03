#pragma once
#include "SFML/Graphics.hpp"
#include "StarSystem.h"
namespace Application {
  class ViewPort
  {
  public:
    ViewPort();
    ViewPort(Celestial::StarSystem&);
    void Initialize();
    void Run();
    void MainLoop();
    ~ViewPort();
  protected:
    void Render();
    void Draw();
    void Poll();
    void CreateSpheres();
    void UpdateSpheres();
    void KeyboardEvent();
    void Zoom();
    sf::RenderWindow* m_window;
    sf::View* m_view;
    sf::Event        m_event_handler;
    Celestial::StarSystem* m_system;
    TimeController* m_time;
    std::vector<sf::Shape*> natural_objects;
    std::vector<sf::CircleShape *> natural_sphere;
    std::vector<Physics::StateVector*> natural_vectors;
  private:
    void CreateNaturalOrbit(Kepler::ObjectBase &);
    bool running;
    double scale = 7400e6;
  };
  const sf::Color background_color = sf::Color(32, 32, 32, 255);
};

