// REMOVE_BEGIN
#include "ParametrizedFlyingBall.h"
#include "neml2/tensors/Vec.h"
#include "neml2/misc/math.h"

using namespace neml2;

register_NEML2_object(ParametrizedFlyingBall);

OptionSet
ParametrizedFlyingBall::expected_options()
{
  auto options = Model::expected_options();
  options.set<LabeledAxisAccessor>("velocity") = {"state", "v"};
  options.set<LabeledAxisAccessor>("acceleration") = {"state", "a"};
  options.set<CrossRef<Scalar>>("viscosity");
  return options;
}

ParametrizedFlyingBall::ParametrizedFlyingBall(const OptionSet & options)
  : Model(options),
    velocity(declare_input_variable<Vec>(options.get<LabeledAxisAccessor>("velocity"))),
    acceleration(declare_output_variable<Vec>(options.get<LabeledAxisAccessor>("acceleration"))),
    _mu(declare_parameter<Scalar>("mu", "viscosity"))
{
  setup();
}
void
ParametrizedFlyingBall::set_value(const LabeledVector & in,
                                  LabeledVector * out,
                                  LabeledMatrix * dout_din,
                                  LabeledTensor3D * d2out_din2) const
{
  neml_assert_dbg(!d2out_din2, "ParametrizedFlyingBall does not compute 2nd derivatives.");

  const auto options = in.options();

  Real g = 9.81;
  const auto v = in.get<Vec>(velocity);

  if (out)
  {
    const auto a = -Vec::fill(0, g, 0, options) - _mu * v;
    out->set(a, acceleration);
  }

  if (dout_din)
  {
    const auto da_dv = -_mu * Vec::identity_map(options);
    dout_din->set(da_dv, acceleration, velocity);
  }
}
// REMOVE_END
