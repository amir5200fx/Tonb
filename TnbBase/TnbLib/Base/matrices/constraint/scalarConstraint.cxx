#include <constraint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	scalar constraint<scalar>::componentOfValue
	(
		const scalar& v,
		const direction
	) const
	{
		return v;
	}


	template<>
	void constraint<scalar>::combine
	(
		const constraint<scalar>& e
	)
	{
		fixedComponents_ = max(e.fixedComponents_, fixedComponents_);

		value_ = e.value_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //