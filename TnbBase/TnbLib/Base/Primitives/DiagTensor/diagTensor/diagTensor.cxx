#include <diagTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const diagTensor::typeName = "diagTensor";

	template<>
	const char* diagTensor::componentNames[] = { "xx", "yy", "zz" };

	template<>
	const diagTensor diagTensor::zero(0, 0, 0);

	template<>
	const diagTensor diagTensor::one(1, 1, 1);

	template<>
	const diagTensor diagTensor::max(VGREAT, VGREAT, VGREAT);

	template<>
	const diagTensor diagTensor::min(-VGREAT, -VGREAT, -VGREAT);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //