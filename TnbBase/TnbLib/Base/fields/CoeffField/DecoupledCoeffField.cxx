#include <DecoupledCoeffField.hxx>

#include <demandDrivenData.hxx>
#include <expandTensorField.hxx>

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

template<class Type>
const char* const
tnbLib::DecoupledCoeffField<Type>::typeName("DecoupledCoeffField");


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
template<class Type2>
inline void tnbLib::DecoupledCoeffField<Type>::checkSize
(
	const UList<Type2>& f
) const
{
	if (f.size() != this->size())
	{
		FatalErrorIn
		(
			"void DecoupledCoeffField<Type>::checkSize("
			"const Field<Type2>& f) const"
		) << "Incorrect field size: " << f.size()
			<< " local size: " << size()
			<< abort(FatalError);
	}
}


template<class Type>
typename tnbLib::DecoupledCoeffField<Type>::scalarTypeField&
tnbLib::DecoupledCoeffField<Type>::toScalar()
{
	if (!scalarCoeffPtr_)
	{
		// Debug check: demotion
		if (linearCoeffPtr_)
		{
			FatalErrorIn
			(
				"DecoupledCoeffField<Type>::scalarTypeField& "
				"DecoupledCoeffField<Type>::toScalar()"
			) << "Detected demotion to scalar.  Probably an error"
				<< abort(FatalError);
		}

		scalarCoeffPtr_ =
			new scalarTypeField(size(), pTraits<scalarType>::zero);
	}

	return *scalarCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledCoeffField<Type>::linearTypeField&
tnbLib::DecoupledCoeffField<Type>::toLinear()
{
	if (!linearCoeffPtr_)
	{
		linearCoeffPtr_ =
			new linearTypeField(size(), pTraits<linearType>::zero);

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
tnbLib::DecoupledCoeffField<Type>::DecoupledCoeffField(const label size)
	:
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL),
	size_(size)
{}


template<class Type>
tnbLib::DecoupledCoeffField<Type>::DecoupledCoeffField
(
	const DecoupledCoeffField<Type>& f
)
	:
	refCount(),
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL),
	size_(f.size())
{
	if (f.scalarCoeffPtr_)
	{
		scalarCoeffPtr_ = new scalarTypeField(*(f.scalarCoeffPtr_));
	}
	else if (f.linearCoeffPtr_)
	{
		linearCoeffPtr_ = new linearTypeField(*(f.linearCoeffPtr_));
	}
}


template<class Type>
tnbLib::DecoupledCoeffField<Type>::DecoupledCoeffField(Istream& is)
	:
	scalarCoeffPtr_(NULL),
	linearCoeffPtr_(NULL),
	size_(0)
{
	// Read keyword and pick up allocated field
	word key(is);

	if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::UNALLOCATED]
			)
	{
		size_ = readLabel(is);
	}
	else if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::SCALAR]
			)
	{
		scalarCoeffPtr_ = new scalarTypeField(is);
		size_ = scalarCoeffPtr_->size();
	}
	else if
		(
			key
			== blockCoeffBase::activeLevelNames_[blockCoeffBase::LINEAR]
			)
	{
		linearCoeffPtr_ = new linearTypeField(is);
		size_ = linearCoeffPtr_->size();
	}
	else
	{
		FatalIOErrorIn
		(
			"DecoupledCoeffField<Type>::DecoupledCoeffField(Istream& is)",
			is
		) << "invalid keyword while reading: " << key
			<< exit(FatalIOError);
	}
}


