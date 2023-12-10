#include "neml2/tensors/Vec.h"
#include "workshop.h"
#include "FlyingBall.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  // REMOVE_BEGIN
  auto & model = load<FlyingBall>(root_dir() + "FlyingBall.i", "Models", "ball");

  // Specify input
  auto in = LabeledVector::empty({3}, {&model.input()});
  auto v_min = Vec::fill(10, 3, 0);
  auto v_max = Vec::fill(15, 4, 0);
  auto v = Vec::linspace(v_min, v_max, 3);
  in.set(v, model.velocity);
  print_torch_tensor(in, "Model input");

  // Evaluate model to get output
  auto out = model.value(in);
  print_torch_tensor(out, "Model output");
  // REMOVE_END

  return 0;
}
