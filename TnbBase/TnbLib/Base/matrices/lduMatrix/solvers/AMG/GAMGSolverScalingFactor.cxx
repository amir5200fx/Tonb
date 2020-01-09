#include <GAMGSolver.hxx>

#include <vector2D.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::GAMGSolver::scalingFactor
(
	scalarField& x,
	const scalarField& b,
	const scalarField& Ax,
	const scalarField& D
) const
{
	scalar scalingFactorNum = 0.0;
	scalar scalingFactorDenom = 0.0;

	forAll(x, i)
	{
		scalingFactorNum += b[i] * x[i];
		scalingFactorDenom += Ax[i] * x[i];

		// While the matrix-multiply done for the scaling it is
		// possible to perform a point-Jacobi smoothing operation cheaply
		x[i] += (b[i] - Ax[i]) / D[i];
	}

	vector2D scalingVector(scalingFactorNum, scalingFactorDenom);
	reduce(scalingVector, sumOp<vector2D>());
	return scalingVector.x() / stabilise(scalingVector.y(), VSMALL);
}


tnbLib::scalar tnbLib::GAMGSolver::scalingFactor
(
	scalarField& Ax,
	const lduMatrix& A,
	scalarField& x,
	const FieldField<Field, scalar>& coupleLevelBouCoeffs,
	const lduInterfaceFieldPtrsList& interfaceLevel,
	const scalarField& b,
	const direction cmpt
) const
{
	A.Amul
	(
		Ax,
		x,
		coupleLevelBouCoeffs,
		interfaceLevel,
		cmpt
	);

	return scalingFactor
	(
		x,
		b,
		Ax,
		A.diag()
	);
}


// ************************************************************************* //