template<class Type>
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type> >
tnbLib::DecoupledCoeffField<Type>::clone() const
{
	return tmp<DecoupledCoeffField<Type> >
		(
			new DecoupledCoeffField<Type>(*this)
			);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::DecoupledCoeffField<Type>::~DecoupledCoeffField()
{
	this->clear();
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::clear()
{
	deleteDemandDrivenData(scalarCoeffPtr_);
	deleteDemandDrivenData(linearCoeffPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::label tnbLib::DecoupledCoeffField<Type>::size() const
{
	return size_;
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::negate()
{
	if (scalarCoeffPtr_)
	{
		scalarCoeffPtr_->negate();
	}
	else if (linearCoeffPtr_)
	{
		linearCoeffPtr_->negate();
	}
}


template<class Type>
tnbLib::tmp<tnbLib::DecoupledCoeffField<Type> >
tnbLib::DecoupledCoeffField<Type>::transpose() const
{
	tmp<DecoupledCoeffField<Type> > tt
	(
		new DecoupledCoeffField<Type>(this->size())
	);
	DecoupledCoeffField<Type>& t = tt();

	if (scalarCoeffPtr_)
	{
		t.toScalar() = *scalarCoeffPtr_;
	}
	else if (linearCoeffPtr_)
	{
		t.toLinear() = *linearCoeffPtr_;
	}
	else
	{
		// Not allocated - do nothing
	}


	return tt;
}


template<class Type>
tnbLib::blockCoeffBase::activeLevel
tnbLib::DecoupledCoeffField<Type>::activeType() const
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
void tnbLib::DecoupledCoeffField<Type>::checkActive() const
{
	label nActive = 0;

	if (scalarCoeffPtr_) nActive++;
	if (linearCoeffPtr_) nActive++;

	if (nActive > 1)
	{
		FatalErrorIn
		(
			"void tnbLib::DecoupledCoeffField<Type>::checkActive() const"
		) << "Activation/deactivation error.  nActive = " << nActive
			<< abort(FatalError);
	}
}


template<class Type>
const typename tnbLib::DecoupledCoeffField<Type>::scalarTypeField&
tnbLib::DecoupledCoeffField<Type>::asScalar() const
{
	if (!scalarCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::scalarTypeField& "
			"DecoupledCoeffField<Type>::asScalar()"
		) << "Requested scalar but active type is: "
			<< blockCoeffBase::activeLevelNames_[this->activeType()]
			<< ".  This is not allowed."
			<< abort(FatalError);
	}

	return *scalarCoeffPtr_;
}


template<class Type>
const typename tnbLib::DecoupledCoeffField<Type>::linearTypeField&
tnbLib::DecoupledCoeffField<Type>::asLinear() const
{
	if (!linearCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::linearTypeField& "
			"DecoupledCoeffField<Type>::asLinear()"
		) << "Requested linear but active type is: "
			<< blockCoeffBase::activeLevelNames_[this->activeType()]
			<< ".  This is not allowed."
			<< abort(FatalError);
	}

	return *linearCoeffPtr_;
}


template<class Type>
typename tnbLib::DecoupledCoeffField<Type>::scalarTypeField&
tnbLib::DecoupledCoeffField<Type>::asScalar()
{
	if (linearCoeffPtr_)
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::scalarTypeField& "
			"DecoupledCoeffField<Type>::asScalar()"
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
typename tnbLib::DecoupledCoeffField<Type>::linearTypeField&
tnbLib::DecoupledCoeffField<Type>::asLinear()
{
	if (!linearCoeffPtr_)
	{
		return this->toLinear();
	}

	return *linearCoeffPtr_;
}


template<class Type>
tnbLib::tmp<typename tnbLib::DecoupledCoeffField<Type>::scalarTypeField>
tnbLib::DecoupledCoeffField<Type>::component(const direction dir) const
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
			"tmp<DecoupledCoeffField<Type>::scalarTypeField>"
			"DecoupledCoeffField<Type>::component(const direction dir) const"
		) << "Field not allocated."
			<< abort(FatalError);
	}

	// Dummy return to keep compiler happy
	return *scalarCoeffPtr_;
}


template<class Type>
tnbLib::BlockCoeff<Type>
tnbLib::DecoupledCoeffField<Type>::getCoeff(const label index) const
{
	BlockCoeff<Type> result;

	if (scalarCoeffPtr_)
	{
		result.asScalar() = (*scalarCoeffPtr_)[index];
	}
	else if (linearCoeffPtr_)
	{
		result.asLinear() = (*linearCoeffPtr_)[index];
	}

	return result;
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::setCoeff
(
	const label index,
	const BlockCoeff<Type>& coeff
)
{
	BlockCoeff<Type> result;

	if (coeff.activeType() == blockCoeffBase::SCALAR)
	{
		(*scalarCoeffPtr_)[index] = result.asScalar();
	}
	else if (coeff.activeType() == blockCoeffBase::LINEAR)
	{
		(*linearCoeffPtr_)[index] = result.asLinear();
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::getSubset
(
	DecoupledCoeffField<Type>& f,
	const label start,
	const label size
) const
{
	// Check sizes
	if (f.size() != size)
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::getSubset\n"
			"(\n"
			"    DecoupledCoeffField<Type>& f,\n"
			"    const label start,\n"
			"    const label size\n"
			") const"
		) << "Incompatible sizes: " << f.size() << " and " << size
			<< abort(FatalError);
	}

	if (scalarCoeffPtr_)
	{
		scalarTypeField& ff = f.asScalar();

		const scalarTypeField& localF = (*scalarCoeffPtr_);

		forAll(ff, ffI)
		{
			ff[ffI] = localF[start + ffI];
		}
	}
	else if (linearCoeffPtr_)
	{
		linearTypeField& ff = f.asLinear();

		const linearTypeField& localF = (*linearCoeffPtr_);

		forAll(ff, ffI)
		{
			ff[ffI] = localF[start + ffI];
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::getSubset
(
	DecoupledCoeffField<Type>& f,
	const labelList& addr
) const
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::getSubset\n"
			"(\n"
			"    DecoupledCoeffField<Type>& f,\n"
			"    const labelList addr\n"
			") const"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	if (scalarCoeffPtr_)
	{
		scalarTypeField& ff = f.asScalar();

		const scalarTypeField& localF = (*scalarCoeffPtr_);

		forAll(ff, ffI)
		{
			ff[ffI] = localF[addr[ffI]];
		}
	}
	else if (linearCoeffPtr_)
	{
		linearTypeField& ff = f.asLinear();

		const linearTypeField& localF = (*linearCoeffPtr_);

		forAll(ff, ffI)
		{
			ff[ffI] = localF[addr[ffI]];
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::setSubset
(
	const DecoupledCoeffField<Type>& f,
	const label start,
	const label size
)
{
	// Check sizes
	if (f.size() != size)
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::setSubset\n"
			"(\n"
			"     const DecoupledCoeffField<Type>& f,\n"
			"    const label start,\n"
			"    const label size\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << size
			<< abort(FatalError);
	}

	if (f.activeType() == blockCoeffBase::SCALAR)
	{
		const scalarTypeField& ff = f.asScalar();

		scalarTypeField& localF = this->asScalar();

		forAll(ff, ffI)
		{
			localF[start + ffI] = ff[ffI];
		}
	}
	else if (f.activeType() == blockCoeffBase::LINEAR)
	{
		const linearTypeField& ff = f.asLinear();

		linearTypeField& localF = this->asLinear();

		forAll(ff, ffI)
		{
			localF[start + ffI] = ff[ffI];
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::setSubset
(
	const DecoupledCoeffField<Type>& f,
	const labelList& addr
)
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::setSubset\n"
			"(\n"
			"    const DecoupledCoeffField<Type>& f,\n"
			"    const labelList addr\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	if (f.activeType() == blockCoeffBase::SCALAR)
	{
		const scalarTypeField& ff = f.asScalar();

		scalarTypeField& localF = this->asScalar();

		forAll(ff, ffI)
		{
			localF[addr[ffI]] = ff[ffI];
		}
	}
	else if (f.activeType() == blockCoeffBase::LINEAR)
	{
		const linearTypeField& ff = f.asLinear();

		linearTypeField& localF = this->asLinear();

		forAll(ff, ffI)
		{
			localF[addr[ffI]] = ff[ffI];
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::zeroOutSubset
(
	const label start,
	const label size
)
{
	if (scalarCoeffPtr_)
	{
		scalarTypeField& localF = this->asScalar();

		for (label ffI = 0; ffI < size; ffI++)
		{
			localF[start + ffI] = pTraits<scalarType>::zero;
		}
	}
	else if (linearCoeffPtr_)
	{
		linearTypeField& localF = this->asLinear();

		for (label ffI = 0; ffI < size; ffI++)
		{
			localF[start + ffI] = pTraits<linearType>::zero;
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::zeroOutSubset
(
	const labelList& addr
)
{
	if (scalarCoeffPtr_)
	{
		scalarTypeField& localF = this->asScalar();

		forAll(addr, ffI)
		{
			localF[addr[ffI]] = pTraits<scalarType>::zero;
		}
	}
	else if (linearCoeffPtr_)
	{
		linearTypeField& localF = this->asLinear();

		forAll(addr, ffI)
		{
			localF[addr[ffI]] = pTraits<linearType>::zero;
		}
	}
}


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::addSubset
(
	const DecoupledCoeffField<Type>& f,
	const labelList& addr
)
{
	// Check sizes
	if (f.size() != addr.size())
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::addSubset\n"
			"(\n"
			"    const DecoupledCoeffField<Type>& f,\n"
			"    const labelList addr\n"
			")"
		) << "Incompatible sizes: " << f.size() << " and " << addr.size()
			<< abort(FatalError);
	}

	if
		(
			f.activeType() == blockCoeffBase::LINEAR
			|| this->activeType() == blockCoeffBase::LINEAR
			)
	{
		const linearTypeField& ff = f.asLinear();

		linearTypeField& localF = this->asLinear();

		forAll(ff, ffI)
		{
			localF[addr[ffI]] += ff[ffI];
		}
	}
	else if
		(
			f.activeType() == blockCoeffBase::SCALAR
			&& this->activeType() == blockCoeffBase::SCALAR
			)
	{
		const scalarTypeField& ff = f.asScalar();

		scalarTypeField& localF = this->asScalar();

		forAll(ff, ffI)
		{
			localF[addr[ffI]] += ff[ffI];
		}
	}
	else
	{
		FatalErrorIn
		(
			"template<class Type>\n"
			"void tnbLib::DecoupledCoeffField<Type>::addSubset\n"
			"(\n"
			"    const DecoupledCoeffField<Type>& f,\n"
			"    const labelList addr\n"
			")"
		) << "Incompatible combination of types"
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::DecoupledCoeffField<Type>::operator=
(
	const DecoupledCoeffField<Type>& f
	)
{
	if (this == &f)
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::operator=("
			"const DecoupledCoeffField<Type>&)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	// Check field sizes
	if (f.size() != this->size())
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::operator=("
			"const DecoupledCoeffField<Type>&)"
		) << "Incorrect field size: " << f.size()
			<< " local size: " << size()
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


template<class Type>
void tnbLib::DecoupledCoeffField<Type>::operator=
(
	const tmp<DecoupledCoeffField>& tf
	)
{
	if (this == &(tf()))
	{
		FatalErrorIn
		(
			"DecoupledCoeffField<Type>::operator=("
			"const tmp<DecoupledCoeffField>&)"
		) << "attempted assignment to self"
			<< abort(FatalError);
	}

	operator=(tf());
	tf.clear();
}


#define COMPUTED_BASE_ASSIGNMENT(op)                                          \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op                             \
(                                                                             \
    const DecoupledCoeffField<Type>& f                                        \
)                                                                             \
{                                                                             \
    if (f.size() != this->size())                                             \
    {                                                                         \
        FatalErrorIn                                                          \
        (                                                                     \
            "void DecoupledCoeffField<tensor>::operator "                     \
            "op(const DecoupledCoeffField<tensor>& f)"                        \
        )   << "Incorrect field size: " << f.size()                           \
            << " local size: " << size()                                      \
            << abort(FatalError);                                             \
    }                                                                         \
                                                                              \
                                                                              \
    if (f.scalarCoeffPtr_)                                                    \
    {                                                                         \
        this->toScalar() op *(f.scalarCoeffPtr_);                             \
    }                                                                         \
    else if (f.linearCoeffPtr_)                                               \
    {                                                                         \
        this->toLinear() op *(f.linearCoeffPtr_);                             \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op                             \
(                                                                             \
    const tmp<DecoupledCoeffField<Type> >& tf                                 \
)                                                                             \
{                                                                             \
    operator op(tf());                                                        \
    tf.clear();                                                               \
}


#define COMPUTED_ARG_ASSIGNMENT(op)                                           \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op(const scalarTypeField& f)   \
{                                                                             \
    checkSize(f);                                                             \
                                                                              \
    const blockCoeffBase::activeLevel al = this->activeType();                \
                                                                              \
    if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR)    \
    {                                                                         \
        this->toScalar() op f;                                                \
    }                                                                         \
    else if (al == blockCoeffBase::LINEAR)                                    \
    {                                                                         \
        this->toLinear() op f*pTraits<linearType>::one;                       \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op                             \
(                                                                             \
    const tmp<scalarTypeField>& tf                                            \
)                                                                             \
{                                                                             \
    operator op(tf());                                                        \
    tf.clear();                                                               \
}                                                                             \
                                                                              \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op(const linearTypeField& f)   \
{                                                                             \
    checkSize(f);                                                             \
                                                                              \
    const blockCoeffBase::activeLevel al = this->activeType();                \
                                                                              \
    if                                                                        \
    (                                                                         \
        al == blockCoeffBase::UNALLOCATED                                     \
     || al == blockCoeffBase::SCALAR                                          \
     || al == blockCoeffBase::LINEAR                                          \
    )                                                                         \
    {                                                                         \
        this->toLinear() op f;                                                \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op                             \
(                                                                             \
    const tmp<linearTypeField>& tf                                            \
)                                                                             \
{                                                                             \
    operator op(tf());                                                        \
    tf.clear();                                                               \
}                                                                             \


#define COMPUTED_BASE_OPERATOR(TYPE, op)                                      \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op(const TYPE& t)              \
{                                                                             \
    if (scalarCoeffPtr_)                                                      \
    {                                                                         \
        *(scalarCoeffPtr_) op t;                                              \
    }                                                                         \
    else if (linearCoeffPtr_)                                                 \
    {                                                                         \
        *(linearCoeffPtr_) op t;                                              \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op(const UList<TYPE>& tf)      \
{                                                                             \
    checkSize(tf);                                                            \
                                                                              \
    if (scalarCoeffPtr_)                                                      \
    {                                                                         \
        *(scalarCoeffPtr_) op tf;                                             \
    }                                                                         \
    else if (linearCoeffPtr_)                                                 \
    {                                                                         \
        *(linearCoeffPtr_) op tf;                                             \
    }                                                                         \
    else                                                                      \
    {                                                                         \
    }                                                                         \
}                                                                             \
                                                                              \
template<class Type>                                                          \
void tnbLib::DecoupledCoeffField<Type>::operator op                             \
(                                                                             \
    const tmp<Field<TYPE> >& tf                                               \
)                                                                             \
{                                                                             \
    operator op(tf());                                                        \
    tf.clear();                                                               \
}


#define COMPUTED_ASSIGNMENT(op)                                               \
COMPUTED_BASE_ASSIGNMENT(op)                                                  \
COMPUTED_ARG_ASSIGNMENT(op)

// Remaining operator=
template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator =(const scalarTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR) { this->toScalar() = f; }
	else if (al == blockCoeffBase::LINEAR) { this->toLinear() = f * pTraits<linearType>::one; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator =(const tmp<scalarTypeField>& tf)
{
	operator =(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator =(const linearTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR || al == blockCoeffBase::LINEAR)
	{
		this->toLinear() = f;
	}
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator =(const tmp<linearTypeField>& tf)
{
	operator =(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const DecoupledCoeffField<Type>& f)
{
	if (f.size() != this->size())
	{
		FatalErrorIn ( "void DecoupledCoeffField<tensor>::operator " "op(const DecoupledCoeffField<tensor>& f)" ) <<
			"Incorrect field size: " << f.size() << " local size: " << size() << abort(FatalError);
	}
	if (f.scalarCoeffPtr_) { this->toScalar() += *(f.scalarCoeffPtr_); }
	else if (f.linearCoeffPtr_) { this->toLinear() += *(f.linearCoeffPtr_); }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const tmp<DecoupledCoeffField<Type>>& tf)
{
	operator +=(tf());
	tf.clear();
} 

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const scalarTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR) { this->toScalar() += f; }
	else if (al == blockCoeffBase::LINEAR) { this->toLinear() += f * pTraits<linearType>::one; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const tmp<scalarTypeField>& tf)
{
	operator +=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const linearTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR || al == blockCoeffBase::LINEAR)
	{
		this->toLinear() += f;
	}
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator +=(const tmp<linearTypeField>& tf)
{
	operator +=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const DecoupledCoeffField<Type>& f)
{
	if (f.size() != this->size())
	{
		FatalErrorIn ( "void DecoupledCoeffField<tensor>::operator " "op(const DecoupledCoeffField<tensor>& f)" ) <<
			"Incorrect field size: " << f.size() << " local size: " << size() << abort(FatalError);
	}
	if (f.scalarCoeffPtr_) { this->toScalar() -= *(f.scalarCoeffPtr_); }
	else if (f.linearCoeffPtr_) { this->toLinear() -= *(f.linearCoeffPtr_); }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const tmp<DecoupledCoeffField<Type>>& tf)
{
	operator -=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const scalarTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR) { this->toScalar() -= f; }
	else if (al == blockCoeffBase::LINEAR) { this->toLinear() -= f * pTraits<linearType>::one; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const tmp<scalarTypeField>& tf)
{
	operator -=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const linearTypeField& f)
{
	checkSize(f);
	const blockCoeffBase::activeLevel al = this->activeType();
	if (al == blockCoeffBase::UNALLOCATED || al == blockCoeffBase::SCALAR || al == blockCoeffBase::LINEAR)
	{
		this->toLinear() -= f;
	}
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator -=(const tmp<linearTypeField>& tf)
{
	operator -=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator *=(const scalar& t)
{
	if (scalarCoeffPtr_) { *(scalarCoeffPtr_) *= t; }
	else if (linearCoeffPtr_) { *(linearCoeffPtr_) *= t; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator *=(const UList<scalar>& tf)
{
	checkSize(tf);
	if (scalarCoeffPtr_) { *(scalarCoeffPtr_) *= tf; }
	else if (linearCoeffPtr_) { *(linearCoeffPtr_) *= tf; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator *=(const tmp<Field<scalar>>& tf)
{
	operator *=(tf());
	tf.clear();
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator /=(const scalar& t)
{
	if (scalarCoeffPtr_) { *(scalarCoeffPtr_) /= t; }
	else if (linearCoeffPtr_) { *(linearCoeffPtr_) /= t; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator /=(const UList<scalar>& tf)
{
	checkSize(tf);
	if (scalarCoeffPtr_) { *(scalarCoeffPtr_) /= tf; }
	else if (linearCoeffPtr_) { *(linearCoeffPtr_) /= tf; }
	else
	{
	}
}

template <class Type>
void tnbLib::DecoupledCoeffField<Type>::operator /=(const tmp<Field<scalar>>& tf)
{
	operator /=(tf());
	tf.clear();
}

#undef COMPUTED_BASE_OPERATOR
#undef COMPUTED_BASE_ASSIGNMENT
#undef COMPUTED_ARG_ASSIGNMENT
#undef COMPUTED_ASSIGNMENT


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const DecoupledCoeffField<Type>& f
	)
{
	// Write active type
	os << blockCoeffBase::activeLevelNames_[f.activeType()] << nl;

	if (f.activeType() == blockCoeffBase::SCALAR)
	{
		os << f.asScalar();
	}
	else if (f.activeType() == blockCoeffBase::LINEAR)
	{
		os << f.asLinear();
	}
	else
	{
		// Not allocated: write size
		os << f.size();
	}

	return os;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<DecoupledCoeffField<Type> >& tf
	)
{
	os << tf();
	tf.clear();
	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#   include <DecoupledCoeffFieldFunctions.cxx>


// ************************************************************************* //