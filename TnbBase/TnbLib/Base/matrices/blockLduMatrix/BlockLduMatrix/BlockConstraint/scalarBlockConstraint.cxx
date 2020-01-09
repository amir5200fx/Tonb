#include <scalarBlockConstraint.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	void BlockConstraint<scalar>::combine
	(
		const BlockConstraint<scalar>& e
	)
	{
		if (e.fixedComponents_ > fixedComponents_)
		{
			fixedComponents_ = e.fixedComponents_;

			value_ = e.value_;
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //