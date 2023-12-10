#pragma once

#include "neml2/models/solid_mechanics/IsotropicHardening.h"

namespace neml2
{
class CustomIsotropicHardening : public IsotropicHardening
{
public:
  static OptionSet expected_options();

  CustomIsotropicHardening(const OptionSet & options);
};
} // namespace neml2
