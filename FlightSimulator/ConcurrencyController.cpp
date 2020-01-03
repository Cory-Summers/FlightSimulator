#include "ConcurrencyController.h"

MVC::ConcurrencyController::ConcurrencyController()
  : cv_star(),
  cv_natural(),
  star_mutex(),
  natural_mutex()
{
}
