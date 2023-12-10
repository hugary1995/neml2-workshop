#include "ArrheniusLaw.h"

namespace neml2
{
register_NEML2_object(ArrheniusLaw);

OptionSet
ArrheniusLaw::expected_options()
{
  auto options = NonlinearParameter<Scalar>::expected_options();
  // REMOVE_BEGIN
  options.set<LabeledAxisAccessor>("temperature") = {"state", "T"};
  options.set<CrossRef<Scalar>>("activation_energy");
  options.set<Real>("ideal_gas_constant");
  options.set<CrossRef<Scalar>>("reference_value");
  // REMOVE_END
  return options;
}

ArrheniusLaw::ArrheniusLaw(const OptionSet & options)
  : NonlinearParameter<Scalar>(options)
    // REMOVE_BEGIN
    ,
    temperature(declare_input_variable<Scalar>(options.get<LabeledAxisAccessor>("temperature"))),
    _Q(declare_parameter<Scalar>("Q", "activation_energy")),
    _R(options.get<Real>("ideal_gas_constant")),
    _p0(options.get<CrossRef<Scalar>>("reference_value"))
// REMOVE_END
{
}

void
ArrheniusLaw::set_value(const LabeledVector & in,
                        LabeledVector * out,
                        LabeledMatrix * dout_din,
                        LabeledTensor3D * d2out_din2) const
{
  // REMOVE_BEGIN
  auto T = in.get<Scalar>(temperature);

  auto coef = math::exp(-_Q / _R / T) * _p0;

  if (out)
    out->set(coef, /*reserved accessor for the nonlinear parameter*/ p);

  if (dout_din || d2out_din2)
  {
    auto dcoef_dT = _Q / _R / T / T * coef;

    if (dout_din)
      dout_din->set(dcoef_dT, p, temperature);

    if (d2out_din2)
    {
      auto d2coef_dT2 = (_Q / _R / T / T - 2.0 / T) * dcoef_dT;
      d2out_din2->set(d2coef_dT2, p, temperature, temperature);
    }
  }
  // REMOVE_END
}
} // namespace neml2
