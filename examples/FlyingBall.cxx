// REMOVE_BEGIN
#include "FlyingBall.h"
#include "neml2/tensors/Vec.h"
#include "neml2/misc/math.h"

using namespace neml2;

register_NEML2_object(FlyingBall);

OptionSet
FlyingBall::expected_options()
{
  auto options = Model::expected_options();
  options.set<LabeledAxisAccessor>("velocity") = {"state", "v"};
  options.set<LabeledAxisAccessor>("acceleration") = {"state", "a"};
  return options;
}

FlyingBall::FlyingBall(const OptionSet & options)
  : Model(options),
    velocity(declare_input_variable<Vec>(options.get<LabeledAxisAccessor>("velocity"))),
    acceleration(declare_output_variable<Vec>(options.get<LabeledAxisAccessor>("acceleration")))
{
  setup();
}

void
FlyingBall::set_value(const LabeledVector & in,
                      LabeledVector * out,
                      LabeledMatrix * dout_din,
                      LabeledTensor3D * d2out_din2) const
{
  neml_assert_dbg(!d2out_din2, "FlyingBall does not compute 2nd derivatives.");

  const auto options = in.options();

  Real g = 9.81;
  Real mu = 0.01;
  const auto v = in.get<Vec>(velocity);

  if (out)
  {
    const auto a = -Vec::fill(0, g, 0, options) - mu * v;
    out->set(a, acceleration);
  }

  if (dout_din)
  {
    const auto da_dv = -mu * Vec::identity_map(options);
    dout_din->set(da_dv, acceleration, velocity);
  }
}
// REMOVE_END
