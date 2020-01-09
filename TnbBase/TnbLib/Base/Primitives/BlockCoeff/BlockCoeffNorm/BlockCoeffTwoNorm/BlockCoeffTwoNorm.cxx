#include <BlockCoeffTwoNorm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockCoeffTwoNorm<Type>::BlockCoeffTwoNorm
(
	const dictionary& dict
)
	:
	BlockCoeffNorm<Type>(dict),
	dict_(dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::scalar tnbLib::BlockCoeffTwoNorm<Type>::normalize
(
	const tnbLib::BlockCoeff<Type>& a
)
{
	if (a.activeType() == tnbLib::BlockCoeff<Type>::SCALAR)
	{
		return mag(a.asScalar());
	}
	else if (a.activeType() == tnbLib::BlockCoeff<Type>::LINEAR)
	{
		return mag(a.asLinear());
	}
	else if (a.activeType() == tnbLib::BlockCoeff<Type>::SQUARE)
	{
		return mag(a.asSquare());
	}
	else
	{
		FatalErrorIn
		(
			"scalar BlockCoeffTwoNorm<Type>(const BlockCoeff<Type>& a)"
		) << "Unknown type" << abort(FatalError);

		return 0;
	}

	// Dummy return
	return 0;
}


template<class Type>
void tnbLib::BlockCoeffTwoNorm<Type>::coeffMag
(
	const tnbLib::CoeffField<Type>& a,
	tnbLib::Field<scalar>& b
)
{
	if (a.activeType() == tnbLib::BlockCoeff<Type>::SCALAR)
	{
		b = mag(a.asScalar());
	}
	else if (a.activeType() == tnbLib::BlockCoeff<Type>::LINEAR)
	{
		b = mag(a.asLinear());
	}
	else if (a.activeType() == tnbLib::BlockCoeff<Type>::SQUARE)
	{
		b = mag(a.asSquare());
	}
	else
	{
		FatalErrorIn
		(
			"scalar BlockCoeffTwoNorm<Type>(const BlockCoeff<Type>& b)"
		) << "Unknown type" << abort(FatalError);
	}
}


// ************************************************************************* //