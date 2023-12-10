#pragma once

#include "neml2/models/Model.h"

namespace neml2
{

class ParametrizedFlyingBall : public Model
{
public:
  static OptionSet expected_options();

  ParametrizedFlyingBall(const OptionSet & options);
};

}
