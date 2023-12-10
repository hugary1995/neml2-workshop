#include "BallLauncher.h"

namespace neml2
{

register_NEML2_object(BallLauncher);

OptionSet
BallLauncher::expected_options()
{
  OptionSet options = TransientDriver::expected_options();
  // REMOVE_BEGIN
  options.set<LabeledAxisAccessor>("velocity") = {"state", "v"};
  options.set<LabeledAxisAccessor>("position") = {"state", "x"};
  options.set<CrossRef<Vec>>("initial_velocity");
  options.set<CrossRef<Vec>>("initial_position");
  // REMOVE_END
  return options;
}

BallLauncher::BallLauncher(const OptionSet & options)
  : TransientDriver(options)
    // REMOVE_BEGIN
    ,
    _x0_name(options.get<LabeledAxisAccessor>("position")),
    _x0(options.get<CrossRef<Vec>>("initial_position")),
    _v0_name(options.get<LabeledAxisAccessor>("velocity")),
    _v0(options.get<CrossRef<Vec>>("initial_velocity"))
// REMOVE_END
{
}
// REMOVE_BEGIN
void
BallLauncher::apply_ic()
{
  TransientDriver::apply_ic();

  _out.set(_x0, _x0_name);
  _out.set(_v0, _v0_name);
}
// REMOVE_END

}
