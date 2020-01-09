#include <scalarBlockGaussSeidelPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void BlockGaussSeidelPrecon<scalar>::calcInvDiag()
	{
		// Direct inversion of diagonal is sufficient, as the diagonal
		// is linear.  HJ, 20/Aug/2015
		invDiag_ = 1 / this->matrix_.diag();
	}


	template<>
	void BlockGaussSeidelPrecon<scalar>::precondition
	(
		scalarField& x,
		const scalarField& b
	) const
	{
		if (matrix_.diagonal())
		{
			x = b * invDiag_;
		}
		else if (matrix_.symmetric() || matrix_.asymmetric())
		{
			const scalarField& LowerCoeff = matrix_.lower();
			const scalarField& UpperCoeff = matrix_.upper();

			BlockSweep
			(
				x,
				invDiag_,
				LowerCoeff,
				UpperCoeff,
				b
			);
		}
	}


	template<>
	void BlockGaussSeidelPrecon<scalar>::preconditionT
	(
		scalarField& xT,
		const scalarField& bT
	) const
	{
		if (matrix_.diagonal())
		{
			xT = bT * invDiag_;
		}
		else if (matrix_.symmetric() || matrix_.asymmetric())
		{
			const scalarField& LowerCoeff = matrix_.lower();
			const scalarField& UpperCoeff = matrix_.upper();

			// Swap lower and upper coefficients, transposed matrix
			BlockSweep
			(
				xT,
				invDiag_,
				UpperCoeff,
				LowerCoeff,
				bT
			);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //