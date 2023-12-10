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

  return 0;
}
