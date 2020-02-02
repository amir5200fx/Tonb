#pragma once
#ifndef _transformFvPatchFields_Header
#define _transformFvPatchFields_Header

#include <transformFvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	typedef transformFvPatchField<scalar> transformFvPatchScalarField;
	typedef transformFvPatchField<vector> transformFvPatchVectorField;
	typedef transformFvPatchField<sphericalTensor> transformFvPatchSphericalTensorField;
	typedef transformFvPatchField<symmTensor> transformFvPatchSymmTensorField;
	typedef transformFvPatchField<symmTensor4thOrder> transformFvPatchSymmTensor4thOrderField;
	typedef transformFvPatchField<diagTensor> transformFvPatchDiagTensorField;
	typedef transformFvPatchField<tensor> transformFvPatchTensorField;

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformFvPatchFields_Header
