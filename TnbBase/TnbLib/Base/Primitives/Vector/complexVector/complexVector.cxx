#include <complexVector.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const complexVector::typeName = "complexVector";

	template<>
	const char* complexVector::componentNames[] = { "x", "y", "z" };

	template<>
	const complexVector complexVector::zero
	(
		complex(0, 0),
		complex(0, 0),
		complex(0, 0)
	);

	template<>
	const complexVector complexVector::one
	(
		complex(1, 1),
		complex(1, 1),
		complex(1, 1)
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //