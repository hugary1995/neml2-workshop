#include "workshop.h"
#include "neml2/tensors/LabeledVector.h"
#include "neml2/tensors/LabeledMatrix.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  LabeledAxis A;
  A.add<LabeledAxis>("axis1");
  A.add<LabeledAxis>("axis2");
  A.subaxis("axis1").add<Vec>("var1");
  A.subaxis("axis1").add<Rot>("var2");
  A.subaxis("axis2").add<R3>("var3");
  A.setup_layout();
  print_general(A, "LabeledAxis A");

  LabeledAxis B;
  B.add<LabeledAxis>("axis3");
  B.add<LabeledAxis>("axis4");
  B.subaxis("axis3").add<Rot>("var4");
  B.subaxis("axis4").add<R3>("var5");
  B.subaxis("axis4").add<R4>("var6");
  B.setup_layout();
  print_general(B, "LabeledAxis B");

  // LabeledAxisAccessors
  LabeledAxisAccessor axis1("axis1");
  LabeledAxisAccessor axis2("axis2");
  LabeledAxisAccessor axis3("axis3");
  LabeledAxisAccessor axis4("axis4");
  LabeledAxisAccessor var1({"axis1", "var1"});
  LabeledAxisAccessor var2({"axis1", "var2"});
  LabeledAxisAccessor var3({"axis2", "var3"});
  LabeledAxisAccessor var4({"axis3", "var4"});
  LabeledAxisAccessor var5({"axis4", "var5"});
  LabeledAxisAccessor var6({"axis4", "var6"});
  // REMOVE_BEGIN
  auto V = LabeledVector::empty({5, 3}, {&A});
  print_neml2_tensor_info(V, "V");

  auto M = LabeledMatrix::empty({5, 3}, {&A, &B});
  print_neml2_tensor_info(M, "M");

  // Accessing LabeledVector
  print_neml2_tensor_info(V(axis1), "V['axis1']");
  print_neml2_tensor_info(V(var3), "V['axis2/var3']");

  // Accessing LabeledMatrix
  print_neml2_tensor_info(M(axis1, axis3), "M['axis1', 'axis3']");
  print_neml2_tensor_info(M(var1, var5), "M['axis1/var1', 'axis4/var5']");
  // REMOVE_END

  return 0;
}
