#include "workshop.h"
#include "neml2/tensors/LabeledAxis.h"

using namespace neml2;

int
main()
{
  workshop_preface();

  LabeledAxis A;
  A.setup_layout();
  print_general(A, "A");
  // REMOVE_BEGIN
  // Add subaxes
  A.add<LabeledAxis>("axis1");
  A.add<LabeledAxis>("axis2");
  A.subaxis("axis2").add<LabeledAxis>("axis3"); // Can be nested
  A.setup_layout();
  print_general(A, "A after adding subaxes");

  // Add variables
  A.add<Scalar>("var1");
  A.add<SR2>("var2");
  A.add<R2>("var3");
  A.subaxis("axis1").add<Vec>("var4");
  A.subaxis("axis1").add<Rot>("var5");
  A.subaxis("axis2").add<R3>("var6");
  A.subaxis("axis2").add<R4>("var7");
  A.subaxis("axis2").subaxis("axis3").add<SFR3>("var8");
  A.subaxis("axis2").subaxis("axis3").add<R5>("var9");
  A.setup_layout();
  print_general(A, "A after adding variables");

  // Query LabeledAxis
  print_general(A.has_variable("var1"), "Does A have variable named 'var1'?");
  print_general(A.has_variable("foo"), "Does A have variable named 'foo'?");
  print_general(A.has_variable("axis1"), "Does A have variable named 'axis1'?");
  print_general(A.has_subaxis("axis1"), "Does A have subaxis named 'axis1'?");
  print_general(A.has_subaxis("axis2"), "Does A have subaxis named 'axis2'?");
  print_general(A.has_subaxis("axis3"), "Does A have subaxis named 'axis3'?");
  print_general(A.has_item("var1"), "Does A have item named 'var1'?");
  print_general(A.has_item("axis1"), "Does A have item named 'axis1'?");

  // LabeledAxisAccessor
  LabeledAxisAccessor var8({"axis2", "axis3", "var8"});
  LabeledAxisAccessor axis3({"axis2", "axis3"});
  print_general(A.has_variable(var8), "Does A have variable 'axis2/axis3/var8'?");
  print_general(A.has_subaxis(axis3), "Does A have subaxis 'axis2/axis3'?");

  // Why is this useful?
  print_general(A.indices(var8), "Indices for slicing variable 'axis2/axis3/var8'");
  print_general(A.indices(axis3), "Indices for slicing subaxis 'axis2/axis3'");
  // REMOVE_END

  return 0;
}
