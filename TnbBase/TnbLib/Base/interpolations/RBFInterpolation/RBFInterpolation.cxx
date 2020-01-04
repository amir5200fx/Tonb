#include <RBFInterpolation.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

const tnbLib::scalarSquareMatrix& tnbLib::RBFInterpolation::B() const
{
	if (!BPtr_)
	{
		calcB();
	}

	return *BPtr_;
}


void tnbLib::RBFInterpolation::calcB() const
{
	// Determine inverse of boundary connectivity matrix
	label polySize(4);

	if (!polynomials_)
	{
		polySize = 0;
	}

	// Fill Nb x Nb matrix
	simpleMatrix<scalar> A(controlPoints_.size() + polySize);

	const label nControlPoints = controlPoints_.size();
	for (label i = 0; i < nControlPoints; i++)
	{
		scalarField weights = RBF_->weights(controlPoints_, controlPoints_[i]);

		for (label col = 0; col < nControlPoints; col++)
		{
			A[i][col] = weights[col];
		}
	}

	if (polynomials_)
	{
		for
			(
				label row = nControlPoints;
				row < nControlPoints + 1;
				row++
				)
		{
			for (label col = 0; col < nControlPoints; col++)
			{
				A[col][row] = 1.0;
				A[row][col] = 1.0;
			}
		}

		// Fill in X components of polynomial part of matrix
		for
			(
				label row = nControlPoints + 1;
				row < nControlPoints + 2;
				row++
				)
		{
			for (label col = 0; col < nControlPoints; col++)
			{
				A[col][row] = controlPoints_[col].x();
				A[row][col] = controlPoints_[col].x();
			}
		}

		// Fill in Y components of polynomial part of matrix
		for
			(
				label row = nControlPoints + 2;
				row < nControlPoints + 3;
				row++
				)
		{
			for (label col = 0; col < nControlPoints; col++)
			{
				A[col][row] = controlPoints_[col].y();
				A[row][col] = controlPoints_[col].y();
			}
		}
		// Fill in Z components of polynomial part of matrix
		for
			(
				label row = nControlPoints + 3;
				row < nControlPoints + 4;
				row++
				)
		{
			for (label col = 0; col < nControlPoints; col++)
			{
				A[col][row] = controlPoints_[col].z();
				A[row][col] = controlPoints_[col].z();
			}
		}

		// Fill 4x4 zero part of matrix
		for
			(
				label row = nControlPoints;
				row < nControlPoints + 4;
				row++
				)
		{
			for
				(
					label col = nControlPoints;
					col < nControlPoints + 4;
					col++
					)
			{
				A[row][col] = 0.0;
			}
		}
	}

	// HJ and FB (05 Jan 2009)
	// Collect ALL control points from ALL CPUs
	// Create an identical inverse for all CPUs

	Info << "Inverting RBF motion matrix" << endl;

	BPtr_ = new scalarSquareMatrix(A.LUinvert());
}


void tnbLib::RBFInterpolation::clearOut()
{
	deleteDemandDrivenData(BPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBFInterpolation::RBFInterpolation
(
	const dictionary& dict,
	const vectorField& controlPoints,
	const vectorField& dataPoints
)
	:
	controlPoints_(controlPoints),
	dataPoints_(dataPoints),
	RBF_(RBFFunction::New(word(dict.lookup("RBF")), dict)),
	BPtr_(NULL),
	focalPoint_(dict.lookup("focalPoint")),
	innerRadius_(readScalar(dict.lookup("innerRadius"))),
	outerRadius_(readScalar(dict.lookup("outerRadius"))),
	polynomials_(dict.lookup("polynomials"))
{}


tnbLib::RBFInterpolation::RBFInterpolation
(
	const RBFInterpolation& rbf
)
	:
	controlPoints_(rbf.controlPoints_),
	dataPoints_(rbf.dataPoints_),
	RBF_(rbf.RBF_->clone()),
	BPtr_(NULL),
	focalPoint_(rbf.focalPoint_),
	innerRadius_(rbf.innerRadius_),
	outerRadius_(rbf.outerRadius_),
	polynomials_(rbf.polynomials_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBFInterpolation::~RBFInterpolation()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::RBFInterpolation::movePoints()
{
	clearOut();
}


// ************************************************************************* //