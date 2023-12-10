#include <fstream>

#include "neml2/drivers/Driver.h"
#include "workshop.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  auto & driver = load<Driver>(root_dir() + "ParametrizedFlyingBall.i", "Drivers", "launcher");
  driver.run();

  return 0;
}
