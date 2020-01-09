#ifndef _sphericalTensorBlockLduMatrix_CXX
#define _sphericalTensorBlockLduMatrix_CXX

#include <BlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::sumDiag()
	{
		// Decoupled version
		decoupledSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::negSumDiag()
	{
		// Decoupled version
		decoupledNegSumDiag();
	}


	template<>
	void tnbLib::BlockLduMatrix<sphericalTensor>::check() const
	{
		// Decoupled version
		decoupledCheck();
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::relax
	(
		const sphericalTensorField& x,
		sphericalTensorField& b,
		const scalar alpha
	)
	{
		// Decoupled version
		decoupledRelax(x, b, alpha);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::operator*=
		(
			const scalarField& sf
			)
	{
		// Decoupled version
		decoupledMultEqOp(sf);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::AmulCore
	(
		sphericalTensorField& Ax,
		const sphericalTensorField& x
	) const
	{
		decoupledAmulCore(Ax, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::TmulCore
	(
		sphericalTensorField& Tx,
		const sphericalTensorField& x
	) const
	{
		// Decoupled version
		decoupledTmulCore(Tx, x);
	}


	template<>
	void tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::segregateB
	(
		sphericalTensorField&,
		const sphericalTensorField&
	) const
	{
		FatalErrorIn
		(
			"void tnbLib::BlockLduMatrix<sphericalTensor>::segregateB\n"
			"(\n"
			"    sphericalTensorField&,\n"
			"    const sphericalTensorField&\n"
			") const"
		) << "Requested decoupling of sphericalTensor matrix - never coupled"
			<< abort(FatalError);
	}


	template<>
	tnbLib::tmp<tnbLib::sphericalTensorField>
		tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::H
		(
			const sphericalTensorField& x
		) const
	{
		// Decoupled version
		return decoupledH(x);
	}


	template<>
	tnbLib::tmp<tnbLib::sphericalTensorField>
		tnbLib::BlockLduMatrix<tnbLib::sphericalTensor>::faceH
		(
			const sphericalTensorField& x
		) const
	{
		// Decoupled version
		return decoupledFaceH(x);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sphericalTensorBlockLduMatrix_CXX
