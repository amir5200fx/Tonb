#include <sphericalTensorCoeffField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CoeffField<tnbLib::sphericalTensor>::CoeffField(const label size)
	:
	DecoupledCoeffField<sphericalTensor>(size)
{}


tnbLib::CoeffField<tnbLib::sphericalTensor>::CoeffField
(
	const CoeffField<sphericalTensor>& f
)
	:
	DecoupledCoeffField<sphericalTensor>(f)
{}


tnbLib::CoeffField<tnbLib::sphericalTensor>::CoeffField
(
	const DecoupledCoeffField<sphericalTensor>& f
)
	:
	DecoupledCoeffField<sphericalTensor>(f)
{}


tnbLib::CoeffField<tnbLib::sphericalTensor>::CoeffField
(
	const tmp<DecoupledCoeffField<sphericalTensor> >& tf
)
	:
	DecoupledCoeffField<sphericalTensor>(tf())
{}


tnbLib::CoeffField<tnbLib::sphericalTensor>::CoeffField(Istream& is)
	:
	DecoupledCoeffField<sphericalTensor>(is)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const CoeffField<sphericalTensor>& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const tmp<CoeffField<sphericalTensor> >& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const CoeffField<sphericalTensor>::scalarTypeField& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const tmp<CoeffField<sphericalTensor>::scalarTypeField>& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const CoeffField<sphericalTensor>::linearTypeField& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


void tnbLib::CoeffField<tnbLib::sphericalTensor>::operator=
(
	const tmp<CoeffField<sphericalTensor>::linearTypeField>& f
	)
{
	DecoupledCoeffField<sphericalTensor>::operator=(f);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CoeffField<sphericalTensor>& f
	)
{
	const DecoupledCoeffField<sphericalTensor>& df = f;
	return operator<<(os, df);
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<sphericalTensor> >& tf
	)
{
	const DecoupledCoeffField<sphericalTensor>& df = tf();
	os << df;
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

tnbLib::tmp<tnbLib::CoeffField<tnbLib::sphericalTensor> > tnbLib::inv
(
	const CoeffField<sphericalTensor>& f
)
{
	const DecoupledCoeffField<sphericalTensor>& df = f;

	return tmp<CoeffField<sphericalTensor> >
		(
			new CoeffField<sphericalTensor>(inv(df)())
			);
}


template<>
void tnbLib::multiply
(
	sphericalTensorField& f,
	const CoeffField<sphericalTensor>& f1,
	const sphericalTensor& f2
)
{
	const DecoupledCoeffField<sphericalTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	sphericalTensorField& f,
	const CoeffField<sphericalTensor>& f1,
	const sphericalTensorField& f2
)
{
	const DecoupledCoeffField<sphericalTensor>& df1 = f1;

	multiply(f, df1, f2);
}


template<>
void tnbLib::multiply
(
	sphericalTensorField& f,
	const sphericalTensorField& f1,
	const CoeffField<sphericalTensor>& f2
)
{
	const DecoupledCoeffField<sphericalTensor>& df2 = f2;

	multiply(f, f1, df2);
}


// ************************************************************************* //