#include <tensorBlockGaussSeidelPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void BlockGaussSeidelPrecon<tensor>::calcInvDiag()
	{
		calcDecoupledInvDiag();
	}


	template<>
	void BlockGaussSeidelPrecon<tensor>::precondition
	(
		tensorField& x,
		const tensorField& b
	) const
	{
		// Decoupled version
		decoupledPrecondition(x, b);
	}


	template<>
	void BlockGaussSeidelPrecon<tensor>::preconditionT
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