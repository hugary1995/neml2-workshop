#include "neml2/models/Model.h"
#include "neml2/tensors/Vec.h"
#include "neml2/misc/math.h"
#include "workshop.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  auto & model = load<Model>(root_dir() + "ParametrizedFlyingBall.i", "Models", "trajectory");

  TorchSize nbatch = 5;
  auto in = LabeledVector::empty({nbatch}, {&model.input()});

  // Specify old velocity
  auto v_accessor = LabeledAxisAccessor({"old_state", "v"});
  auto v_min = Vec::fill(10, 3, 0);
  auto v_max = Vec::fill(15, 4, 0);
  auto v = Vec::linspace(v_min, v_max, nbatch);
  in.set(v, v_accessor);

  // Specify old position
  auto x_accessor = LabeledAxisAccessor({"old_state", "x"});
  auto x_min = Vec::fill(0.5, 0.5, 0);
  auto x_max = Vec::fill(1.0, 2.0, 0);
  auto x = Vec::linspace(v_min, v_max, nbatch);
  in.set(x, x_accessor);

  // Specify old time
  auto tn_accessor = LabeledAxisAccessor({"old_forces", "t"});
  auto tn = Scalar::full(0.0);
  in.set(tn, tn_accessor);

  // Specify current time
  auto t_accessor = LabeledAxisAccessor({"forces", "t"});
  auto t = Scalar::full(0.7);
  in.set(t, t_accessor);

  return 0;
}
