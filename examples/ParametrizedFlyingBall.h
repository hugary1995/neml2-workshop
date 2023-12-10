#pragma once

#include "neml2/models/Model.h"

namespace neml2
{

class ParametrizedFlyingBall : public Model
{
public:
  static OptionSet expected_options();

  ParametrizedFlyingBall(const OptionSet & options);
  // REMOVE_BEGIN
  const LabeledAxisAccessor velocity;
  const LabeledAxisAccessor acceleration;

protected:
  virtual void set_value(const LabeledVector & in,
                         LabeledVector * out,
                         LabeledMatrix * dout_din = nullptr,
                         LabeledTensor3D * d2out_din2 = nullptr) const override;

  const Scalar & _mu;
  // REMOVE_END
};

}
