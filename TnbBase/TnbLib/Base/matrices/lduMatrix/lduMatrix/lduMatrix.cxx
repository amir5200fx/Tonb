#include <lduMatrix.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(lduMatrix, 1);
}

const tnbLib::scalar tnbLib::lduMatrix::great_ = 1.0e+20;
const tnbLib::scalar tnbLib::lduMatrix::small_ = 1.0e-20;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::lduMatrix::lduMatrix(const lduMesh& mesh)
	:
	lduMesh_(mesh),
	lowerPtr_(NULL),
	diagPtr_(NULL),
	upperPtr_(NULL)
{}


tnbLib::lduMatrix::lduMatrix(const lduMatrix& A)
	:
	lduMesh_(A.lduMesh_),
	lowerPtr_(NULL),
	diagPtr_(NULL),
	upperPtr_(NULL)
{
	if (A.lowerPtr_)
	{
		lowerPtr_ = new scalarField(*(A.lowerPtr_));
	}

	if (A.diagPtr_)
	{
		diagPtr_ = new scalarField(*(A.diagPtr_));
	}

	if (A.upperPtr_)
	{
		upperPtr_ = new scalarField(*(A.upperPtr_));
	}
}


tnbLib::lduMatrix::lduMatrix(lduMatrix& A, bool reUse)
	:
	lduMesh_(A.lduMesh_),
	lowerPtr_(NULL),
	diagPtr_(NULL),
	upperPtr_(NULL)
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
		if (A.lowerPtr_)
		{
			lowerPtr_ = new scalarField(*(A.lowerPtr_));
		}

		if (A.diagPtr_)
		{
			diagPtr_ = new scalarField(*(A.diagPtr_));
		}

		if (A.upperPtr_)
		{
			upperPtr_ = new scalarField(*(A.upperPtr_));
		}
	}
}


tnbLib::lduMatrix::lduMatrix
(
	const lduMesh& mesh,
	Istream& is
)
	:
	lduMesh_(mesh),
	lowerPtr_(new scalarField(is)),
	diagPtr_(new scalarField(is)),
	upperPtr_(new scalarField(is))
{}


tnbLib::lduMatrix::~lduMatrix()
{
	if (lowerPtr_)
	{
		delete lowerPtr_;
	}

	if (diagPtr_)
	{
		delete diagPtr_;
	}

	if (upperPtr_)
	{
		delete upperPtr_;
	}
}


tnbLib::scalarField& tnbLib::lduMatrix::lower()
{
	if (!lowerPtr_)
	{
		if (upperPtr_)
		{
			lowerPtr_ = new scalarField(*upperPtr_);
		}
		else
		{
			lowerPtr_ = new scalarField(lduAddr().lowerAddr().size(), 0.0);
		}
	}

	return *lowerPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::diag()
{
	if (!diagPtr_)
	{
		diagPtr_ = new scalarField(lduAddr().size(), 0.0);
	}

	return *diagPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::upper()
{
	if (!upperPtr_)
	{
		if (lowerPtr_)
		{
			upperPtr_ = new scalarField(*lowerPtr_);
		}
		else
		{
			upperPtr_ = new scalarField(lduAddr().lowerAddr().size(), 0.0);
		}
	}

	return *upperPtr_;
}


const tnbLib::scalarField& tnbLib::lduMatrix::lower() const
{
	if (!lowerPtr_ && !upperPtr_)
	{
		FatalErrorIn("lduMatrix::lower() const")
			<< "lowerPtr_ or upperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (lowerPtr_)
	{
		return *lowerPtr_;
	}
	else
	{
		return *upperPtr_;
	}
}


const tnbLib::scalarField& tnbLib::lduMatrix::diag() const
{
	if (!diagPtr_)
	{
		FatalErrorIn("const scalarField& lduMatrix::diag() const")
			<< "diagPtr_ unallocated"
			<< abort(FatalError);
	}

	return *diagPtr_;
}


const tnbLib::scalarField& tnbLib::lduMatrix::upper() const
{
	if (!lowerPtr_ && !upperPtr_)
	{
		FatalErrorIn("lduMatrix::upper() const")
			<< "lowerPtr_ or upperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (upperPtr_)
	{
		return *upperPtr_;
	}
	else
	{
		return *lowerPtr_;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const lduMatrix& ldum)
{
	if (ldum.lowerPtr_)
	{
		os << "Lower triangle = "
			<< *ldum.lowerPtr_
			<< endl << endl;
	}

	if (ldum.diagPtr_)
	{
		os << "diagonal = "
			<< *ldum.diagPtr_
			<< endl << endl;
	}

	if (ldum.upperPtr_)
	{
		os << "Upper triangle = "
			<< *ldum.upperPtr_
			<< endl << endl;
	}

	os.check("Ostream& operator<<(Ostream&, const lduMatrix&");

	return os;
}


// ************************************************************************* //