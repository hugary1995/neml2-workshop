#include "workshop.h"
#include "neml2/tensors/tensors.h"

using namespace neml2;

int
main()
{
  workshop_preface();
  // REMOVE_BEGIN
  auto A = BatchTensor::ones({2, 3, 1, 2}, {5, 6});
  print_neml2_tensor_info(A, "A");

  auto B = BatchTensor::full({3, 5, 2}, {5, 6}, 2.3);
  print_neml2_tensor_info(B, "B");

  auto C = BatchTensor::zeros({2, 3, 1, 2}, {1, 1});
  print_neml2_tensor_info(C, "C");

  auto D = A + B; // OK, because
                  // 1. A and B have the same base shape
                  // 2. Iterating backward from the last batch dimension, the batch
                  // sizes either
                  //     a. match,
                  //     b. one of them is one, or
                  //     c. one of them does not exist.
                  //
                  // A's batch shape: (2, 3, 1, 2)
                  // B's batch shape: (   3, 5, 2)
                  //                            ^ match
                  //                         ^ one of them is one
                  //                      ^ match
                  //                   ^ one of them does not exist
                  //
                  // Broadcasting happens at the 0th and the 2nd batch dimensions of
                  // A. The resulting tensor should have batch shape
                  //                  (2, 3, 5, 2)
                  //                   ^     ^
  print_neml2_tensor_info(D, "D = A + B");

#ifndef NDEBUG
  try
  {
    print_title("E = A + C, expecting an exception");
    auto E = A + C;
  }
  catch (NEMLException & e)
  {
    std::cout << e.what() << std::endl << std::endl;
  }
#endif

  auto E = torch::Tensor(A) + torch::Tensor(C);
  print_torch_tensor_info(E, "E = torch::Tensor(A) + torch::Tensor(C)");
  // REMOVE_END

  return 0;
}
