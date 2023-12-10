#pragma once

#include "neml2/drivers/TransientDriver.h"
#include "neml2/tensors/Vec.h"

namespace neml2
{
class BallLauncher : public TransientDriver
{
public:
  static OptionSet expected_options();

  BallLauncher(const OptionSet & options);

protected:
  // REMOVE_BEGIN
  virtual void apply_ic() override;

  const LabeledAxisAccessor _x0_name;
  const Vec _x0;

  const LabeledAxisAccessor _v0_name;
  const Vec _v0;
  // REMOVE_END
};
}
