#include <blockLduMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>
		 
#include <blockLduPrecons.hxx>
#include <BlockNoPrecon.hxx>
#include <blockDiagonalPrecons.hxx>
#include <blockGaussSeidelPrecons.hxx>
#include <BlockCholeskyPrecon.hxx>
#include <BlockILUCpPrecon.hxx>
		 
#include <blockLduSmoothers.hxx>
#include <blockGaussSeidelSmoothers.hxx>
#include <BlockILUSmoother.hxx>
#include <BlockILUCpSmoother.hxx>
		 
#include <blockLduSolvers.hxx>
#include <BlockDiagonalSolver.hxx>
#include <BlockBiCGStabSolver.hxx>
#include <BlockCGSolver.hxx>
#include <BlockGaussSeidelSolver.hxx>
#include <BlockGMRESSolver.hxx>

// KRJ: 2012-12-15: Multigrid solver
#include <blockAMGSolvers.hxx>
#include <blockAMGPrecons.hxx>
#include <blockMatrixCoarsenings.hxx>
#include <blockMatrixAgglomerations.hxx>
#include <blockCoeffNorms.hxx>
#include <blockCoeffTwoNorms.hxx>
#include <blockCoeffMaxNorms.hxx>
#include <blockCoeffComponentNorms.hxx>
		 
#include <VectorTensorNFields.hxx>
#include <ExpandTensorN.hxx>
#include <ExpandTensorNField.hxx>
#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeSolver(type, Type, args)                                       \
/* Preconditioners */                                                         \
typedef BlockLduPrecon<type > block##Type##Precon;                            \
defineNamedTemplateTypeNameAndDebug(block##Type##Precon, 0);                  \
defineTemplateRunTimeSelectionTable(block##Type##Precon, dictionary);         \
                                                                              \
typedef BlockNoPrecon<type > block##Type##NoPrecon;                           \
makeBlockPrecon(block##Type##Precon, block##Type##NoPrecon);                  \
                                                                              \
typedef BlockDiagonalPrecon<type > block##Type##DiagonalPrecon;               \
makeBlockPrecon(block##Type##Precon, block##Type##DiagonalPrecon);            \
                                                                              \
typedef BlockGaussSeidelPrecon<type > block##Type##GaussSeidelPrecon;         \
makeBlockPrecon(block##Type##Precon, block##Type##GaussSeidelPrecon);         \
                                                                              \
typedef BlockCholeskyPrecon<type > block##Type##CholeskyPrecon;               \
makeBlockPrecon(block##Type##Precon, block##Type##CholeskyPrecon);            \
                                                                              \
typedef BlockILUCpPrecon<type > block##Type##ILUCpPrecon;                     \
makeBlockPrecon(block##Type##Precon, block##Type##ILUCpPrecon);               \
                                                                              \
/* Smoothers */                                                               \
typedef BlockLduSmoother<type > block##Type##Smoother;                        \
defineNamedTemplateTypeNameAndDebug(block##Type##Smoother, 0);                \
defineTemplateRunTimeSelectionTable(block##Type##Smoother, dictionary);       \
                                                                              \
typedef BlockGaussSeidelSmoother<type > block##Type##GaussSeidelSmoother;     \
makeBlockSmoother(block##Type##Smoother, block##Type##GaussSeidelSmoother);   \
                                                                              \
typedef BlockILUSmoother<type > block##Type##ILUSmoother;                     \
makeBlockSmoother(block##Type##Smoother, block##Type##ILUSmoother);           \
                                                                              \
typedef BlockILUCpSmoother<type > block##Type##ILUCpSmoother;                 \
makeBlockSmoother(block##Type##Smoother, block##Type##ILUCpSmoother);         \
                                                                              \
                                                                              \
/* Solvers */                                                                 \
typedef BlockLduSolver<type > block##Type##Solver;                            \
defineNamedTemplateTypeNameAndDebug(block##Type##Solver, 0);                  \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    block##Type##Solver,                                                      \
    symMatrix                                                                 \
);                                                                            \
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    block##Type##Solver,                                                      \
    asymMatrix                                                                \
);                                                                            \
                                                                              \
typedef BlockDiagonalSolver<type > block##Type##DiagonalSolver;               \
defineNamedTemplateTypeNameAndDebug(block##Type##DiagonalSolver, 0);          \
                                                                              \
typedef BlockBiCGStabSolver<type > block##Type##BiCGStabSolver;               \
makeBlockSolverTypeName(block##Type##BiCGStabSolver);                         \
addSolverToBlockMatrix(Type, block##Type##BiCGStabSolver, symMatrix);         \
addSolverToBlockMatrix(Type, block##Type##BiCGStabSolver, asymMatrix);        \
                                                                              \
typedef BlockCGSolver<type > block##Type##CGSolver;                           \
makeBlockSolverTypeName(block##Type##CGSolver);                               \
addSolverToBlockMatrix(Type, block##Type##CGSolver, symMatrix);               \
                                                                              \
typedef BlockGaussSeidelSolver<type > block##Type##GaussSeidelSolver;         \
makeBlockSolverTypeName(block##Type##GaussSeidelSolver);                      \
addSolverToBlockMatrix(Type, block##Type##GaussSeidelSolver, symMatrix);      \
addSolverToBlockMatrix(Type, block##Type##GaussSeidelSolver, asymMatrix);     \
                                                                              \
typedef BlockGMRESSolver<type > block##Type##GMRESSolver;                     \
makeBlockSolverTypeName(block##Type##GMRESSolver);                            \
addSolverToBlockMatrix(Type, block##Type##GMRESSolver, symMatrix);            \
addSolverToBlockMatrix(Type, block##Type##GMRESSolver, asymMatrix);           \
                                                                              \
typedef BlockMatrixCoarsening<type > block##Type##MatrixCoarsening;           \
defineNamedTemplateTypeNameAndDebug(block##Type##MatrixCoarsening, 0);        \
defineTemplateRunTimeSelectionTable(block##Type##MatrixCoarsening, matrix);   \
                                                                              \
typedef BlockMatrixAgglomeration<type > block##Type##MatrixAgglomeration;     \
makeBlockMatrixCoarsening(block##Type##MatrixCoarsening, block##Type##MatrixAgglomeration); \
                                                                              \
typedef BlockCoeffNorm<type > block##Type##CoeffNorm;                         \
defineNamedTemplateTypeNameAndDebug(block##Type##CoeffNorm, 0);               \
defineTemplateRunTimeSelectionTable(block##Type##CoeffNorm, dictionary);      \
                                                                              \
typedef BlockCoeffTwoNorm<type > block##Type##CoeffTwoNorm;                   \
makeBlockCoeffNorm(block##Type##CoeffNorm, block##Type##CoeffTwoNorm);        \
                                                                              \
typedef BlockCoeffComponentNorm<type > block##Type##CoeffComponentNorm;       \
makeBlockCoeffNorm(block##Type##CoeffNorm, block##Type##CoeffComponentNorm);  \
                                                                              \
typedef BlockCoeffMaxNorm<type > block##Type##CoeffMaxNorm;                   \
makeBlockCoeffNorm(block##Type##CoeffNorm, block##Type##CoeffMaxNorm);        \
                                                                              \
typedef BlockAMGSolver<type > block##Type##AmgSolver;                         \
makeBlockSolverTypeName(block##Type##AmgSolver);                              \
addSolverToBlockMatrix(Type, block##Type##AmgSolver, symMatrix);              \
addSolverToBlockMatrix(Type, block##Type##AmgSolver, asymMatrix);             \
                                                                              \
typedef BlockAMGPrecon<type > block##Type##AmgPrecon;                         \
makeBlockPrecon(block##Type##Precon, block##Type##AmgPrecon);                 \

	forAllVectorNTypes(makeSolver)

#undef makeSolver

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //