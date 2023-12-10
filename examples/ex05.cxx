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
  // REMOVE_BEGIN
  A += 3.3;
  print_torch_tensor(A, "A after A += 3.3");
  print_torch_tensor(B, "B after A += 3.3");
  print_torch_tensor(C, "C after A += 3.3");

  B -= 5.5;
  print_torch_tensor(A, "A after B -= 5.5");
  print_torch_tensor(B, "B after B -= 5.5");
  print_torch_tensor(C, "C after B -= 5.5");

  A.base_index_put({Slice(2), Slice(3)}, BatchTensor::zeros({}, {}, default_tensor_options));
  print_torch_tensor(A, "A after A[2:, 3:] = 0");
  print_torch_tensor(B, "B after A[2:, 3:] = 0");
  print_torch_tensor(C, "C after A[2:, 3:] = 0");
  // REMOVE_END

  return 0;
}
