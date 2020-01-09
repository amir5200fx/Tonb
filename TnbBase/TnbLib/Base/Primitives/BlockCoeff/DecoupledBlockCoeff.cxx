#include <DecoupledBlockCoeff.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
typename tnbLib::DecoupledBlockCoeff<Type>::scalarType&
tnbLib::DecoupledBlockCoeff<Type>::toScalar()
{
	if (!scalarCoeffPtr_)
	{
		// Debug check: demotion
		if (linearCoeffPtr_)
		{
			FatalErrorIn
			(
				"DecoupledBlockCoeff<Type>::scalarType& "
				"DecoupledBlockCoeff<Type>::toScalar()"
			) << "Detected demotion to scalar.  Probably an error"
				<< abort(FatalError);
		}

		scalarCoeffPtr_ = new scalarType(pTraits<scalarType>::zero);
	}

	return *scalarCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledBlockCoeff<Type>::linearType&
tnbLib::DecoupledBlockCoeff<Type>::toLinear()
{
	if (!linearCoeffPtr_)
	{
		linearCoeffPtr_ = new linearType(pTraits<linearType>::zero);

		// If scalar is active, promote to linear
		if (scalarCoeffPtr_)
		{
			*linearCoeffPtr_ = (*scalarCoeffPtr_)*pTraits<linearType>::one;
			deleteDemandDrivenData(scalarCoeffPtr_);
		}
	}

	return *linearCoeffPtr_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::DecoupledBlockCoeff<Type>::DecoupledBlockCoeff()
	:
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL)
{}


template<class Type>
tnbLib::DecoupledBlockCoeff<Type>::DecoupledBlockCoeff
(
	const DecoupledBlockCoeff<Type>& f
)
	:
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL)
{
	if (f.scalarCoeffPtr_)
	{
		scalarCoeffPtr_ = new scalarType(*(f.scalarCoeffPtr_));
	}
	else if (f.linearCoeffPtr_)
	{
		linearCoeffPtr_ = new linearType(*(f.linearCoeffPtr_));
	}
}


template<class Type>
tnbLib::DecoupledBlockCoeff<Type>::DecoupledBlockCoeff(Istream& is)
	:
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL)
{
	// Read keyword and pick up allocated field
	word key(is);

	if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::UNALLOCATED]
			)
	{
	}
	else if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::SCALAR]
			)
	{
		scalarCoeffPtr_ = new scalarType(readScalar(is));
	}
	else if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::LINEAR]
			)
	{
		linearCoeffPtr_ = new linearType(is);
	}
	else
	{
		FatalIOErrorIn
		(
			"DecoupledBlockCoeff<Type>::DecoupledBlockCoeff(Istream& is)",
			is
		) << "invalid keyword while reading: " << key
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::DecoupledBlockCoeff<Type> tnbLib::DecoupledBlockCoeff<Type>::clone() const
{
	return DecoupledBlockCoeff<Type>(*this);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::DecoupledBlockCoeff<Type>::~DecoupledBlockCoeff()
{
	this->clear();
}


template<class Type>
void tnbLib::DecoupledBlockCoeff<Type>::clear()
{
	deleteDemandDrivenData(scalarCoeffPtr_);
	deleteDemandDrivenData(linearCoeffPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::blockCoeffBase::activeLevel
tnbLib::DecoupledBlockCoeff<Type>::activeType() const
{
	if (scalarCoeffPtr_)
	{
		return blockCoeffBase::SCALAR;
	}
	else if (linearCoeffPtr_)
	{
		return blockCoeffBase::LINEAR;
	}
	else
	{
		return blockCoeffBase::UNALLOCATED;
	}
}


template<class Type>
void tnbLib::DecoupledBlockCoeff<Type>::checkActive() const
{
	label nActive = 0;

	if (scalarCoeffPtr_) nActive++;
	if (linearCoeffPtr_) nActive++;

	if (nActive > 1)
	{
		FatalErrorIn
		(
			"void tnbLib::DecoupledBlockCoeff<Type>::checkActive() const"
		) << "Activation/deactivation error.  nActive = " << nActive
			<< abort(FatalError);
	}
}


template<class Type>
const typename tnbLib::DecoupledBlockCoeff<Type>::scalarType&
tnbLib::DecoupledBlockCoeff<Type>::asScalar() const
{
	if (!scalarCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledBlockCoeff<Type>::scalarType& "
			"DecoupledBlockCoeff<Type>::asScalar()"
		) << "Requested scalar but active type is: "
			<< blockCoeffBase::activeLevelNames_[this->activeType()]
			<< ".  This is not allowed."
			<< abort(FatalError);
	}

	return *scalarCoeffPtr_;
}


template<class Type>
const typename tnbLib::DecoupledBlockCoeff<Type>::linearType&
tnbLib::DecoupledBlockCoeff<Type>::asLinear() const
{
	if (!linearCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledBlockCoeff<Type>::linearType& "
			"DecoupledBlockCoeff<Type>::asLinear()"
		) << "Requested linear but active type is: "
			<< blockCoeffBase::activeLevelNames_[this->activeType()]
			<< ".  This is not allowed."
			<< abort(FatalError);
	}

	return *linearCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledBlockCoeff<Type>::scalarType&
tnbLib::DecoupledBlockCoeff<Type>::asScalar()
{
	if (linearCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledBlockCoeff<Type>::scalarType& "
			"DecoupledBlockCoeff<Type>::asScalar()"
		) << "Requested scalar but active type is: "
			<< blockCoeffBase::activeLevelNames_[this->activeType()]
			<< ".  This is not allowed."
			<< abort(FatalError);
	}

	if (!scalarCoeffPtr_)
	{
		return this->toScalar();
	}

	return *scalarCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledBlockCoeff<Type>::linearType&
tnbLib::DecoupledBlockCoeff<Type>::asLinear()
{
	if (!linearCoeffPtr_)
	{
		return this->toLinear();
	}

	return *linearCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledBlockCoeff<Type>::scalarType
tnbLib::DecoupledBlockCoeff<Type>::component(const direction dir) const
{
	if (scalarCoeffPtr_)
	{
		return *scalarCoeffPtr_;
	}
	else if (linearCoeffPtr_)
	{
		return linearCoeffPtr_->component(dir);
	}
	else
	{
		FatalErrorIn
		(
			"tmp<DecoupledBlockCoeff<Type>::scalarType>"
			"DecoupledBlockCoeff<Type>::component(const direction dir) const"
		) << " not allocated."
			<< abort(FatalError);
	}

	// Dummy return to keep compiler happy
	return *scalarCoeffPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::DecoupledBlockCoeff<Type>::operator=
(
	const DecoupledBlockCoeff<Type>& f
	)
{
	if (this == &f)
	{
		FatalErrorIn
		(
			"DecoupledBlockCoeff<Type>::operator=("
			"const DecoupledBlockCoeff<Type>&)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	if (f.scalarCoeffPtr_)
	{
		this->toScalar() = *(f.scalarCoeffPtr_);
	}
	else if (f.linearCoeffPtr_)
	{
		this->toLinear() = *(f.linearCoeffPtr_);
	}
	else
	{
		// Not allocated - do nothing
	}
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const DecoupledBlockCoeff<Type>& f)
{
	// Write active type
	os << blockCoeffBase::activeLevelNames_[f.activeType()] << nl;

	if (f.scalarCoeffPtr_)
	{
		os << *(f.scalarCoeffPtr_);
	}
	else if (f.linearCoeffPtr_)
	{
		os << *(f.linearCoeffPtr_);
	}

	return os;
}


// ************************************************************************* //