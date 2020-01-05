#include <diagTensorCoeffField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CoeffField<tnbLib::diagTensor>::CoeffField(const label size)
	:
	DecoupledCoeffField<diagTensor>(size)
{}


tnbLib::CoeffField<tnbLib::diagTensor>::CoeffField
(
	const CoeffField<diagTensor>& f
)
	:
	DecoupledCoeffField<diagTensor>(f)
{}


tnbLib::CoeffField<tnbLib::diagTensor>::CoeffField
(
	const DecoupledCoeffField<diagTensor>& f
)
	:
	DecoupledCoeffField<diagTensor>(f)
{}


tnbLib::CoeffField<tnbLib::diagTensor>::CoeffField
(
	const tmp<DecoupledCoeffField<diagTensor> >& tf
)
	:
	DecoupledCoeffField<diagTensor>(tf())
{}


tnbLib::CoeffField<tnbLib::diagTensor>::CoeffField(Istream& is)
	:
	DecoupledCoeffField<diagTensor>(is)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const CoeffField<diagTensor>& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const tmp<CoeffField<diagTensor> >& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const CoeffField<diagTensor>::scalarTypeField& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const tmp<CoeffField<diagTensor>::scalarTypeField>& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const CoeffField<diagTensor>::linearTypeField& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::diagTensor>::operator=
(
	const tmp<CoeffField<diagTensor>::linearTypeField>& f
	)
{
	DecoupledCoeffField<diagTensor>::operator=(f);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CoeffField<diagTensor>& f)
{
	const DecoupledCoeffField<diagTensor>& df = f;
	return operator<<(os, df);
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<diagTensor> >& tf
	)
{
	const DecoupledCoeffField<diagTensor>& df = tf();
	os << df;
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

tnbLib::tmp<tnbLib::CoeffField<tnbLib::diagTensor> > tnbLib::inv
(
	const CoeffField<diagTensor>& f
)
{
	const DecoupledCoeffField<diagTensor>& df = f;

	return tmp<CoeffField<diagTensor> >
		(
			new CoeffField<diagTensor>(inv(df)())
			);
}


template<>
void tnbLib::multiply
(
	diagTensorField& f,
	const CoeffField<diagTensor>& f1,
	const diagTensor& f2
)
{
	const DecoupledCoeffField<diagTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	diagTensorField& f,
	const CoeffField<diagTensor>& f1,
	const diagTensorField& f2
)
{
	const DecoupledCoeffField<diagTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	diagTensorField& f,
	const diagTensorField& f1,
	const CoeffField<diagTensor>& f2
)
{
	const DecoupledCoeffField<diagTensor>& df2 = f2;

	multiply(f, f1, df2);
}


// ************************************************************************* //