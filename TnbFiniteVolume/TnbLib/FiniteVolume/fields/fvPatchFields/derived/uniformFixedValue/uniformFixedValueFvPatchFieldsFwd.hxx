#pragma once
#ifndef _uniformFixedValueFvPatchFieldsFwd_Header
#define _uniformFixedValueFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class uniformFixedValueFvPatchField;
	template<class Type> class uniformFvPatchField;

	typedef uniformFvPatchField<scalar> uniformFvPatchScalarField;
	typedef uniformFvPatchField<vector> uniformFvPatchVectorField;
	typedef uniformFvPatchField<sphericalTensor> uniformFvPatchSphericalTensorField;
	typedef uniformFvPatchField<symmTensor> uniformFvPatchSymmTensorField;
	typedef uniformFvPatchField<symmTensor4thOrder> uniformFvPatchSymmTensor4thOrderField;
	typedef uniformFvPatchField<diagTensor> uniformFvPatchDiagTensorField;
	typedef uniformFvPatchField<tensor> uniformFvPatchTensorField;

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_uniformFixedValueFvPatchFieldsFwd_Header
