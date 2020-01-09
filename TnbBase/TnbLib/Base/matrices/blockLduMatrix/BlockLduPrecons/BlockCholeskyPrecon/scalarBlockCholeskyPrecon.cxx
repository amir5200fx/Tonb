#include <scalarBlockCholeskyPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockCholeskyPrecon<scalar>::calcPreconDiag()
	{
		// Precondition the diagonal
		if (matrix_.symmetric())
		{
			const unallocLabelList& upperAddr = matrix_.lduAddr().upperAddr();
			const unallocLabelList& lowerAddr = matrix_.lduAddr().lowerAddr();

			// Get off-diagonal matrix coefficients
			const scalarField& upper = matrix_.upper();

			forAll(upper, coeffI)
			{
				preconDiag_[upperAddr[coeffI]] -=
					sqr(upper[coeffI]) / preconDiag_[lowerAddr[coeffI]];
			}
		}
		else if (matrix_.asymmetric())
		{
			const unallocLabelList& upperAddr = matrix_.lduAddr().upperAddr();
			const unallocLabelList& lowerAddr = matrix_.lduAddr().lowerAddr();

			// Get off-diagonal matrix coefficients
			const scalarField& upper = matrix_.upper();
			const scalarField& lower = matrix_.lower();

			forAll(upper, coeffI)
			{
				preconDiag_[upperAddr[coeffI]] -=
					upper[coeffI] * lower[coeffI] / preconDiag_[lowerAddr[coeffI]];
			}
		}

		// Invert the diagonal for future use
		forAll(preconDiag_, i)
		{
			preconDiag_[i] = 1.0 / preconDiag_[i];
		}
	}


	template<>
	void tnbLib::BlockCholeskyPrecon<scalar>::precondition
	(
		scalarField& x,
		const scalarField& b
	) const
	{
		forAll(x, i)
		{
			x[i] = b[i] * preconDiag_[i];
		}

		if (matrix_.symmetric())
		{
			const unallocLabelList& upperAddr = matrix_.lduAddr().upperAddr();
			const unallocLabelList& lowerAddr = matrix_.lduAddr().lowerAddr();

			// Get off-diagonal matrix coefficients
			const scalarField& upper = matrix_.upper();

			forAll(upper, coeffI)
			{
				x[upperAddr[coeffI]] -=
					preconDiag_[upperAddr[coeffI]] *
					upper[coeffI] * x[lowerAddr[coeffI]];
			}

			forAllReverse(upper, coeffI)
			{
				x[lowerAddr[coeffI]] -=
					preconDiag_[lowerAddr[coeffI]] *
					upper[coeffI] * x[upperAddr[coeffI]];
			}
		}
		else if (matrix_.asymmetric())
		{
			const unallocLabelList& upperAddr = matrix_.lduAddr().upperAddr();
			const unallocLabelList& lowerAddr = matrix_.lduAddr().lowerAddr();
			const unallocLabelList& losortAddr = matrix_.lduAddr().losortAddr();

			// Get off-diagonal matrix coefficients
			const scalarField& upper = matrix_.upper();
			const scalarField& lower = matrix_.lower();

			label losortCoeff;

			forAll(lower, coeffI)
			{
				losortCoeff = losortAddr[coeffI];

				x[upperAddr[losortCoeff]] -=
					preconDiag_[upperAddr[losortCoeff]] *
					lower[losortCoeff] * x[lowerAddr[losortCoeff]];
			}

			forAllReverse(upper, coeffI)
			{
				x[lowerAddr[coeffI]] -=
					preconDiag_[lowerAddr[coeffI]] *
					upper[coeffI] * x[upperAddr[coeffI]];
			}
		}
	}


	template<>
	void tnbLib::BlockCholeskyPrecon<scalar>::preconditionT
	(
		scalarField& xT,
		const scalarField& bT
	) const
	{
		if (matrix_.symmetric())
		{
			precondition(xT, bT);
		}

		forAll(xT, i)
		{
			xT[i] = bT[i] * preconDiag_[i];
		}

		if (matrix_.asymmetric())
		{
			const unallocLabelList& upperAddr = matrix_.lduAddr().upperAddr();
			const unallocLabelList& lowerAddr = matrix_.lduAddr().lowerAddr();
			const unallocLabelList& losortAddr = matrix_.lduAddr().losortAddr();

			// Get off-diagonal matrix coefficients
			const scalarField& upper = matrix_.upper();
			const scalarField& lower = matrix_.lower();

			label losortCoeff;

			forAll(lower, coeffI)
			{
				xT[upperAddr[coeffI]] -=
					preconDiag_[upperAddr[coeffI]] *
					upper[coeffI] * xT[lowerAddr[coeffI]];
			}

			forAllReverse(upper, coeffI)
			{
				losortCoeff = losortAddr[coeffI];

				xT[lowerAddr[losortCoeff]] -=
					preconDiag_[lowerAddr[losortCoeff]] *
					lower[losortCoeff] * xT[upperAddr[losortCoeff]];
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //