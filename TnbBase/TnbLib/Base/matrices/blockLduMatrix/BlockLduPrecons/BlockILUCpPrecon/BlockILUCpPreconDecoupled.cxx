#include <BlockILUCpPrecon.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockILUCpPrecon<Type>::decoupledPrecondition
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	// Helper type definition of DecoupledCoeffField
	typedef DecoupledCoeffField<Type> DecoupledTypeCoeffField;

	if (!this->matrix_.diagonal())
	{
		// Get upper and lower matrix factors
		const DecoupledTypeCoeffField& Lower = extBlockMatrix_.extendedLower();
		const DecoupledTypeCoeffField& Upper = extBlockMatrix_.extendedUpper();

		// Execute preconditioning by LU substitution.
		// Note: lower, diag and upper must have same type as required by the
		// algorithm. This is handled by lowest possible promotion
		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				LUSubstitute
				(
					x,
					preconDiag_.asScalar(),
					Upper.asScalar(),
					Lower.asScalar(),
					b
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				LUSubstitute
				(
					x,
					preconDiag_.asLinear(), // Promotes to linear
					Upper.asLinear(),
					Lower.asLinear(),
					b
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				LUSubstitute
				(
					x,
					preconDiag_.asLinear(),
					Upper.asLinear(), // Promotes to linear
					Lower.asLinear(), // Promotes to linear
					b
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				LUSubstitute
				(
					x,
					preconDiag_.asLinear(),
					Upper.asLinear(),
					Lower.asLinear(),
					b
				);
			}
		}
		else
		{
			FatalErrorIn
			(
				"void BlockILUCpPrecon<Type>::decoupledPrecondition\n"
				"(\n"
				"    Field<Type>& x,\n"
				"    const Field<Type>& T\n"
				") const"
			) << "Problem with coefficient type morphing."
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn
		(
			"void BlockILUCpPrecon<Type>::decoupledPrecondition\n"
			"(\n"
			"    Field<Type>& x,\n"
			"    const Field<Type>& b\n"
			") const"
		) << "Unnecessary use of BlockILUCp preconditioner for diagonal "
			<< "matrix. "
			<< nl
			<< "Use BlockDiagonal preconditioner instead."
			<< abort(FatalError);
	}
}


template<class Type>
void tnbLib::BlockILUCpPrecon<Type>::decoupledPreconditionT
(
	Field<Type>& xT,
	const Field<Type>& bT
) const
{
	// Helper type definition of DecoupledCoeffField
	typedef DecoupledCoeffField<Type> DecoupledTypeCoeffField;

	if (!this->matrix_.diagonal())
	{
		// Get upper and lower matrix factors
		const DecoupledTypeCoeffField& Lower = extBlockMatrix_.extendedLower();
		const DecoupledTypeCoeffField& Upper = extBlockMatrix_.extendedUpper();

		// Execute preconditioning by LU substitution.
		// Note: lower, diag and upper must have same type as required by the
		// algorithm. This is handled by lowest possible promotion
		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				LUSubstituteT
				(
					xT,
					preconDiag_.asScalar(),
					Upper.asScalar(),
					Lower.asScalar(),
					bT
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				LUSubstituteT
				(
					xT,
					preconDiag_.asLinear(), // Promotes to linear
					Upper.asLinear(),
					Lower.asLinear(),
					bT
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (Upper.activeType() == blockCoeffBase::SCALAR)
			{
				LUSubstituteT
				(
					xT,
					preconDiag_.asLinear(),
					Upper.asLinear(), // Promotes to linear
					Lower.asLinear(), // Promotes to linear
					bT
				);
			}
			else if (Upper.activeType() == blockCoeffBase::LINEAR)
			{
				LUSubstituteT
				(
					xT,
					preconDiag_.asLinear(),
					Upper.asLinear(),
					Lower.asLinear(),
					bT
				);
			}
		}
		else
		{
			FatalErrorIn
			(
				"void BlockILUCpPrecon<Type>::decoupledPreconditionT\n"
				"(\n"
				"    Field<Type>& x,\n"
				"    const Field<Type>& T\n"
				") const"
			) << "Problem with coefficient type morphing."
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn
		(
			"void BlockILUCpPrecon<Type>::decoupledPreconditionT\n"
			"(\n"
			"    Field<Type>& x,\n"
			"    const Field<Type>& b\n"
			") const"
		) << "Unnecessary use of BlockILUCp preconditioner for diagonal "
			<< "matrix. "
			<< nl
			<< "Use BlockDiagonal preconditioner instead."
			<< abort(FatalError);
	}
}


// ************************************************************************* //