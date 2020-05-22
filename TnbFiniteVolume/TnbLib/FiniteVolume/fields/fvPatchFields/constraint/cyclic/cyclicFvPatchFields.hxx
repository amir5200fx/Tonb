#pragma once
#ifndef _cyclicFvPatchFields_Header
#define _cyclicFvPatchFields_Header

#include <cyclicFvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef cyclicFvPatchField<scalar> cyclicFvPatchScalarField;
	typedef cyclicFvPatchField<vector> cyclicFvPatchVectorField;
	typedef cyclicFvPatchField<sphericalTensor> cyclicFvPatchSphericalTensorField;
	typedef cyclicFvPatchField<symmTensor> cyclicFvPatchSymmTensorField;
	typedef cyclicFvPatchField<symmTensor4thOrder> cyclicFvPatchSymmTensor4thOrderField;
	typedef cyclicFvPatchField<diagTensor> cyclicFvPatchDiagTensorField;
	typedef cyclicFvPatchField<tensor> cyclicFvPatchTensorField;

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatchFields_Header
