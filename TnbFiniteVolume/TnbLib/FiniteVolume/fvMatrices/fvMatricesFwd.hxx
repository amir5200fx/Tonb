#pragma once
#ifndef _fvMatricesFwd_Header
#define _fvMatricesFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type>
	class fvMatrix;

	typedef fvMatrix<scalar> fvScalarMatrix;
	typedef fvMatrix<vector> fvVectorMatrix;
	typedef fvMatrix<sphericalTensor> fvSphericalTensorMatrix;
	typedef fvMatrix<symmTensor> fvSymmTensorMatrix;
	typedef fvMatrix<symmTensor4thOrder> fvSymmTensor4thOrderMatrix;
	typedef fvMatrix<diagTensor> fvDiagTensorMatrix;
	typedef fvMatrix<tensor> fvTensorMatrix;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvMatricesFwd_Header
