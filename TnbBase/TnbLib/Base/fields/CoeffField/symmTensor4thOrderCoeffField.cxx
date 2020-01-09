#include <symmTensor4thOrderCoeffField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::CoeffField(const label size)
	:
	DecoupledCoeffField<symmTensor4thOrder>(size)
{}


tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::CoeffField
(
	const CoeffField<symmTensor4thOrder>& f
)
	:
	DecoupledCoeffField<symmTensor4thOrder>(f)
{}


tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::CoeffField
(
	const DecoupledCoeffField<symmTensor4thOrder>& f
)
	:
	DecoupledCoeffField<symmTensor4thOrder>(f)
{}


tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::CoeffField
(
	const tmp<DecoupledCoeffField<symmTensor4thOrder> >& tf
)
	:
	DecoupledCoeffField<symmTensor4thOrder>(tf())
{}


tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::CoeffField(Istream& is)
	:
	DecoupledCoeffField<symmTensor4thOrder>(is)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const CoeffField<symmTensor4thOrder>& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const tmp<CoeffField<symmTensor4thOrder> >& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const CoeffField<symmTensor4thOrder>::scalarTypeField& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const tmp<CoeffField<symmTensor4thOrder>::scalarTypeField>& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const CoeffField<symmTensor4thOrder>::linearTypeField& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor4thOrder>::operator=
(
	const tmp<CoeffField<symmTensor4thOrder>::linearTypeField>& f
	)
{
	DecoupledCoeffField<symmTensor4thOrder>::operator=(f);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CoeffField<symmTensor4thOrder>& f
	)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df = f;
	return operator<<(os, df);
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<symmTensor4thOrder> >& tf
	)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df = tf();
	os << df;
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

tnbLib::tmp<tnbLib::CoeffField<tnbLib::symmTensor4thOrder> > tnbLib::inv
(
	const CoeffField<symmTensor4thOrder>& f
)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df = f;

	return tmp<CoeffField<symmTensor4thOrder> >
		(
			new CoeffField<symmTensor4thOrder>(inv(df)())
			);
}


template<>
void tnbLib::multiply
(
	symmTensor4thOrderField& f,
	const CoeffField<symmTensor4thOrder>& f1,
	const symmTensor4thOrder& f2
)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	symmTensor4thOrderField& f,
	const CoeffField<symmTensor4thOrder>& f1,
	const symmTensor4thOrderField& f2
)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	symmTensor4thOrderField& f,
	const symmTensor4thOrderField& f1,
	const CoeffField<symmTensor4thOrder>& f2
)
{
	const DecoupledCoeffField<symmTensor4thOrder>& df2 = f2;

	multiply(f, f1, df2);
}


// ************************************************************************* //