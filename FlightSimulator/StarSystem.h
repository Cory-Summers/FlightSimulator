#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Star.h"
#include "TimeControl.h"
#include <vector>
#include <memory>
#include <initializer_list>
#include <map>
#include "ThreadPool.h"

namespace Celestial {
  class StarSystem
  {
    using object_ptr = std::shared_ptr<Kepler::ObjectBase>;
  public:
    StarSystem();
    StarSystem(std::shared_ptr<Kepler::Star>);
    StarSystem(std::shared_ptr<Kepler::Star>, std::initializer_list<object_ptr> const &);
    void AddBody(std::initializer_list<object_ptr> const &);
    void AddBody(object_ptr const&);
    void AddCraft(std::initializer_list<object_ptr> const&);
    void AddCraft(object_ptr const&);
    void Initialize();
    void Update();
    void MainLoop();
    void LateUpdate();
    void Cycle(size_t i = 1);
    TimeController& GetTimeController() { return m_time; }
    void SetStar(std::shared_ptr<Kepler::Star> const & star);
    Kepler::ObjectBase* GetObjectByName(std::string const&);

    Kepler::Star& GetStar() { return *m_star; }
  protected:
    std::condition_variable m_cv_star;
    std::condition_variable m_cv_natural;
    std::mutex m_star_mutex;
    std::mutex m_natural_mutex;
    void DisplayDate();
    std::vector<object_ptr> m_natural_body;
    std::vector<object_ptr> m_artifical_satellite;
    std::shared_ptr<Kepler::Star> m_star;
    TimeController m_time;
    ThreadPool<void, Kepler::ObjectBase *, double> orbit_pool;
    bool running = 1;
    uint64_t counter = 0;
  };
}
