#pragma once
#include <memory>
#include <vector>
#include <initializer_list>
#include "Star.h"
#include "TimeControl.h"
#include "ConcurrencyController.h"
#include "planet-class.h"
namespace MVC {
  class Simulation
  {
    using object_ptr = std::shared_ptr<Kepler::ObjectBase>;
    using star_ptr = std::shared_ptr<Kepler::Star>;
  public:
    Simulation();
    void Initialize();
    void Update();
    void LateUpdate();
    void Main();
    void Cycle(size_t i = 1);
    void AddBody(object_ptr const&);
    void BuildFromFile(std::string const&);
    Kepler::Planet GetBody(size_t pos);
    star_ptr GetStar() const { return m_star; }
    void SetCncrCtrl(ConcurrencyController& obj) { cncr_ctrl = &obj; }

  private:
    std::vector<object_ptr> m_natural_body;
    std::vector<object_ptr> m_art_body;
    std::shared_ptr<Kepler::Star> m_star;
    TimeController m_time;
    ConcurrencyController * cncr_ctrl = nullptr;
    size_t counter = 0;
    bool running = 1;
  };
};

