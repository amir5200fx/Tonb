#pragma once
#ifndef _fvsPatchFieldsFwd_Header
#define _fvsPatchFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fvsPatchField;

	typedef fvsPatchField<scalar> fvsPatchScalarField;
	typedef fvsPatchField<vector> fvsPatchVectorField;
	typedef fvsPatchField<sphericalTensor> fvsPatchSphericalTensorField;
	typedef fvsPatchField<symmTensor> fvsPatchSymmTensorField;
	typedef fvsPatchField<symmTensor4thOrder> fvsPatchSymmTensor4thOrderField;
	typedef fvsPatchField<diagTensor> fvsPatchDiagTensorField;
	typedef fvsPatchField<tensor> fvsPatchTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvsPatchFieldsFwd_Header
