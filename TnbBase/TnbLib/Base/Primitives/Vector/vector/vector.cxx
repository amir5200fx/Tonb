#include <vector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const vector::typeName = "vector";

	template<>
	const char* vector::componentNames[] = { "x", "y", "z" };

	template<>
	const vector vector::zero(0, 0, 0);

	template<>
	const vector vector::one(1, 1, 1);

	template<>
	const vector vector::max(VGREAT, VGREAT, VGREAT);

	template<>
	const vector vector::min(-VGREAT, -VGREAT, -VGREAT);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib