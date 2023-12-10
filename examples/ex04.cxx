#include "workshop.h"
#include "neml2/tensors/tensors.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  using namespace torch::indexing;
  auto A = BatchTensor::ones({15, 13, 5}, {12, 22, 2});
  print_neml2_tensor_info(A, "A");
  // REMOVE_BEGIN
  print_neml2_tensor_info(A.batch_index({2, Slice(5, 12, 2), 1}), "A.batch[2, 5:12:2, 1]");
  print_neml2_tensor_info(A.base_index({Slice(), -5, 0}), "A.base[:, -5, 0]");
  print_neml2_tensor_info(A.batch_index({Ellipsis, Slice(0, None, 2)}), "A.batch[..., 0::2]");
  print_neml2_tensor_info(A.base_index({Slice(8, -2), Ellipsis}), "A.base[8:-2, ...]");
  // REMOVE_END

  return 0;
}
