#include <fstream>

#include "neml2/drivers/Driver.h"
#include "workshop.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  auto & model = load<Model>(root_dir() + "ArrheniusLaw.i", "Models", "model");

  print_general(model.input(), "Input variables");
  print_dict(
      model.named_parameters(true), [](auto && p) { return p.sizes(); }, "Model parameters");

  return 0;
}
