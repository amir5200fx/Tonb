#include <sphericalTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const sphericalTensor::typeName = "sphericalTensor";

	template<>
	const char* sphericalTensor::componentNames[] = { "ii" };

	template<>
	const sphericalTensor sphericalTensor::zero(0);

	template<>
	const sphericalTensor sphericalTensor::one(1);

	template<>
	const sphericalTensor sphericalTensor::max(VGREAT);

	template<>
	const sphericalTensor sphericalTensor::min(-VGREAT);

	template<>
	const sphericalTensor sphericalTensor::I(1);

	template<>
	const sphericalTensor sphericalTensor::oneThirdI(1.0 / 3.0);

	template<>
	const sphericalTensor sphericalTensor::twoThirdsI(2.0 / 3.0);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //