#ifndef _tensorBlockLduMatrix_CXX
#define _tensorBlockLduMatrix_CXX

#include <tensorBlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::sumDiag()
	{
		// Decoupled version
		decoupledSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::negSumDiag()
	{
		// Decoupled version
		decoupledNegSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<tensor>::check() const
	{
		// Decoupled version
		decoupledCheck();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::relax
	(
		const tensorField& x,
		tensorField& b,
		const scalar alpha
	)
	{
		// Decoupled version
		decoupledRelax(x, b, alpha);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::operator*=(const scalarField& sf)
	{
		// Decoupled version
		decoupledMultEqOp(sf);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::AmulCore
	(
		tensorField& Ax,
		const tensorField& x
	) const
	{
		decoupledAmulCore(Ax, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::TmulCore
	(
		tensorField& Tx,
		const tensorField& x
	) const
	{
		// Decoupled version
		decoupledTmulCore(Tx, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::tensor>::segregateB
	(
		tensorField&,
		const tensorField&
	) const
	{
		FatalErrorIn
		(
			"void tnbLib::BlockLduMatrix<tensor>::segregateB\n"
			"(\n"
			"    tensorField&,\n"
			"    const tensorField&\n"
			") const"
		) << "Requested decoupling of tensor matrix - never coupled"
			<< abort(FatalError);
	}


	template<>
	tnbLib::tmp<tnbLib::tensorField>
		tnbLib::BlockLduMatrix<tnbLib::tensor>::H(const tensorField& x) const
	{
		// Decoupled version
		return decoupledH(x);
	}


	template<>
	tnbLib::tmp<tnbLib::tensorField>
		tnbLib::BlockLduMatrix<tnbLib::tensor>::faceH(const tensorField& x) const
	{
		// Decoupled version
		return decoupledFaceH(x);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tensorBlockLduMatrix_CXX
