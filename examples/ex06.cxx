#include "workshop.h"
#include "neml2/tensors/tensors.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  // Rank 0
  print_neml2_tensor_info(Scalar::empty({5, 5}), "Scalar");

  // Rank 1
  print_neml2_tensor_info(Vec::empty({5, 5}), "Vec");
  print_neml2_tensor_info(Rot::empty({5, 5}), "Rot");

  // Rank 2
  print_neml2_tensor_info(R2::empty({5, 5}), "R2");
  print_neml2_tensor_info(WR2::empty({5, 5}), "WR2");
  print_neml2_tensor_info(SR2::empty({5, 5}), "SR2");

  // Rank 3
  print_neml2_tensor_info(R3::empty({5, 5}), "R3");
  print_neml2_tensor_info(SFR3::empty({5, 5}), "SFR3");

  // Rank 4
  print_neml2_tensor_info(R4::empty({5, 5}), "R4");
  print_neml2_tensor_info(SSR4::empty({5, 5}), "SSR4");

  // Rank 5
  print_neml2_tensor_info(R5::empty({5, 5}), "R5");
  print_neml2_tensor_info(SSFR5::empty({5, 5}), "SSFR5");

  // Other
  print_neml2_tensor_info(Quaternion::empty({5, 5}), "Quaternion");
  print_neml2_tensor_info(MillerIndex::empty({5, 5}), "MillerIndex");

  return 0;
}
