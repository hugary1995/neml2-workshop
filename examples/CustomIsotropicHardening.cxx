// REMOVE_BEGIN
#include "CustomIsotropicHardening.h"

namespace neml2
{
register_NEML2_object(CustomIsotropicHardening);

OptionSet
CustomIsotropicHardening::expected_options()
{
  OptionSet options = IsotropicHardening::expected_options();
  options.set<CrossRef<Scalar>>("a");
  options.set<CrossRef<Scalar>>("b");
  return options;
}

CustomIsotropicHardening::CustomIsotropicHardening(const OptionSet & options)
  : IsotropicHardening(options),
    _a(declare_parameter<Scalar>("a", "a")),
    _b(declare_parameter<Scalar>("b", "b"))
{
}

void
CustomIsotropicHardening::set_value(const LabeledVector & in,
                                    LabeledVector * out,
                                    LabeledMatrix * dout_din,
                                    LabeledTensor3D * d2out_din2) const
{
  auto ep = in.get<Scalar>(equivalent_plastic_strain);

  if (out)
  {
    auto h = _a * ep * math::exp(-ep / _b);
    out->set(h, isotropic_hardening);
  }

  if (dout_din)
  {
    auto dh_dep = _a * math::exp(-ep / _b) - _a / _b * ep * math::exp(-ep / _b);
    dout_din->set(dh_dep, isotropic_hardening, equivalent_plastic_strain);
    if (has_nonlinear_parameter("a"))
      dout_din->set(ep * math::exp(-ep / _b), isotropic_hardening, nl_param("a"));
  }

  if (d2out_din2)
  {
    auto d2h_dep2 = _a / _b * (ep / _b * math::exp(-ep / _b) - 2.0 * math::exp(-ep / _b));
    d2out_din2->set(d2h_dep2, isotropic_hardening, equivalent_plastic_strain, equivalent_plastic_strain);
  }
}
} // namespace neml2
  // REMOVE_END
