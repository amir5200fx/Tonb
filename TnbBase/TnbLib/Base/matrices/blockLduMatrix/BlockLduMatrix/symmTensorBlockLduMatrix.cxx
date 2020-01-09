#ifndef _symmTensorBlockLduMatrix_CXX
#define _symmTensorBlockLduMatrix_CXX

#include <symmTensorBlockLduMatrix.hxx>
#include <coeffFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::sumDiag()
	{
		// Decoupled version
		decoupledSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::negSumDiag()
	{
		// Decoupled version
		decoupledNegSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<symmTensor>::check() const
	{
		// Decoupled version
		decoupledCheck();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::relax
	(
		const symmTensorField& x,
		symmTensorField& b,
		const scalar alpha
	)
	{
		// Decoupled version
		decoupledRelax(x, b, alpha);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::operator*=(const scalarField& sf)
	{
		// Decoupled version
		decoupledMultEqOp(sf);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::AmulCore
	(
		symmTensorField& Ax,
		const symmTensorField& x
	) const
	{
		decoupledAmulCore(Ax, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::TmulCore
	(
		symmTensorField& Tx,
		const symmTensorField& x
	) const
	{
		// Decoupled version
		decoupledTmulCore(Tx, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::symmTensor>::segregateB
	(
		symmTensorField&,
		const symmTensorField&
	) const
	{
		FatalErrorIn
		(
			"void tnbLib::BlockLduMatrix<symmTensor>::segregateB\n"
			"(\n"
			"    symmTensorField&,\n"
			"    const symmTensorField&\n"
			") const"
		) << "Requested decoupling of symmTensor matrix - never coupled"
			<< abort(FatalError);
	}


	template<>
	tnbLib::tmp<tnbLib::symmTensorField>
		tnbLib::BlockLduMatrix<tnbLib::symmTensor>::H(const symmTensorField& x) const
	{
		// Decoupled version
		return decoupledH(x);
	}


	template<>
	tnbLib::tmp<tnbLib::symmTensorField>
		tnbLib::BlockLduMatrix<tnbLib::symmTensor>::faceH(const symmTensorField& x) const
	{
		// Decoupled version
		return decoupledFaceH(x);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmTensorBlockLduMatrix_CXX


