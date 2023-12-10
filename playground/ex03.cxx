#include "workshop.h"
#include "neml2/tensors/tensors.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  using namespace torch::indexing;
  auto A = BatchTensor::ones({15}, {12});
  print_neml2_tensor_info(A, "A");

  return 0;
}
