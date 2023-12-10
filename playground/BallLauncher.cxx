#include "BallLauncher.h"

namespace neml2
{

register_NEML2_object(BallLauncher);

OptionSet
BallLauncher::expected_options()
{
  OptionSet options = TransientDriver::expected_options();
  return options;
}

BallLauncher::BallLauncher(const OptionSet & options)
  : TransientDriver(options)
{
}

}
