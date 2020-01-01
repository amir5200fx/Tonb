#include <UniformDimensionedField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const IOobject& io,
	const dimensioned<Type>& dt
)
	:
	regIOobject(io),
	dimensioned<Type>(dt)
{}


template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const UniformDimensionedField<Type>& rdt
)
	:
	regIOobject(rdt),
	dimensioned<Type>(rdt)
{}


template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const IOobject& io
)
	:
	regIOobject(io),
	dimensioned<Type>(regIOobject::name(), dimless, pTraits<Type>::zero)
{
	dictionary dict(readStream(typeName));
	this->dimensions().reset(dict.lookup("dimensions"));
	this->value() = pTraits<Type>(dict.lookup("value"));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::UniformDimensionedField<Type>::~UniformDimensionedField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::UniformDimensionedField<Type>::writeData(Ostream& os) const
{
	os.writeKeyword("dimensions") << this->dimensions() << token::END_STATEMENT
		<< nl;
	os.writeKeyword("value") << this->value() << token::END_STATEMENT
		<< nl << nl;

	return (os.good());
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::UniformDimensionedField<Type>::operator=
(
	const UniformDimensionedField<Type>& rhs
	)
{
	dimensioned<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::UniformDimensionedField<Type>::operator=
(
	const dimensioned<Type>& rhs
	)
{
	dimensioned<Type>::operator=(rhs);
}


// ************************************************************************* //
