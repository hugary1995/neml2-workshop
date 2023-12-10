#include "workshop.h"

void
workshop_preface()
{
  std::cout << R""""(
╔═══════════════════════════════════════════════════════════════════════════════╗
║ Welcome to the NEML2 workshop!                                                ║
║                                                                               ║
║ These set of training materials were last updated on 12/12, 2023.             ║
║ Questions and bug reports: https://github.com/reverendbedford/neml2/issues    ║
╚═══════════════════════════════════════════════════════════════════════════════╝

╔═══════════════════════════════════════════════════════════════════════════════╗
║ Copyright 2023, UChicago Argonne, LLC                                         ║
║ All Rights Reserved                                                           ║
║ Software Name: NEML2 -- the New Engineering material Model Library, version 2 ║
║ By: Argonne National Laboratory                                               ║
║ OPEN SOURCE LICENSE (MIT)                                                     ║
╚═══════════════════════════════════════════════════════════════════════════════╝
)"""" << std::endl;
}

void
print_title(const std::string_view title, const size_t pad, const size_t n)
{
  assert(n - pad * 2 - title.size() > 0);

  std::cout << std::endl;

  if (!title.empty())
  {
    auto left = (n - title.size() - pad * 2) / 2;
    auto right = n - left - title.size() - pad * 2;
    std::cout << std::string(left, '=') << std::string(pad, ' ') << title << std::string(pad, ' ')
              << std::string(right, '=') << std::endl;
  }
  else
    std::cout << std::string(n, '=') << std::endl;
}

void
print_torch_tensor(const torch::Tensor & x, const std::string_view title, const size_t pad, const size_t n)
{
  print_title(title, pad, n);

  std::cout << x << std::endl << std::endl;
}

void
print_torch_tensor_info(const torch::Tensor & x, const std::string_view title, const size_t pad, const size_t n)
{
  print_title(title, pad, n);

  std::cout << "      dimension: " << x.dim() << std::endl;
  std::cout << "          shape: " << x.sizes() << std::endl;
  std::cout << "          dtype: " << x.dtype() << std::endl;
  std::cout << "         device: " << x.device() << std::endl;
  std::cout << "  requires grad: " << (x.requires_grad() ? "true" : "false") << std::endl;
  std::cout << std::endl;
}

void
print_neml2_tensor_info(const neml2::BatchTensor & x, const std::string_view title, const size_t pad, const size_t n)
{
  print_torch_tensor_info(x, title, pad, n);

  std::cout << "NEML2 specific info" << std::endl;
  std::cout << "-------------------" << std::endl;
  std::cout << "batch dimension: " << x.batch_dim() << std::endl;
  std::cout << " base dimension: " << x.base_dim() << std::endl;
  std::cout << "    batch shape: " << x.batch_sizes() << std::endl;
  std::cout << "     base shape: " << x.base_sizes() << std::endl;
  std::cout << "   base storage: " << x.base_storage() << std::endl;
  std::cout << std::endl;
}
