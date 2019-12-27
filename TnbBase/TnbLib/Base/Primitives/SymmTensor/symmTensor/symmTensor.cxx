#include <symmTensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const symmTensor::typeName = "symmTensor";

	template<>
	const char* symmTensor::componentNames[] =
	{
		"xx", "xy", "xz",
			  "yy", "yz",
					"zz"
	};

	template<>
	const symmTensor symmTensor::zero
	(
		0, 0, 0,
		0, 0,
		0
	);

	template<>
	const symmTensor symmTensor::one
	(
		1, 1, 1,
		1, 1,
		1
	);

	template<>
	const symmTensor symmTensor::max
	(
		VGREAT, VGREAT, VGREAT,
		VGREAT, VGREAT,
		VGREAT
	);

	template<>
	const symmTensor symmTensor::min
	(
		-VGREAT, -VGREAT, -VGREAT,
		-VGREAT, -VGREAT,
		-VGREAT
	);

	template<>
	const symmTensor symmTensor::I
	(
		1, 0, 0,
		1, 0,
		1
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //