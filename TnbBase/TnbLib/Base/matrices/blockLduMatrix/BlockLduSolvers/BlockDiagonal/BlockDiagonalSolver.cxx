#include <BlockDiagonalSolver.hxx>

#include <CoeffField.hxx>
#include <BlockSolverPerformance.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

//- Construct from matrix
template<class Type>
tnbLib::BlockDiagonalSolver<Type>::BlockDiagonalSolver
(
	const word& fieldName,
	const BlockLduMatrix<Type>& matrix,
	const dictionary& dict
)
	:
	BlockLduSolver<Type>(fieldName, matrix, dict)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::BlockSolverPerformance<Type>
tnbLib::BlockDiagonalSolver<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& b
)
{
	CoeffField<Type> dD = inv(this->matrix_.diag());

	multiply(x, b, dD);

	return BlockSolverPerformance<Type>
		(
			this->typeName,
			this->fieldName(),
			pTraits<Type>::zero,
			pTraits<Type>::zero,
			0,
			true,
			false
			);
}


// ************************************************************************* //