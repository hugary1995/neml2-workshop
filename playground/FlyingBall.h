#pragma once

#include "neml2/models/Model.h"

namespace neml2
{

class FlyingBall : public Model
{
public:
  static OptionSet expected_options();

  FlyingBall(const OptionSet & options);

};

}
