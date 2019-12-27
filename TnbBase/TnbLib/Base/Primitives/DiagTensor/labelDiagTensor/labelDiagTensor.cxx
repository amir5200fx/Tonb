#include <labelDiagTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const labelDiagTensor::typeName = "labelDiagTensor";

	template<>
	const char* labelDiagTensor::componentNames[] = { "xx", "yy", "zz" };

	template<>
	const labelDiagTensor labelDiagTensor::zero(0, 0, 0);

	template<>
	const labelDiagTensor labelDiagTensor::one(1, 1, 1);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //