#include <tensorCoeffField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CoeffField<tnbLib::tensor>::CoeffField(const label size)
	:
	DecoupledCoeffField<tensor>(size)
{}


tnbLib::CoeffField<tnbLib::tensor>::CoeffField(const CoeffField<tensor>& f)
	:
	DecoupledCoeffField<tensor>(f)
{}


tnbLib::CoeffField<tnbLib::tensor>::CoeffField
(
	const DecoupledCoeffField<tensor>& f
)
	:
	DecoupledCoeffField<tensor>(f)
{}


tnbLib::CoeffField<tnbLib::tensor>::CoeffField
(
	const tmp<DecoupledCoeffField<tensor> >& tf
)
	:
	DecoupledCoeffField<tensor>(tf())
{}


tnbLib::CoeffField<tnbLib::tensor>::CoeffField(Istream& is)
	:
	DecoupledCoeffField<tensor>(is)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::tensor>::operator=(const CoeffField<tensor>& f)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::tensor>::operator=
(
	const tmp<CoeffField<tensor> >& f
	)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::tensor>::operator=
(
	const CoeffField<tensor>::scalarTypeField& f
	)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::tensor>::operator=
(
	const tmp<CoeffField<tensor>::scalarTypeField>& f
	)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::tensor>::operator=
(
	const CoeffField<tensor>::linearTypeField& f
	)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::tensor>::operator=
(
	const tmp<CoeffField<tensor>::linearTypeField>& f
	)
{
	DecoupledCoeffField<tensor>::operator=(f);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CoeffField<tensor>& f)
{
	const DecoupledCoeffField<tensor>& df = f;
	return operator<<(os, df);
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<tensor> >& tf
	)
{
	const DecoupledCoeffField<tensor>& df = tf();
	os << df;
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

template<>
tnbLib::tmp<tnbLib::CoeffField<tnbLib::tensor> > tnbLib::inv
(
	const CoeffField<tensor>& f
)
{
	const DecoupledCoeffField<tensor>& df = f;

	return tmp<CoeffField<tensor> >(new CoeffField<tensor>(inv(df)()));
}


template<>
void tnbLib::multiply
(
	tensorField& f,
	const CoeffField<tensor>& f1,
	const tensor& f2
)
{
	const DecoupledCoeffField<tensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	tensorField& f,
	const CoeffField<tensor>& f1,
	const tensorField& f2
)
{
	const DecoupledCoeffField<tensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	tensorField& f,
	const tensorField& f1,
	const CoeffField<tensor>& f2
)
{
	const DecoupledCoeffField<tensor>& df2 = f2;

	multiply(f, f1, df2);
}


// ************************************************************************* //