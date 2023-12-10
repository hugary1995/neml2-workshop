#pragma once

#include "neml2/models/solid_mechanics/IsotropicHardening.h"

namespace neml2
{
class CustomIsotropicHardening : public IsotropicHardening
{
public:
  static OptionSet expected_options();

  CustomIsotropicHardening(const OptionSet & options);
  // REMOVE_BEGIN
protected:
  void set_value(const LabeledVector & in,
                 LabeledVector * out,
                 LabeledMatrix * dout_din = nullptr,
                 LabeledTensor3D * d2out_din2 = nullptr) const override;

  const Scalar & _a;
  const Scalar & _b;
  // REMOVE_END
};
} // namespace neml2
