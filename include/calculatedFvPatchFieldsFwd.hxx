#pragma once
#ifndef _calculatedFvPatchFieldsFwd_Header
#define _calculatedFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class calculatedFvPatchField;

	typedef calculatedFvPatchField<scalar> calculatedFvPatchScalarField;
	typedef calculatedFvPatchField<vector> calculatedFvPatchVectorField;
	typedef calculatedFvPatchField<sphericalTensor> calculatedFvPatchSphericalTensorField;
	typedef calculatedFvPatchField<symmTensor> calculatedFvPatchSymmTensorField;
	typedef calculatedFvPatchField<symmTensor4thOrder> calculatedFvPatchSymmTensor4thOrderField;
	typedef calculatedFvPatchField<diagTensor> calculatedFvPatchDiagTensorField;
	typedef calculatedFvPatchField<tensor> calculatedFvPatchTensorField;

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calculatedFvPatchFieldsFwd_Header
