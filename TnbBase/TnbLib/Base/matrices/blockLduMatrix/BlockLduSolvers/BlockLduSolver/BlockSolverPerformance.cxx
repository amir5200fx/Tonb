#include <BlockSolverPerformance.hxx>

#include <BlockLduMatrix.hxx>
#include <Istream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::BlockSolverPerformance<Type>::checkConvergence
(
	const scalar Tolerance,
	const scalar RelTolerance
)
{
	if (blockLduMatrix::debug >= 2)
	{
		Info << solverName_
			<< ":  Iteration " << nIterations_
			<< " residual = " << finalResidual_
			<< " mag = " << mag(finalResidual_)
			<< " tol = "
			<< tnbLib::max(Tolerance, RelTolerance*mag(initialResidual_))
			<< endl;
	}

	// Reconsider evaluation of the final residual residualVector
	// - mag(residualVector) = sqrt(sum(sqr(cmpt))).  Currently used - strict
	// - cmptSum(residualVector) = consistent with 1-norm
	// - cmptMax(residualVector) = consistent with inftyNorm
	// HJ, 29/May/2014
	if
		(
			mag(finalResidual_) < Tolerance
			|| (
				RelTolerance > SMALL
				&& mag(finalResidual_) <= RelTolerance * mag(initialResidual_)
				)
			)
	{
		converged_ = true;
	}
	else
	{
		converged_ = false;
	}

	return converged_;
}


template<class Type>
bool tnbLib::BlockSolverPerformance<Type>::checkSingularity
(
	const scalar& residual
)
{
	if (mag(residual) > VSMALL)
	{
		singular_ = false;
	}
	else
	{
		singular_ = true;
	}

	return singular_;
}


template<class Type>
void tnbLib::BlockSolverPerformance<Type>::print() const
{
	if (blockLduMatrix::debug)
	{
		Info << solverName_ << ":  Solving for " << fieldName_;

		if (singular())
		{
			Info << ":  solution singularity" << endl;
		}
		else
		{
			Info << ", Initial residual = " << initialResidual_
				<< ", Final residual = " << finalResidual_
				<< ", No Iterations " << nIterations_
				<< endl;
		}
	}
}


template<class Type>
bool tnbLib::BlockSolverPerformance<Type>::operator!=
(
	const BlockSolverPerformance<Type>& bsp
	) const
{
	return
		(
			solverName() != bsp.solverName()
			|| fieldName() != bsp.fieldName()
			|| initialResidual() != bsp.initialResidual()
			|| finalResidual() != bsp.finalResidual()
			|| nIterations() != bsp.nIterations()
			|| converged() != bsp.converged()
			|| singular() != bsp.singular()
			);
}


template<class Type>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	typename tnbLib::BlockSolverPerformance<Type>& bsp
	)
{
	is.readBeginList("BlockSolverPerformance<Type>");
	is >> bsp.solverName_
		>> bsp.fieldName_
		>> bsp.initialResidual_
		>> bsp.finalResidual_
		>> bsp.nIterations_
		>> bsp.converged_
		>> bsp.singular_;
	is.readEndList("BlockSolverPerformance<Type>");

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const typename tnbLib::BlockSolverPerformance<Type>& bsp
	)
{
	os << token::BEGIN_LIST
		<< bsp.solverName_ << token::SPACE
		<< bsp.fieldName_ << token::SPACE
		<< bsp.initialResidual_ << token::SPACE
		<< bsp.finalResidual_ << token::SPACE
		<< bsp.nIterations_ << token::SPACE
		<< bsp.converged_ << token::SPACE
		<< bsp.singular_ << token::SPACE
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //