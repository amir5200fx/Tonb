#include <BlockCoeffMaxNorm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockCoeffMaxNorm<Type>::BlockCoeffMaxNorm
(
	const dictionary& dict
)
	:
	BlockCoeffNorm<Type>(dict),
	dict_(dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::scalar tnbLib::BlockCoeffMaxNorm<Type>::normalize
(
	const tnbLib::BlockCoeff<Type>& a
)
{
	if (a.activeType() == BlockCoeff<Type>::SCALAR)
	{
		return mag(a.asScalar());
	}
	else if (a.activeType() == BlockCoeff<Type>::LINEAR)
	{
		return cmptMax(cmptMag(a.asLinear()));
	}
	else if (a.activeType() == BlockCoeff<Type>::SQUARE)
	{
		return cmptMax(cmptMag(a.asSquare()));
	}
	else
	{
		FatalErrorIn
		(
			"scalar BlockCoeffMaxNorm<Type>(const BlockCoeff<Type>& b)"
		) << "Unknown type" << abort(FatalError);

		return 0;
	}
}


template<class Type>
void tnbLib::BlockCoeffMaxNorm<Type>::coeffMag
(
	const tnbLib::CoeffField<Type>& a,
	tnbLib::Field<scalar>& b
)
{
	if (a.activeType() == BlockCoeff<Type>::SCALAR)
	{
		b = mag(a.asScalar());
	}
	else if (a.activeType() == BlockCoeff<Type>::LINEAR)
	{
		b = cmptMax(cmptMag(a.asLinear()));
	}
	else if (a.activeType() == BlockCoeff<Type>::SQUARE)
	{
		b = cmptMax(cmptMag(a.asSquare()));
	}
	else
	{
		FatalErrorIn
		(
			"scalar BlockCoeffMaxNorm<Type>(const BlockCoeff<Type>& b)"
		) << "Unknown type" << abort(FatalError);
	}
}


// ************************************************************************* //