#include <scalarCoeffField.hxx>

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

const char* const tnbLib::CoeffField<tnbLib::scalar>::typeName("CoeffField");


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::blockCoeffBase::activeLevel
tnbLib::CoeffField<tnbLib::scalar>::activeType() const
{
	return blockCoeffBase::SCALAR;
}


tnbLib::tmp<tnbLib::CoeffField<tnbLib::scalar> >
tnbLib::CoeffField<tnbLib::scalar>::transpose() const
{
	return tmp<CoeffField<scalar> >(new CoeffField<scalar>(*this));
}


const tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asScalar() const
{
	return *this;
}


tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asScalar()
{
	return *this;
}


const tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asLinear() const
{
	return *this;
}


tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asLinear()
{
	return *this;
}


const tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asSquare() const
{
	return *this;
}


tnbLib::scalarField&
tnbLib::CoeffField<tnbLib::scalar>::asSquare()
{
	return *this;
}


tnbLib::BlockCoeff<tnbLib::scalar>
tnbLib::CoeffField<tnbLib::scalar>::getCoeff(const label index) const
{
	BlockCoeff<scalar> result;

	result.asScalar() = (operator[](index));

	return result;
}


void tnbLib::CoeffField<tnbLib::scalar>::setCoeff
(
	const label index,
	const BlockCoeff<scalar>& coeff
)
{
	operator[](index) = coeff.asScalar();
}


void tnbLib::CoeffField<tnbLib::scalar>::getSubset
(
	CoeffField<scalar>& f,
	const label start,
	const label size
) const
{
	// Check sizes
	if (f.size() != size)
	{
		FatalErrorIn
		(
			"void tnbLib::CoeffField<tnbLib::scalar>::getSubset\n"
			"(\n"
			"    CoeffField<scalar>& f,\n"
			"    const label start,\n"
			"    const label size\n"
			") const"
		) << "Incompatible sizes: " << f.size() << " and " << size
			<< abort(FatalError);
	}

	const scalarField& localF = *this;

	forAll(f, fI)
	{
		f[fI] = localF[start + fI];
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::getSubset
(
	CoeffField<scalar>& f,
	const labelList& addr
) const
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"void tnbLib::CoeffField<tnbLib::scalar>::getSubset\n"
			"(\n"
			"    CoeffField<scalar>& f,\n"
			"    const labelList addr\n"
			") const"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	const scalarField& localF = *this;

	forAll(f, fI)
	{
		f[fI] = localF[addr[fI]];
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::setSubset
(
	const CoeffField<scalar>& f,
	const label start,
	const label size
)
{
	// Check sizes
	if (f.size() != size)
	{
		FatalErrorIn
		(
			"void tnbLib::CoeffField<tnbLib::scalar>::setSubset\n"
			"(\n"
			"     const CoeffField<scalar>& f,\n"
			"    const label start,\n"
			"    const label size\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << size
			<< abort(FatalError);
	}

	scalarField& localF = *this;

	forAll(f, fI)
	{
		localF[start + fI] = f[fI];
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::setSubset
(
	const CoeffField<scalar>& f,
	const labelList& addr
)
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"void tnbLib::CoeffField<tnbLib::scalar>::setSubset\n"
			"(\n"
			"    const CoeffField<scalar>& f,\n"
			"    const labelList addr\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	scalarField& localF = this->asScalar();

	forAll(f, fI)
	{
		localF[addr[fI]] = f[fI];
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::zeroOutSubset
(
	const label start,
	const label size
)
{
	scalarField& localF = *this;

	for (label ffI = 0; ffI < size; ffI++)
	{
		localF[start + ffI] = pTraits<scalar>::zero;
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::zeroOutSubset
(
	const labelList& addr
)
{
	scalarField& localF = *this;

	forAll(addr, ffI)
	{
		localF[addr[ffI]] = pTraits<scalar>::zero;
	}
}


void tnbLib::CoeffField<tnbLib::scalar>::addSubset
(
	const CoeffField<scalar>& f,
	const labelList& addr
)
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"void tnbLib::CoeffField<tnbLib::scalar>::addSubset\n"
			"(\n"
			"    const CoeffField<scalar>& f,\n"
			"    const labelList addr\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	scalarField& localF = this->asScalar();

	forAll(f, fI)
	{
		localF[addr[fI]] += f[fI];
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::CoeffField<tnbLib::scalar>::operator=(const scalarField& f)
{
	scalarField::operator=(f);
}


void tnbLib::CoeffField<tnbLib::scalar>::operator=(const tmp<scalarField>& tf)
{
	scalarField::operator=(tf);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const CoeffField<scalar>& f)
{
	os << static_cast<const scalarField&>(f);

	return os;
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<CoeffField<scalar> >& tf
	)
{
	os << tf();
	tf.clear();
	return os;
}


/* * * * * * * * * * * * * * * * Global functions  * * * * * * * * * * * * * */

template<>
tnbLib::tmp<tnbLib::CoeffField<tnbLib::scalar> >
tnbLib::inv(const CoeffField<scalar>& f)
{
	tmp<CoeffField<scalar> > tresult(new CoeffField<scalar>(f.size()));
	scalarField& result = tresult();
	result = 1.0 / f;

	return tresult;
}


template<>
void tnbLib::negate
(
	CoeffField<scalar>& f,
	const CoeffField<scalar>& f1
)
{
	f = f1;
	f.negate();
}


template<>
void tnbLib::multiply
(
	scalarField& f,
	const CoeffField<scalar>& f1,
	const scalar& f2
)
{
	const scalarField& sf = f1;
	f = sf * f2;
}


template<>
void tnbLib::multiply
(
	scalarField& f,
	const CoeffField<scalar>& f1,
	const scalarField& f2
)
{
	const scalarField& sf = f1;
	f = sf * f2;
}


template<>
void tnbLib::multiply
(
	scalarField& f,
	const scalarField& f1,
	const CoeffField<scalar>& f2
)
{
	const scalarField& sf = f2;
	f = f1 * sf;
}


// ************************************************************************* //