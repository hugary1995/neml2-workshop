#pragma once

#include "neml2/models/NonlinearParameter.h"

namespace neml2
{
class ArrheniusLaw : public NonlinearParameter<Scalar>
{
public:
  static OptionSet expected_options();

  ArrheniusLaw(const OptionSet & options);
  // REMOVE_BEGIN
  const LabeledAxisAccessor temperature;
  // REMOVE_END

protected:
  virtual void set_value(const LabeledVector & in,
                         LabeledVector * out,
                         LabeledMatrix * dout_din = nullptr,
                         LabeledTensor3D * d2out_din2 = nullptr) const override;
  // REMOVE_BEGIN
  const Scalar & _Q;
  const Real _R;
  const Scalar _p0;
  // REMOVE_END
};
} // namespace neml2
