#include "workshop.h"
#include "FlyingBall.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  // REMOVE_BEGIN
  auto & model = load<FlyingBall>(root_dir() + "FlyingBall.i", "Models", "ball");

  print_general(model.input(), "FlyingBall input variables");
  print_general(model.output(), "FlyingBall output variables");
  // REMOVE_END

  return 0;
}
