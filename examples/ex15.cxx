#include <fstream>

#include "neml2/drivers/Driver.h"
#include "workshop.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  // REMOVE_BEGIN
  auto & driver = load<Driver>("examples/FlyingBall.i", "Drivers", "launcher");
  driver.run();
  // REMOVE_END

  return 0;
}
