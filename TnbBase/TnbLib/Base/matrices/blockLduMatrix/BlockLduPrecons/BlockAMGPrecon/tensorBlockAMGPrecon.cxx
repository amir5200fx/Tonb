#include <tensorBlockAMGPrecon.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockAMGPrecon<tensor>::precondition
	(
		tensorField& x,
		const tensorField& b
	) const
	{
		// Decoupled version
		notImplemented("void tnbLib::BlockAMGPrecon<tensor>::precondition");
	}


	// template<>
	// void tnbLib::BlockAMGPrecon<tensor>::preconditionT
	// (
	//     tensorField& xT,
	//     const tensorField& bT
	// ) const
	// {
	//     // Decoupled version
	//     decoupledPreconditionT(xT, bT);
	// }


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //