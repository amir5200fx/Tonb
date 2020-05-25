#pragma once
#ifndef _slicedVolFieldsFwd_Header
#define _slicedVolFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class volMesh;

	template<class Type>
	class fvPatchField;

	template<class Type>
	class slicedFvPatchField;

	template
		<
		class Type,
		template<class> class PatchField,
		template<class> class SlicedPatchField,
		class GeoMesh
		>
		class SlicedGeometricField;

	typedef
		SlicedGeometricField<scalar, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolScalarField;

	typedef
		SlicedGeometricField<vector, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolVectorField;

	typedef
		SlicedGeometricField<sphericalTensor, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolSphericalTensorField;

	typedef
		SlicedGeometricField<symmTensor, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolSymmTensorField;

	typedef
		SlicedGeometricField<symmTensor4thOrder, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolSymmTensor4thOrderField;

	typedef
		SlicedGeometricField<diagTensor, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolDiagTensorField;

	typedef
		SlicedGeometricField<tensor, fvPatchField, slicedFvPatchField, volMesh>
		slicedVolTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


#endif // !_slicedVolFieldsFwd_Header
