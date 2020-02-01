#pragma once
#ifndef _fvPatchFieldsFwd_Header
#define _fvPatchFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fvPatchField;

	typedef fvPatchField<scalar> fvPatchScalarField;
	typedef fvPatchField<vector> fvPatchVectorField;
	typedef fvPatchField<sphericalTensor> fvPatchSphericalTensorField;
	typedef fvPatchField<symmTensor> fvPatchSymmTensorField;
	typedef fvPatchField<symmTensor4thOrder> fvPatchSymmTensor4thOrderField;
	typedef fvPatchField<diagTensor> fvPatchDiagTensorField;
	typedef fvPatchField<tensor> fvPatchTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvPatchFieldsFwd_Header
