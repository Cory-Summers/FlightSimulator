// FlightSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _ENABLE_EXTENDED_ALIGNED_STORAGE
#include <iostream>
#include <string>
#include <vector>
#include "Star.h"
#include "TimeControl.h"
#include "planet-class.h"
#include "StarSystem.h"
#include "ViewPort.h"
#include <memory>
void InitializeSolarSystem(Celestial::StarSystem ** system);
int main()
{
  Application::ViewPort* port;
  Celestial::StarSystem * solar_system;
  InitializeSolarSystem(&solar_system);
  port = new Application::ViewPort(*solar_system);
  port->Initialize();
  port->MainLoop();

  return 0;
}
void InitializeSolarSystem(Celestial::StarSystem ** system) {
  *system = new Celestial::StarSystem(std::make_shared<Celestial::Star>(std::string("Sun"),
    Physics::StateVector({ 0,0,0 }, { 0,0,0 }),
    Physics::StateElements(),
    Physics::RotationVector({ 0,0,0 }, { 0, 252.019, 1981.034 }),
    1.989e30,
    695700, //km
    1.32712440018e11));

  (*system)->AddBody({
    std::make_shared<Kepler::Planet>(
    std::string("Venus"),
    Physics::StateVector(
      { 18.963642678868314562, 27.032381534407686985, 10.958176401674448286 },
      { 90992820.059048295021, -52229470.094395421445, -29253017.756921399385 }
    ),
    Physics::RotationVector({ 0, 0, 0 }, { 0.0018111111, 0 , 0 }),
    6051.8, //km
    3.24859e5,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Earth"),
    Physics::StateVector(
      { 29.108594477163027392, 3.0181572786088968208, 1.3089359475535311539 },
      { 17355583.376673273742, -138618217.80339628458, -60109363.56389850378 }),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    6371.0, //km
    398600.4418,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Mars"),
    Physics::StateVector(
      { 25.07496623536686034, 0.41084958802272611, -0.4913005936619511 },
      { -1.7157167726489680928e7, -1.98720804521835725702e8, -9.0679525650894539347e7}),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    3389.5, //km
    42828.37,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Jupiter"),
    Physics::StateVector(
        {1.89088086E+00, -1.12918222E+01, -4.88663423E+00},
        {-8.05477727E+08, -1.24354649E+08, -3.36741757E+07}),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    69911, //km
    1.267e8,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Saturn"),
    Physics::StateVector(
      {-5.56897924E+00, 7.49632440E+00, 3.33462863E+00},
      {1.18032753E+09, 6.87518325E+08, 2.33141355E+08}),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    58232, //km
    3.793e7,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Uranus"),
    Physics::StateVector(
        {3.83486027E-01, -6.52180831E+00, -2.86176503E+00},
        {-2.73317716E+09, -1.73941652E+08, -3.74552833E+07}),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    25362, //km
    5.794e6,
    &((*system)->GetStar())
    ),
    std::make_shared<Kepler::Planet>(
    std::string("Uranus"),
    Physics::StateVector(
        {4.57524555E+00, -2.60254479E+00, -1.17928011E+00},
        {-2.40250795E+09, -3.58186506E+09, -1.40630325E+09}),
    Physics::RotationVector({ 0,0,0 }, { 0.4651, 0, 0 }),
    24622, //km
    6.837e6,
    &((*system)->GetStar())
    )
    });
}
