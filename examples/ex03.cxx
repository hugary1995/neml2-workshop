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
  // REMOVE_BEGIN
  print_neml2_tensor_info(A.batch_index({2}), "A.batch[2]");
  print_neml2_tensor_info(A.base_index({2}), "A.base[2]");

  print_neml2_tensor_info(A.batch_index({true}), "A.batch[True]");
  print_neml2_tensor_info(A.base_index({true}), "A.base[True]");

  print_neml2_tensor_info(A.batch_index({Slice()}), "A.batch[:]");
  print_neml2_tensor_info(A.base_index({Slice()}), "A.base[:]");

  print_neml2_tensor_info(A.batch_index({Slice(2, None)}), "A.batch[2:]");
  print_neml2_tensor_info(A.base_index({Slice(2, None)}), "A.base[2:]");

  print_neml2_tensor_info(A.batch_index({Slice(None, 2)}), "A.batch[:2]");
  print_neml2_tensor_info(A.base_index({Slice(None, 2)}), "A.base[:2]");

  print_neml2_tensor_info(A.batch_index({Slice(1, 5, 2)}), "A.batch[1:5:2]");
  print_neml2_tensor_info(A.base_index({Slice(1, 5, 2)}), "A.base[1:5:2]");
  // REMOVE_END

  return 0;
}
