#pragma once
#ifndef _slicedSurfaceFieldsFwd_Header
#define _slicedSurfaceFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class surfaceMesh;

	template<class Type>
	class fvsPatchField;

	template<class Type>
	class slicedFvsPatchField;

	template
		<
		class Type,
		template<class> class PatchField,
		template<class> class SlicedPatchField,
		class GeoMesh
		>
		class SlicedGeometricField;

	typedef
		SlicedGeometricField<scalar, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceScalarField;

	typedef
		SlicedGeometricField<vector, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceVectorField;

	typedef
		SlicedGeometricField<sphericalTensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceSphericalTensorField;

	typedef
		SlicedGeometricField<symmTensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceSymmTensorField;

	typedef
		SlicedGeometricField<symmTensor4thOrder, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceSymmTensor4thOrderField;

	typedef
		SlicedGeometricField<diagTensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceDiagTensorField;

	typedef
		SlicedGeometricField<tensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>
		slicedSurfaceTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_slicedSurfaceFieldsFwd_Header
