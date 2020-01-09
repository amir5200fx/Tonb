#include <tensorBlockCholeskyPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockCholeskyPrecon<tensor>::calcPreconDiag()
	{
		// Decoupled version
		calcDecoupledPreconDiag();
	}


	template<>
	void tnbLib::BlockCholeskyPrecon<tensor>::precondition
	(
		tensorField& x,
		const tensorField& b
	) const
	{
		// Decoupled version
		decoupledPrecondition(x, b);
	}


	template<>
	void tnbLib::BlockCholeskyPrecon<tensor>::preconditionT
	(
		tensorField& xT,
		const tensorField& bT
	) const
	{
		// Decoupled version
		decoupledPreconditionT(xT, bT);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //