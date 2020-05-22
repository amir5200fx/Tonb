#include <AverageIOField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AverageIOField<Type>::AverageIOField
(
	const IOobject& io
)
	:
	regIOobject(io)
{
	readStream(typeName) >> average_;
	readStream(typeName) >> static_cast<Field<Type>&>(*this);
	close();
}


template<class Type>
tnbLib::AverageIOField<Type>::AverageIOField
(
	const IOobject& io,
	const label size
)
	:
	regIOobject(io),
	Field<Type>(size),
	average_(pTraits<Type>::zero)
{}


template<class Type>
tnbLib::AverageIOField<Type>::AverageIOField
(
	const IOobject& io,
	const Type& average,
	const Field<Type>& f
)
	:
	regIOobject(io),
	Field<Type>(f),
	average_(average)
{
	if (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
	{
		readStream(typeName)
			>> average_
			>> static_cast<Field<Type>&>(*this);
		close();
	}
}


template<class Type>
bool tnbLib::AverageIOField<Type>::writeData(Ostream& os) const
{
	os << average_
		<< token::NL
		<< static_cast<const Field<Type>&>(*this);

	return os.good();
}


// ************************************************************************* //