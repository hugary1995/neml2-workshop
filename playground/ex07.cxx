#include "workshop.h"
#include "neml2/tensors/LabeledAxis.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  LabeledAxis A;
  A.setup_layout();
  print_general(A, "A");

  return 0;
}
