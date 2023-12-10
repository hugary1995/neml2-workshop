#include "ArrheniusLaw.h"

namespace neml2
{
register_NEML2_object(ArrheniusLaw);

OptionSet
ArrheniusLaw::expected_options()
{
  auto options = NonlinearParameter<Scalar>::expected_options();
  return options;
}

ArrheniusLaw::ArrheniusLaw(const OptionSet & options)
  : NonlinearParameter<Scalar>(options)
{
}

void
ArrheniusLaw::set_value(const LabeledVector & in,
                        LabeledVector * out,
                        LabeledMatrix * dout_din,
                        LabeledTensor3D * d2out_din2) const
{
}
} // namespace neml2
