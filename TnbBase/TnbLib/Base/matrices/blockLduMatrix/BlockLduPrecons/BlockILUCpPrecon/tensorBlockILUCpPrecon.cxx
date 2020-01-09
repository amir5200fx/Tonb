#include <tensorBlockILUCpPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	template<>
	void BlockILUCpPrecon<tensor>::calcActiveTypeFactorization
	(
		tensorField& preconD,
		tensorField& extUpper,
		tensorField& extLower
	) const
	{
		// Decoupled version
		notImplemented("void tnbLib::BlockILUCpPrecon<tensor>::calcFactorization");
	}


	template<>
	void BlockILUCpPrecon<tensor>::calcFactorization() const
	{
		// Get upper and lower matrix factors
		CoeffField<tensor>& Lower = extBlockMatrix_.extendedLower();
		CoeffField<tensor>& Upper = extBlockMatrix_.extendedUpper();

		// Calculate factorization
		// Note: lower, diag and upper must have same type as required by the
		// algorithm. This is handled by lowest possible promotion
		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				calcActiveTypeFactorization
				(
					preconDiag_.asScalar(),
					Upper.asScalar(),
					Lower.asScalar()
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				calcActiveTypeFactorization
				(
					preconDiag_.asLinear(), // Promotes to linear
					Upper.asLinear(),
					Lower.asLinear()
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				calcActiveTypeFactorization
				(
					preconDiag_.asLinear(),
					Upper.asLinear(), // Promotes to linear
					Lower.asLinear()  // Promotes to linear
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				calcActiveTypeFactorization
				(
					preconDiag_.asLinear(),
					Upper.asLinear(),
					Lower.asLinear()
				);
			}
		}
	}


	template<>
	void BlockILUCpPrecon<tensor>::precondition
	(
		tensorField& x,
		const tensorField& b
	) const
	{
		// Decoupled version
		notImplemented("void tnbLib::BlockILUCpPrecon<tensor>::precondition");
	}


	template<>
	void BlockILUCpPrecon<tensor>::preconditionT
	(
		tensorField& xT,
		const tensorField& bT
	) const
	{
		// Decoupled version
		notImplemented("void tnbLib::BlockILUCpPrecon<tensor>::preconditionT");
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //