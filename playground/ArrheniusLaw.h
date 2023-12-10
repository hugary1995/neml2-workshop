#pragma once

#include "neml2/models/NonlinearParameter.h"

namespace neml2
{
class ArrheniusLaw : public NonlinearParameter<Scalar>
{
public:
  static OptionSet expected_options();

  ArrheniusLaw(const OptionSet & options);

protected:
  virtual void set_value(const LabeledVector & in,
                         LabeledVector * out,
                         LabeledMatrix * dout_din = nullptr,
                         LabeledTensor3D * d2out_din2 = nullptr) const override;
};
} // namespace neml2
