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
};
}
