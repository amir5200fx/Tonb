#pragma once
#ifndef _surfaceFieldsFwd_Header
#define _surfaceFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class surfaceMesh;

	template<class Type>
	class fvsPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

	typedef GeometricField<scalar, fvsPatchField, surfaceMesh> surfaceScalarField;
	typedef GeometricField<vector, fvsPatchField, surfaceMesh> surfaceVectorField;
	typedef GeometricField<sphericalTensor, fvsPatchField, surfaceMesh>
		surfaceSphericalTensorField;
	typedef GeometricField<symmTensor, fvsPatchField, surfaceMesh>
		surfaceSymmTensorField;
	typedef GeometricField<symmTensor4thOrder, fvsPatchField, surfaceMesh>
		surfaceSymmTensor4thOrderField;
	typedef GeometricField<diagTensor, fvsPatchField, surfaceMesh>
		surfaceDiagTensorField;
	typedef GeometricField<tensor, fvsPatchField, surfaceMesh> surfaceTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceFieldsFwd_Header
