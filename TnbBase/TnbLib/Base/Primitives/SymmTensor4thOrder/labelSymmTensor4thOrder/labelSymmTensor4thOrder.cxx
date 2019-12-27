#include <labelSymmTensor4thOrder.hxx>

#include <mathematicalConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const labelSymmTensor4thOrder::typeName = "labelSymmTensor4thOrder";

	template<>
	const char* labelSymmTensor4thOrder::componentNames[] =
	{
		"xxxx", "xxyy", "xxzz",
				"yyyy", "yyzz",
						"zzzz",
							   "xyxy",
									  "yzyz",
											 "zxzx"
	};

	template<>
	const labelSymmTensor4thOrder labelSymmTensor4thOrder::zero
	(
		0, 0, 0,
		0, 0,
		0,
		0,
		0,
		0
	);

	template<>
	const labelSymmTensor4thOrder labelSymmTensor4thOrder::one
	(
		1, 1, 1,
		1, 1,
		1,
		1,
		1,
		1
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //