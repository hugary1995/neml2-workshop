#include "workshop.h"
#include "neml2/tensors/tensors.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  using namespace torch::indexing;

  auto A = BatchTensor::ones({}, {5, 5});
  print_torch_tensor(A, "A");

  auto B = A.base_index({Slice(None, 3), Slice(2, 4)});
  print_torch_tensor(B, "B");

  auto C = B.clone();
  print_torch_tensor(C, "C");

  return 0;
}
