#include <scalarBlockCoeff.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::scalar>::BlockCoeff()
	:
	scalarCoeff_(pTraits<scalar>::zero)
{}


tnbLib::BlockCoeff<tnbLib::scalar>::BlockCoeff(const BlockCoeff<scalar>& f)
	:
	scalarCoeff_(f.scalarCoeff_)
{}


tnbLib::BlockCoeff<tnbLib::scalar>::BlockCoeff(Istream& is)
	:
	scalarCoeff_(readScalar(is))
{}


tnbLib::BlockCoeff<tnbLib::scalar> tnbLib::BlockCoeff<tnbLib::scalar>::clone() const
{
	return BlockCoeff<scalar>(*this);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::BlockCoeff<tnbLib::scalar>::~BlockCoeff()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::blockCoeffBase::activeLevel
tnbLib::BlockCoeff<tnbLib::scalar>::activeType() const
{
	return blockCoeffBase::SCALAR;
}


tnbLib::scalar tnbLib::BlockCoeff<tnbLib::scalar>::component(const direction) const
{
	return scalarCoeff_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::BlockCoeff<tnbLib::scalar>::operator=(const BlockCoeff<scalar>& f)
{
	if (this == &f)
	{
		FatalErrorIn
		(
			"BlockCoeff<scalar>::operator=(const BlockCoeff<scalar>&)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	scalarCoeff_ = f.scalarCoeff_;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const BlockCoeff<scalar>& f)
{
	os << f.scalarCoeff_;

	return os;
}


// ************************************************************************* //