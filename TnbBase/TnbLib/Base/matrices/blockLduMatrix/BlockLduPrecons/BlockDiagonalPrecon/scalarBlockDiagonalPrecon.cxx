#include <scalarBlockDiagonalPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockDiagonalPrecon<scalar>::precondition
	(
		scalarField& x,
		const scalarField& b
	) const
	{
		const scalarField& diag = matrix_.diag();

		forAll(x, i)
		{
			x[i] = b[i] / diag[i];
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //