#include <labelSphericalTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const labelSphericalTensor::typeName = "labelSphericalTensor";

	template<>
	const char* labelSphericalTensor::componentNames[] = { "ii" };

	template<>
	const labelSphericalTensor labelSphericalTensor::zero(0);

	template<>
	const labelSphericalTensor labelSphericalTensor::one(1);

	template<>
	const labelSphericalTensor labelSphericalTensor::I(1);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //