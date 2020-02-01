#pragma once
#ifndef _surfaceVectorNFieldsFwd_Header
#define _surfaceVectorNFieldsFwd_Header

#include <surfaceFieldsFwd.hxx>
#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class surfaceMesh;

	template<class Type>
	class fvsPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

#define doMakeTypedefs(type, Type, args)         \
    typedef GeometricField<type, fvsPatchField, surfaceMesh> surface##Type##Field;

	typedef GeometricField<vector2, fvsPatchField, surfaceMesh> surfaceVector2Field;
	typedef GeometricField<vector3, fvsPatchField, surfaceMesh> surfaceVector3Field;
	typedef GeometricField<vector4, fvsPatchField, surfaceMesh> surfaceVector4Field;
	typedef GeometricField<vector6, fvsPatchField, surfaceMesh> surfaceVector6Field;
	typedef GeometricField<vector8, fvsPatchField, surfaceMesh> surfaceVector8Field;

		
	typedef GeometricField<tensor2, fvsPatchField, surfaceMesh> surfaceTensor2Field;
	typedef GeometricField<tensor3, fvsPatchField, surfaceMesh> surfaceTensor3Field;
	typedef GeometricField<tensor4, fvsPatchField, surfaceMesh> surfaceTensor4Field;
	typedef GeometricField<tensor6, fvsPatchField, surfaceMesh> surfaceTensor6Field;
	typedef GeometricField<tensor8, fvsPatchField, surfaceMesh> surfaceTensor8Field;

		
	typedef GeometricField<diagTensor2, fvsPatchField, surfaceMesh> surfaceDiagTensor2Field;
	typedef GeometricField<diagTensor3, fvsPatchField, surfaceMesh> surfaceDiagTensor3Field;
	typedef GeometricField<diagTensor4, fvsPatchField, surfaceMesh> surfaceDiagTensor4Field;
	typedef GeometricField<diagTensor6, fvsPatchField, surfaceMesh> surfaceDiagTensor6Field;
	typedef GeometricField<diagTensor8, fvsPatchField, surfaceMesh> surfaceDiagTensor8Field;

		
	typedef GeometricField<sphericalTensor2, fvsPatchField, surfaceMesh> surfaceSphericalTensor2Field;
	typedef GeometricField<sphericalTensor3, fvsPatchField, surfaceMesh> surfaceSphericalTensor3Field;
	typedef GeometricField<sphericalTensor4, fvsPatchField, surfaceMesh> surfaceSphericalTensor4Field;
	typedef GeometricField<sphericalTensor6, fvsPatchField, surfaceMesh> surfaceSphericalTensor6Field;
	typedef GeometricField<sphericalTensor8, fvsPatchField, surfaceMesh> surfaceSphericalTensor8Field;

#undef doMakeTypedefs

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceVectorNFieldsFwd_Header
