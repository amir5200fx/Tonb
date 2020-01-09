#include <symmTensorCoeffField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CoeffField<tnbLib::symmTensor>::CoeffField(const label size)
	:
	DecoupledCoeffField<symmTensor>(size)
{}


tnbLib::CoeffField<tnbLib::symmTensor>::CoeffField
(
	const CoeffField<symmTensor>& f
)
	:
	DecoupledCoeffField<symmTensor>(f)
{}


tnbLib::CoeffField<tnbLib::symmTensor>::CoeffField
(
	const DecoupledCoeffField<symmTensor>& f
)
	:
	DecoupledCoeffField<symmTensor>(f)
{}


tnbLib::CoeffField<tnbLib::symmTensor>::CoeffField
(
	const tmp<DecoupledCoeffField<symmTensor> >& tf
)
	:
	DecoupledCoeffField<symmTensor>(tf())
{}


tnbLib::CoeffField<tnbLib::symmTensor>::CoeffField(Istream& is)
	:
	DecoupledCoeffField<symmTensor>(is)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const CoeffField<symmTensor>& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const tmp<CoeffField<symmTensor> >& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const CoeffField<symmTensor>::scalarTypeField& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const tmp<CoeffField<symmTensor>::scalarTypeField>& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const CoeffField<symmTensor>::linearTypeField& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::symmTensor>::operator=
(
	const tmp<CoeffField<symmTensor>::linearTypeField>& f
	)
{
	DecoupledCoeffField<symmTensor>::operator=(f);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CoeffField<symmTensor>& f)
{
	const DecoupledCoeffField<symmTensor>& df = f;
	return operator<<(os, df);
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<symmTensor> >& tf
	)
{
	const DecoupledCoeffField<symmTensor>& df = tf();
	os << df;
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

tnbLib::tmp<tnbLib::CoeffField<tnbLib::symmTensor> > tnbLib::inv
(
	const CoeffField<symmTensor>& f
)
{
	const DecoupledCoeffField<symmTensor>& df = f;

	return tmp<CoeffField<symmTensor> >
		(
			new CoeffField<symmTensor>(inv(df)())
			);
}


template<>
void tnbLib::multiply
(
	symmTensorField& f,
	const CoeffField<symmTensor>& f1,
	const symmTensor& f2
)
{
	const DecoupledCoeffField<symmTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	symmTensorField& f,
	const CoeffField<symmTensor>& f1,
	const symmTensorField& f2
)
{
	const DecoupledCoeffField<symmTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	symmTensorField& f,
	const symmTensorField& f1,
	const CoeffField<symmTensor>& f2
)
{
	const DecoupledCoeffField<symmTensor>& df2 = f2;

	multiply(f, f1, df2);
}


// ************************************************************************* //