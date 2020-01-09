#include <GAMGSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGSolver, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<GAMGSolver>
		addGAMGSolverMatrixConstructorToTable_;

	lduMatrix::solver::addasymMatrixConstructorToTable<GAMGSolver>
		addGAMGAsymSolverMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGSolver::makeAgglomeration()
{
	forAll(agglomeration_, fineLevelIndex)
	{
		agglomerateMatrix(fineLevelIndex);
	}

	if (matrixLevels_.size())
	{
		const label coarsestLevel = matrixLevels_.size() - 1;

		if (directSolveCoarsest_)
		{
			coarsestLUMatrixPtr_.set
			(
				new LUscalarMatrix
				(
					matrixLevels_[coarsestLevel],
					coupleLevelsBouCoeffs_[coarsestLevel],
					interfaceLevels_[coarsestLevel]
				)
			);
		}
	}
	else
	{
		FatalErrorIn("GAMGSolver::makeAgglomeration()")
			<< "No coarse levels created, either matrix too small for GAMG"
			" or nCellsInCoarsestLevel too large.\n"
			"    Either choose another solver of reduce "
			"nCellsInCoarsestLevel."
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GAMGSolver::GAMGSolver
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& coupleBouCoeffs,
	const FieldField<Field, scalar>& coupleIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& dict
)
	:
	lduMatrix::solver
	(
		fieldName,
		matrix,
		coupleBouCoeffs,
		coupleIntCoeffs,
		interfaces,
		dict
	),

	// Default values for all controls
	// which may be overridden by those in dict
	cacheAgglomeration_(false),
	nPreSweeps_(0),
	nPostSweeps_(2),
	nFinestSweeps_(2),
	scaleCorrection_(matrix.symmetric()),
	directSolveCoarsest_(false),
	agglomeration_(GAMGAgglomeration::New(matrix_, dict)),

	matrixLevels_(agglomeration_.size()),
	interfaceLevels_(agglomeration_.size()),
	coupleLevelsBouCoeffs_(agglomeration_.size()),
	coupleLevelsIntCoeffs_(agglomeration_.size())
{
	readControls();
	makeAgglomeration();
}



// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::GAMGSolver::~GAMGSolver()
{
	// Clear the the lists of pointers to the interfaces
	forAll(interfaceLevels_, leveli)
	{
		lduInterfaceFieldPtrsList& curLevel = interfaceLevels_[leveli];

		forAll(curLevel, i)
		{
			if (curLevel.set(i))
			{
				delete curLevel(i);
			}
		}
	}

	if (!cacheAgglomeration_)
	{
		delete &agglomeration_;
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGSolver::readControls()
{
	lduMatrix::solver::readControls();

	dict().readIfPresent("cacheAgglomeration", cacheAgglomeration_);
	dict().readIfPresent("nPreSweeps", nPreSweeps_);
	dict().readIfPresent("nPostSweeps", nPostSweeps_);
	dict().readIfPresent("nFinestSweeps", nFinestSweeps_);
	dict().readIfPresent("scaleCorrection", scaleCorrection_);
	dict().readIfPresent("directSolveCoarsest", directSolveCoarsest_);
}


const tnbLib::lduMatrix& tnbLib::GAMGSolver::matrixLevel(const label i) const
{
	if (i == 0)
	{
		return matrix_;
	}
	else
	{
		return matrixLevels_[i - 1];
	}
}


const tnbLib::lduInterfaceFieldPtrsList& tnbLib::GAMGSolver::interfaceLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return interfaces_;
	}
	else
	{
		return interfaceLevels_[i - 1];
	}
}


const tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>&
tnbLib::GAMGSolver::coupleBouCoeffsLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return coupleBouCoeffs_;
	}
	else
	{
		return coupleLevelsBouCoeffs_[i - 1];
	}
}


const tnbLib::FieldField<tnbLib::Field, tnbLib::scalar>&
tnbLib::GAMGSolver::coupleIntCoeffsLevel
(
	const label i
) const
{
	if (i == 0)
	{
		return coupleIntCoeffs_;
	}
	else
	{
		return coupleLevelsIntCoeffs_[i - 1];
	}
}


// ************************************************************************* //