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

  auto D = BatchTensor::ones({5, 1}, {2, 2}, torch::kInt64);
  print_neml2_tensor_info(D, "D");

  if (torch::cuda::is_available())
  {
    auto E = BatchTensor::ones({2, 3, 1, 2}, {5, 6}, torch::kCUDA);
    // equivalent to
    // auto E = A.to(torch::kCUDA);
    print_neml2_tensor_info(E, "E");
  }

  A.requires_grad_();
  print_neml2_tensor_info(A, "A (with AD)");

  auto F = BatchTensor::ones(
      {5, 1}, {2, 2}, torch::TensorOptions().dtype(torch::kFloat32).device(torch::kCPU).requires_grad(true));
  print_neml2_tensor_info(F, "F");

  auto G = BatchTensor::ones({}, {5, 5, 5});
  print_neml2_tensor_info(G, "G");
  // REMOVE_END

  return 0;
}
