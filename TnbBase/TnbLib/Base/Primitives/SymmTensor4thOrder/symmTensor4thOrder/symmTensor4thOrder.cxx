#include <symmTensor4thOrder.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* const symmTensor4thOrder::typeName = "symmTensor4thOrder";

	template<>
	const char* symmTensor4thOrder::componentNames[] =
	{
		"xxxx", "xxyy", "xxzz",
				"yyyy", "yyzz",
						"zzzz",
							   "xyxy",
									  "yzyz",
											 "zxzx"
	};

	template<>
	const symmTensor4thOrder symmTensor4thOrder::zero
	(
		0, 0, 0,
		0, 0,
		0,
		0,
		0,
		0
	);

	template<>
	const symmTensor4thOrder symmTensor4thOrder::one
	(
		1, 1, 1,
		1, 1,
		1,
		1,
		1,
		1
	);

	template<>
	const symmTensor4thOrder symmTensor4thOrder::max
	(
		VGREAT, VGREAT, VGREAT,
		VGREAT, VGREAT,
		VGREAT,
		VGREAT,
		VGREAT,
		VGREAT
	);

	template<>
	const symmTensor4thOrder symmTensor4thOrder::min
	(
		-VGREAT, -VGREAT, -VGREAT,
		-VGREAT, -VGREAT,
		-VGREAT,
		-VGREAT,
		-VGREAT,
		-VGREAT
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //