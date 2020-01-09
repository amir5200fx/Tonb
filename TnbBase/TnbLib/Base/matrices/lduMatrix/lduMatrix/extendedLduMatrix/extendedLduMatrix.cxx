#include <extendedLduMatrix.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(extendedLduMatrix, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::extendedLduMatrix::clearOut()
{
	deleteDemandDrivenData(extendedLowerPtr_);
	deleteDemandDrivenData(extendedUpperPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedLduMatrix::extendedLduMatrix
(
	const lduMatrix& ldum,
	const extendedLduAddressing& extLduAddr
)
	:
	basicLduMatrix_(ldum),
	extLduAddr_(extLduAddr),
	extendedLowerPtr_(NULL),
	extendedUpperPtr_(NULL)
{
	if (debug)
	{
		InfoIn("extendedLduMatrix(lduMatrix&, label, polyMesh&)")
			<< "Constructing extendedLduMatrix."
			<< endl;
	}

	if (ldum.diagonal())
	{
		WarningIn("extendedLduMatrix(lduMatrix&, label, polyMesh&)")
			<< "Attempted to create extended lower/upper coeffs for matrix "
			<< "that is diagonal."
			<< nl << endl;
	}
	else if (ldum.symmetric())
	{
		// Get reference to faceMap in extended addressing
		const unallocLabelList& faceMap = extLduAddr_.faceMap();

		// Matrix is considered symmetric if the upper is allocated and lower
		// is not allocated. Allocating extended upper only.
		extendedUpperPtr_ = new scalarField
		(
			extLduAddr_.extendedUpperAddr().size(),
			0.0
		);
		scalarField& extUpper = *extendedUpperPtr_;

		// Get upper coeffs from underlying lduMatrix
		const scalarField& upper = ldum.upper();

		// Copy non-zero coeffs from basic lduMatrix into corresponding
		// positions
		forAll(upper, faceI)
		{
			extUpper[faceMap[faceI]] = upper[faceI];
		}
	}
	else
	{
		// Get reference to faceMap in extended addressing
		const unallocLabelList& faceMap = extLduAddr_.faceMap();

		// Get number of extended faces
		const label nExtFaces = extLduAddr_.extendedUpperAddr().size();

		// Allocate extended upper and lower
		extendedUpperPtr_ = new scalarField(nExtFaces, scalar(0));
		scalarField& extUpper = *extendedUpperPtr_;

		extendedLowerPtr_ = new scalarField(nExtFaces, scalar(0));
		scalarField& extLower = *extendedLowerPtr_;

		// Get upper and lower coeffs from underlying lduMatrix
		const scalarField& upper = ldum.upper();
		const scalarField& lower = ldum.lower();

		// Copy non-zero coeffs from basic lduMatrix into corresponding
		// positions
		forAll(upper, faceI)
		{
			extUpper[faceMap[faceI]] = upper[faceI];
			extLower[faceMap[faceI]] = lower[faceI];
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor* * * * * * * * * * * * * * * * //

tnbLib::extendedLduMatrix::~extendedLduMatrix()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalarField& tnbLib::extendedLduMatrix::extendedLower()
{
	if (!extendedLowerPtr_)
	{
		if (extendedUpperPtr_)
		{
			extendedLowerPtr_ = new scalarField(*extendedUpperPtr_);
		}
		else
		{
			extendedLowerPtr_ = new scalarField
			(
				extLduAddr_.extendedLowerAddr().size(),
				scalar(0)
			);
		}
	}

	return *extendedLowerPtr_;
}


tnbLib::scalarField& tnbLib::extendedLduMatrix::extendedUpper()
{
	if (!extendedUpperPtr_)
	{
		if (extendedLowerPtr_)
		{
			extendedUpperPtr_ = new scalarField(*extendedLowerPtr_);
		}
		else
		{
			extendedUpperPtr_ = new scalarField
			(
				extLduAddr_.extendedUpperAddr().size(),
				scalar(0)
			);
		}
	}

	return *extendedUpperPtr_;
}


const tnbLib::scalarField& tnbLib::extendedLduMatrix::extendedLower() const
{
	if (!extendedLowerPtr_ && !extendedUpperPtr_)
	{
		FatalErrorIn
		(
			"const scalarfield& extendedLduMatrix::extendedLower() const"
		) << "extendedLowerPtr_ or extendedUpperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (extendedLowerPtr_)
	{
		return *extendedLowerPtr_;
	}
	else
	{
		return *extendedUpperPtr_;
	}
}


const tnbLib::scalarField& tnbLib::extendedLduMatrix::extendedUpper() const
{
	if (!extendedLowerPtr_ && !extendedUpperPtr_)
	{
		FatalErrorIn
		(
			"const scalarfield& extendedLduMatrix::extendedUpper() const"
		) << "extendedLowerPtr_ or extendedUpperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (extendedUpperPtr_)
	{
		return *extendedUpperPtr_;
	}
	else
	{
		return *extendedLowerPtr_;
	}
}


// ************************************************************************* //