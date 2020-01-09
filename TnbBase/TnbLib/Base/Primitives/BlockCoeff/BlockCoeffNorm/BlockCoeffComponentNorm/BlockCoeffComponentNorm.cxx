#include <BlockCoeffComponentNorm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockCoeffComponentNorm<Type>::BlockCoeffComponentNorm
(
	const dictionary& dict
)
	:
	BlockCoeffNorm<Type>(dict),
	dict_(dict),
	cmpt_(readInt(this->dict().lookup("normComponent")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::scalar tnbLib::BlockCoeffComponentNorm<Type>::normalize
(
	const tnbLib::BlockCoeff<Type>& a
)
{
	return mag(a.component(cmpt_));
}


template<class Type>
void tnbLib::BlockCoeffComponentNorm<Type>::coeffMag
(
	const tnbLib::CoeffField<Type>& a,
	tnbLib::Field<scalar>& b
)
{
	b = mag(a.component(cmpt_));
}


// ************************************************************************* //