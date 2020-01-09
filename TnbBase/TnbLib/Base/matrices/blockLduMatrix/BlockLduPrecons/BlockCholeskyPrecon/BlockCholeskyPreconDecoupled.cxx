#include <BlockCholeskyPrecon.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::BlockCholeskyPrecon<Type>::calcDecoupledPreconDiag()
{
	typedef CoeffField<Type> TypeCoeffField;

	// Note: Assuming lower and upper triangle have the same active type

	if (this->matrix_.symmetric())
	{
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				diagMultiply
				(
					preconDiag_.asScalar(),
					UpperCoeff.asScalar()
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					UpperCoeff.asLinear()
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					UpperCoeff.asScalar()
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					UpperCoeff.asLinear()
				);
			}
		}
	}
	else // Asymmetric matrix
	{
		const TypeCoeffField& LowerCoeff = this->matrix_.lower();
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				diagMultiply
				(
					preconDiag_.asScalar(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar()
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear()
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar()
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				diagMultiply
				(
					preconDiag_.asLinear(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear()
				);
			}
		}
	}

	// Invert the diagonal
	// Note: since square diag type does not exist, simple inversion
	// covers all cases
	preconDiag_ = inv(preconDiag_);
}


template<class Type>
void tnbLib::BlockCholeskyPrecon<Type>::decoupledPrecondition
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	typedef CoeffField<Type> TypeCoeffField;

	// Note: Assuming lower and upper triangle have the same active type

	if (this->matrix_.symmetric())
	{
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asScalar(),
					UpperCoeff.asScalar(),
					b
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asScalar(),
					UpperCoeff.asLinear(),
					b
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asLinear(),
					UpperCoeff.asScalar(),
					b
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asLinear(),
					UpperCoeff.asLinear(),
					b
				);
			}
		}
	}
	else // Asymmetric matrix
	{
		const TypeCoeffField& LowerCoeff = this->matrix_.lower();
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asScalar(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar(),
					b
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asScalar(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear(),
					b
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asLinear(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar(),
					b
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiply
				(
					x,
					preconDiag_.asLinear(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear(),
					b
				);
			}
		}
	}
}


template<class Type>
void tnbLib::BlockCholeskyPrecon<Type>::decoupledPreconditionT
(
	Field<Type>& xT,
	const Field<Type>& bT
) const
{
	typedef CoeffField<Type> TypeCoeffField;

	// Note: Assuming lower and upper triangle have the same active type

	if (this->matrix_.symmetric())
	{
		precondition(xT, bT);
	}
	else // Asymmetric matrix
	{
		const TypeCoeffField& LowerCoeff = this->matrix_.lower();
		const TypeCoeffField& UpperCoeff = this->matrix_.upper();

		if (preconDiag_.activeType() == blockCoeffBase::SCALAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiplyTranspose
				(
					xT,
					preconDiag_.asScalar(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar(),
					bT
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiplyTranspose
				(
					xT,
					preconDiag_.asScalar(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear(),
					bT
				);
			}
		}
		else if (preconDiag_.activeType() == blockCoeffBase::LINEAR)
		{
			if (UpperCoeff.activeType() == blockCoeffBase::SCALAR)
			{
				ILUmultiplyTranspose
				(
					xT,
					preconDiag_.asLinear(),
					LowerCoeff.asScalar(),
					UpperCoeff.asScalar(),
					bT
				);
			}
			else if (UpperCoeff.activeType() == blockCoeffBase::LINEAR)
			{
				ILUmultiplyTranspose
				(
					xT,
					preconDiag_.asLinear(),
					LowerCoeff.asLinear(),
					UpperCoeff.asLinear(),
					bT
				);
			}
		}
	}
}


// ************************************************************************* //