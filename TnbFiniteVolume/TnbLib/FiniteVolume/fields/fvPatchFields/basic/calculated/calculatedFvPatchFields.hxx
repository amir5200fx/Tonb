#pragma once
#ifndef _calculatedFvPatchFields_Header
#define _calculatedFvPatchFields_Header

#include <calculatedFvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

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

#endif // !_calculatedFvPatchFields_Header
