#include <BlockLduMatrix.hxx>

#include <demandDrivenData.hxx>
#include <error.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
const tnbLib::debug::optimisationSwitch
tnbLib::BlockLduMatrix<Type>::fixFillIn
(
	"matrixConstraintFillIn",
	4
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockLduMatrix<Type>::BlockLduMatrix(const lduMesh& ldu)
	:
	lduMesh_(ldu),
	diagPtr_(NULL),
	upperPtr_(NULL),
	lowerPtr_(NULL),
	interfaces_(ldu.interfaces().size()),
	coupleUpper_(ldu.lduAddr().nPatches()),
	coupleLower_(ldu.lduAddr().nPatches()),
	fixedEqns_(ldu.lduAddr().size() / fixFillIn())
{
	const lduAddressing& addr = ldu.lduAddr();

	forAll(coupleUpper_, i)
	{
		coupleUpper_.set(i, new CoeffField<Type>(addr.patchAddr(i).size()));
		coupleLower_.set(i, new CoeffField<Type>(addr.patchAddr(i).size()));
	}

}


template<class Type>
tnbLib::BlockLduMatrix<Type>::BlockLduMatrix(const BlockLduMatrix<Type>& A)
	:
	refCount(),
	lduMesh_(A.lduMesh_),
	diagPtr_(NULL),
	upperPtr_(NULL),
	lowerPtr_(NULL),
	interfaces_(A.interfaces_),
	coupleUpper_(A.coupleUpper_),
	coupleLower_(A.coupleLower_),
	fixedEqns_(A.fixedEqns_)
{
	if (A.diagPtr_)
	{
		diagPtr_ = new TypeCoeffField(*(A.diagPtr_));
	}

	if (A.upperPtr_)
	{
		upperPtr_ = new TypeCoeffField(*(A.upperPtr_));
	}

	if (A.lowerPtr_)
	{
		lowerPtr_ = new TypeCoeffField(*(A.lowerPtr_));
	}
}


//HJ, problematic: memory management.
// Reconsider.  HJ, 7/Nov/2010
template<class Type>
tnbLib::BlockLduMatrix<Type>::BlockLduMatrix(BlockLduMatrix<Type>& A, bool reUse)
	:
	refCount(),
	lduMesh_(A.lduMesh_),
	diagPtr_(NULL),
	upperPtr_(NULL),
	lowerPtr_(NULL),
	interfaces_(A.interfaces_, reUse),
	coupleUpper_(A.coupleUpper_, reUse),
	coupleLower_(A.coupleLower_, reUse),
	fixedEqns_(A.fixedEqns_)
{
	if (reUse)
	{
		if (A.lowerPtr_)
		{
			lowerPtr_ = A.lowerPtr_;
			A.lowerPtr_ = NULL;
		}

		if (A.diagPtr_)
		{
			diagPtr_ = A.diagPtr_;
			A.diagPtr_ = NULL;
		}

		if (A.upperPtr_)
		{
			upperPtr_ = A.upperPtr_;
			A.upperPtr_ = NULL;
		}
	}
	else
	{
		if (A.diagPtr_)
		{
			diagPtr_ = new TypeCoeffField(*(A.diagPtr_));
		}

		if (A.upperPtr_)
		{
			upperPtr_ = new TypeCoeffField(*(A.upperPtr_));
		}

		if (A.lowerPtr_)
		{
			lowerPtr_ = new TypeCoeffField(*(A.lowerPtr_));
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockLduMatrix<Type>::~BlockLduMatrix()
{
	deleteDemandDrivenData(diagPtr_);
	deleteDemandDrivenData(upperPtr_);
	deleteDemandDrivenData(lowerPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


template<class Type>
typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::diag()
{
	if (!diagPtr_)
	{
		diagPtr_ = new TypeCoeffField(lduAddr().size());
	}

	return *diagPtr_;
}


template<class Type>
const typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::diag() const
{
	if (!diagPtr_)
	{
		FatalErrorIn
		(
			"const TypeCoeffField& BlockLduMatrix<Type>::diag() const"
		) << "diagPtr_ unallocated"
			<< abort(FatalError);
	}

	return *diagPtr_;
}


template<class Type>
typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::upper()
{
	if (!upperPtr_)
	{
		upperPtr_ = new TypeCoeffField(lduAddr().lowerAddr().size());
	}

	return *upperPtr_;
}


template<class Type>
const typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::upper() const
{
	if (!upperPtr_)
	{
		FatalErrorIn
		(
			"const TypeCoeffField& BlockLduMatrix<Type>::upper() const"
		) << "upperPtr_ unallocated"
			<< abort(FatalError);
	}

	return *upperPtr_;
}


template<class Type>
typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::lower()
{
	if (!lowerPtr_)
	{
		if (upperPtr_)
		{
			//             Info << "Manufacturing lower from upper transpose" << endl;
			lowerPtr_ = new TypeCoeffField(upperPtr_->transpose());
		}
		else
		{
			lowerPtr_ = new TypeCoeffField(lduAddr().lowerAddr().size());
		}
	}

	return *lowerPtr_;
}


template<class Type>
const typename tnbLib::BlockLduMatrix<Type>::TypeCoeffField&
tnbLib::BlockLduMatrix<Type>::lower() const
{
	if (!lowerPtr_)
	{
		FatalErrorIn
		(
			"const TypeCoeffField&  BlockLduMatrix<Type>::lower() const"
		) << "lowerPtr_ unallocated"
			<< abort(FatalError);
	}

	return *lowerPtr_;
}


template<class Type>
void tnbLib::BlockLduMatrix<Type>::clearInterfaces()
{
	forAll(interfaces_, i)
	{
		if (interfaces_.set(i))
		{
			delete interfaces_(i);
		}
	}
}



template<class Type>
bool tnbLib::BlockLduMatrix<Type>::empty() const
{
	return (!diagPtr_ && !lowerPtr_ && !upperPtr_);
}


template<class Type>
bool tnbLib::BlockLduMatrix<Type>::diagonal() const
{
	return (diagPtr_ && !lowerPtr_ && !upperPtr_);
}


template<class Type>
bool tnbLib::BlockLduMatrix<Type>::symmetric() const
{
	if (lowerPtr_ && !upperPtr_)
	{
		FatalErrorIn
		(
			"bool BlockLduMatrix<Type>::symmetric() const"
		) << "Matrix assembly error: symmetric matrix but only lower "
			<< "triangle is allocated.  This is not allowed."
			<< abort(FatalError);
	}

	// Note:
	// It is possible that the block matrix is symmetric in sparseness
	// pattern, but asymmetric because the diagonal or upper coefficients are
	// square and asymmetric within the coefficients.
	// In such cases, the symmetric check in this function will falsely claim
	// the matrix is symmetries whereas in its flattened nature it is not
	// For the moment, symmetric check is used to see if the lower() is
	// allocated or not.
	// Please reconsider, especially related to matrix structure in
	// complex cases and in choice of linear equation solver for matrices
	// with asymmetric square coefficients
	// HJ and VV, 16/Mar/2016

	return (diagPtr_ && (!lowerPtr_ && upperPtr_));
}


template<class Type>
bool tnbLib::BlockLduMatrix<Type>::asymmetric() const
{
	return (diagPtr_ && lowerPtr_ && upperPtr_);
}


template<class Type>
bool tnbLib::BlockLduMatrix<Type>::componentCoupled() const
{
	// Return true if the matrix coefficient couple the components
	if (thereIsDiag())
	{
		if (diag().activeType() == blockCoeffBase::SQUARE)
		{
			return true;
		}
	}

	if (thereIsUpper())
	{
		if (upper().activeType() == blockCoeffBase::SQUARE)
		{
			return true;
		}
	}

	if (thereIsLower())
	{
		if (lower().activeType() == blockCoeffBase::SQUARE)
		{
			return true;
		}
	}

	return false;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Type>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const BlockLduMatrix<Type>& ldum)
{
	if (ldum.diagPtr_)
	{
		os.writeKeyword("diagonal")
			<< *ldum.diagPtr_ << token::END_STATEMENT << nl;
	}
	else
	{
		// Dummy write for consistency
		os.writeKeyword("diagonal")
			<< typename BlockLduMatrix<Type>::TypeCoeffField
			(
				ldum.lduAddr().size()
			)
			<< token::END_STATEMENT << nl;
	}

	if (ldum.upperPtr_)
	{
		os.writeKeyword("upper")
			<< *ldum.upperPtr_
			<< token::END_STATEMENT << nl;
	}
	else
	{
		// Dummy write for consistency
		os.writeKeyword("upper")
			<< typename BlockLduMatrix<Type>::TypeCoeffField
			(
				ldum.lduAddr().lowerAddr().size()
			)
			<< token::END_STATEMENT << nl;
	}

	if (ldum.lowerPtr_)
	{
		os.writeKeyword("lower")
			<< *ldum.lowerPtr_ << token::END_STATEMENT << nl;
	}
	else
	{
		// Dummy write for consistency
		os.writeKeyword("lower")
			<< typename BlockLduMatrix<Type>::TypeCoeffField
			(
				ldum.lduAddr().lowerAddr().size()
			)
			<< token::END_STATEMENT << nl;
	}

	os.writeKeyword("coupleUpper")
		<< ldum.coupleUpper_
		<< token::END_STATEMENT << endl;

	os.writeKeyword("coupleLower")
		<< ldum.coupleLower_
		<< token::END_STATEMENT << endl;

	os.check("Ostream& operator<<(Ostream&, const BlockLduMatrix<Type>&");

	return os;
}


// ************************************************************************* //