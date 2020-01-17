#pragma once
#include <chrono>
#include <iostream>
#include <cstdint>
#include "StateElements.h"
#include "GlobalIDManager.h"
namespace Kepler {
  enum class ObjectType
  {
    na = 0,
    star = 1,
    planet = 2,
    moon = 3,
    craft = 4
  };
  class ObjectBase
  {
  public:
    ObjectBase();
    ObjectBase(std::string const &, Physics::StateVector const&, double const &);
    virtual void Initialize() = 0;
    virtual void Update(double const dt) = 0;
    std::string const& GetName() const       { return m_name; }
    virtual void SetParent(ObjectBase * obj) { m_parent_body = obj; }
    virtual ObjectBase* GetParent() const    { return m_parent_body; }
    virtual ~ObjectBase() {}
    virtual Physics::StateVector const& GetVector() const { return m_st_vector; }
    virtual void SetVector(Physics::StateVector const& vector) { m_st_vector = vector; }
    virtual Physics::RotationVector const& GetRotation() const { return m_rotation; }
    double const& GetRadius() const noexcept { return m_radius; }
    double const& GetMu() const { return mu; }
    ETS::IDField const& GetID() const { return m_id; }
    virtual ObjectType GetType() const = 0;
  protected:
    virtual void CalculateRotation(double const &);
    void CalculateMovement(double const&);
    std::string             m_name;
    Physics::StateVector    m_st_vector;
    Physics::RotationVector m_rotation; //Legacy needs to be replaced
    ETS::IDField            m_id;
    double   m_mass; //kg
    double   m_radius; //km
    ObjectBase* m_parent_body;
    double   mu;
  };
  void CalculateMovement(Kepler::ObjectBase* obj, double const& dt);
};

