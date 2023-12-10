#include <fstream>

#include "neml2/models/ComposedModel.h"
#include "workshop.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  // REMOVE_BEGIN
  auto & model = load<ComposedModel>("examples/FlyingBall.i", "Models", "implicit_trajectory");

  print_general(model.input(), "implicit_trajectory input variables");
  print_general(model.output(), "implicit_trajectory output variables");

  std::ofstream dot("implicit_trajectory.dot");
  model.to_dot(dot);
  // REMOVE_END

  return 0;
}
