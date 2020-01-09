#include <BlockIterativeSolver.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from matrix and solver data stream
template<class Type>
tnbLib::BlockIterativeSolver<Type>::BlockIterativeSolver
(
	const word& fieldName,
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
	:
	BlockLduSolver<Type>(fieldName, matrix, dict),
	tolerance_(readScalar(this->dict().lookup("tolerance"))),
	relTolerance_(readScalar(this->dict().lookup("relTol"))),
	minIter_(readLabel(this->dict().lookup("minIter"))),
	maxIter_(readLabel(this->dict().lookup("maxIter")))
{}


// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<class Type>
tnbLib::scalar tnbLib::BlockIterativeSolver<Type>::normFactor
(
	Field<Type>& x,
	const Field<Type>& b
) const
{
	const BlockLduMatrix<Type>& matrix = this->matrix_;

	// Calculate the normalisation factor
	const label nRows = x.size();

	Field<Type> pA(nRows);
	Field<Type> wA(nRows);

	// Calculate reference value of x
	Type xRef = gAverage(x);

	// Calculate A.x
	matrix.Amul(wA, x);

	// Calculate A.xRef, temporarily using pA for storage
	matrix.Amul
	(
		pA,
		Field<Type>(nRows, xRef)
	);

	scalar normFactor = gSum(mag(wA - pA) + mag(b - pA)) + this->small_;

	if (BlockLduMatrix<Type>::debug >= 2)
	{
		Info << "Iterative solver normalisation factor = "
			<< normFactor << endl;
	}

	return normFactor;
}


template<class Type>
bool tnbLib::BlockIterativeSolver<Type>::stop
(
	BlockSolverPerformance<Type>& solverPerf
) const
{
	if (solverPerf.nIterations() < minIter_)
	{
		return false;
	}

	if
		(
			solverPerf.nIterations() >= maxIter_
			|| solverPerf.checkConvergence(tolerance_, relTolerance_)
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //