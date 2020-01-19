#pragma once
#include <memory>
#include <vector>
#include <initializer_list>
#include <queue>

#include "Simulation/Star.h"
#include "Simulation/TimeControl.h"
#include "ConcurrencyController.h"
#include "Simulation/planet-class.h"
#include "Utility/SimMessage.h"
namespace MVC {
  namespace Render {
    class Renderer;
  }
  class Simulation
  {
    using object_ptr = std::shared_ptr<Kepler::ObjectBase>;
    using star_ptr = std::shared_ptr<Kepler::Star>;
    friend class Render::Renderer;
  public:
    Simulation();
    void Initialize();
    void Update();
    void LateUpdate();
    void Main();
    void SendMessage(SimMessage const &);
    inline void ReadMessage();
    void DispatchMessage(SimMessage const &);
    void Cycle(size_t i = 1);
    void AddBody(object_ptr const&);
    void BuildFromFile(std::string const&);
    object_ptr GetBody(size_t pos);
    star_ptr GetStar() const { return m_star; }
    TimeController& GetTime() { return m_time; }
    void SetCncrCtrl(ConcurrencyController& obj) { cncr_ctrl = &obj; }
    std::vector<object_ptr> m_natural_body;

  private:
    std::vector<object_ptr> m_art_body;
    std::shared_ptr<Kepler::Star> m_star;
    TimeController m_time;
    ConcurrencyController * cncr_ctrl = nullptr;
    size_t counter = 0;
    bool running = 1;
    std::mutex m_msg_mutex;
    std::queue<SimMessage> m_msg_queue;
  };
};

