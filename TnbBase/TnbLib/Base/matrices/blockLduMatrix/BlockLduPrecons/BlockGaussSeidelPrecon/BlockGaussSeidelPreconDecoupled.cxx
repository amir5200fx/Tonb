#include <BlockGaussSeidelPrecon.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockGaussSeidelPrecon<Type>::calcDecoupledInvDiag()
{
	// Get reference to diagonal and obtain inverse by casting
	typedef CoeffField<Type> TypeCoeffField;

	const TypeCoeffField& d = this->matrix_.diag();
	const DecoupledCoeffField<Type>& dd = d;

	invDiag_ = CoeffField<Type>(inv(dd)());
}


template<class Type>
void tnbLib::BlockGaussSeidelPrecon<Type>::decoupledPrecondition
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	typedef DecoupledCoeffField<Type> TypeCoeffField;

	if (this->matrix_.diagonal())
	{
		if (invDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			x = invDiag_.asScalar()*b;
		}
		else if (invDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			x = cmptMultiply(invDiag_.asLinear(), b);
		}
	}
	else if (this->matrix_.symmetric() || this->matrix_.asymmetric())
	{
		const TypeCoeffField& LowerCoeff = this->matrix_.lower();
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		// Note
		// Gauss-Seidel loops need to be executed in the specific
		// order with direct access to the coefficients which can be
		// of morphed type.  Under normal circumstances, the
		// operations are not inter-leaved and the decision can be
		// made at the beginning of the loop.  Here, the order needs
		// to be enforced without the per-element if-condition, which
		// makes for ugly code.  HJ, 19/May/2005

		// Note: Assuming lower and upper triangle have the same active type

		if (invDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					BlockSweep
					(
						x,
						invDiag_.asScalar(),
						LowerCoeff.asScalar(),
						UpperCoeff.asScalar(),
						b
					);
				}
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					BlockSweep
					(
						x,
						invDiag_.asScalar(),
						LowerCoeff.asLinear(),
						UpperCoeff.asLinear(),
						b
					);
				}
			}
		}
		else if (invDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					BlockSweep
					(
						x,
						invDiag_.asLinear(),
						LowerCoeff.asScalar(),
						UpperCoeff.asScalar(),
						b
					);
				}
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					BlockSweep
					(
						x,
						invDiag_.asLinear(),
						LowerCoeff.asLinear(),
						UpperCoeff.asLinear(),
						b
					);
				}
			}
		}
		else
		{
			FatalErrorIn
			(
				"void BlockGaussSeidelPrecon<Type>::precondition\n"
				"(\n"
				"    Field<Type>& x,\n"
				"    const Field<Type>& b\n"
				") const"
			) << "Problem with coefficient type morphing."
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn
		(
			"void BlockGaussSeidelPrecon<Type>::precondition\n"
			"(\n"
			"    Field<Type>& x,\n"
			"    const Field<Type>& b\n"
			") const"
		) << "cannot solve incomplete matrix, no diagonal"
			<< abort(FatalError);
	}
}


template<class Type>
void tnbLib::BlockGaussSeidelPrecon<Type>::decoupledPreconditionT
(
	Field<Type>& xT,
	const Field<Type>& bT
) const
{
	typedef DecoupledCoeffField<Type> TypeCoeffField;

	if (this->matrix_.diagonal())
	{
		if (invDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			xT = invDiag_.asScalar()*bT;
		}
		else if (invDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			xT = cmptMultiply(invDiag_.asLinear(), bT);
		}
	}
	else if (this->matrix_.symmetric() || this->matrix_.asymmetric())
	{
		const TypeCoeffField& LowerCoeff = this->matrix_.lower();
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		// Note
		// Gauss-Seidel loops need to be executed in the specific
		// order with direct access to the coefficients which can be
		// of morphed type.  Under normal circumstances, the
		// operations are not inter-leaved and the decision can be
		// made at the beginning of the loop.  Here, the order needs
		// to be enforced without the per-element if-condition, which
		// makes for ugly code.  HJ, 19/May/2005

		// Note: Assuming lower and upper triangle have the same active type

		if (invDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					// Transpose multiplication - swap lower and upper coeff
					BlockSweep
					(
						xT,
						invDiag_.asScalar(),
						UpperCoeff.asScalar(),
						LowerCoeff.asScalar(),
						bT
					);
				}
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					// Transpose multiplication - swap lower and upper coeff
					BlockSweep
					(
						xT,
						invDiag_.asScalar(),
						UpperCoeff.asLinear(),
						LowerCoeff.asLinear(),
						bT
					);
				}
			}
		}
		else if (invDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					// Transpose multiplication - swap lower and upper coeff
					BlockSweep
					(
						xT,
						invDiag_.asLinear(),
						UpperCoeff.asScalar(),
						LowerCoeff.asScalar(),
						bT
					);
				}
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				for (label sweep = 0; sweep < nSweeps_; sweep++)
				{
					// Transpose multiplication - swap lower and upper coeff
					BlockSweep
					(
						xT,
						invDiag_.asLinear(),
						UpperCoeff.asLinear(),
						LowerCoeff.asLinear(),
						bT
					);
				}
			}
		}
		else
		{
			FatalErrorIn
			(
				"void BlockGaussSeidelPrecon<Type>::preconditionT\n"
				"(\n"
				"    Field<Type>& xT,\n"
				"    const Field<Type>& bT\n"
				") const"
			) << "Problem with coefficient type morphing."
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn
		(
			"void BlockGaussSeidelPrecon<Type>::preconditionT\n"
			"(\n"
			"    Field<Type>& xT,\n"
			"    const Field<Type>& bT\n"
			") const"
		) << "cannot solve incomplete matrix, no diagonal"
			<< abort(FatalError);
	}
}


// ************************************************************************* //