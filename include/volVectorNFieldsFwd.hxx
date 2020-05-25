#pragma once
#ifndef _volVectorNFieldsFwd_Header
#define _volVectorNFieldsFwd_Header

#include <volFieldsFwd.hxx>
#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class volMesh;

	template<class Type>
	class fvPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

#define doMakeTypedefs(type, Type, args)         \
    typedef GeometricField<type, fvPatchField, volMesh> vol##Type##Field;

	typedef GeometricField<vector2, fvPatchField, volMesh> volVector2Field;
	typedef GeometricField<vector3, fvPatchField, volMesh> volVector3Field;
	typedef GeometricField<vector4, fvPatchField, volMesh> volVector4Field;
	typedef GeometricField<vector6, fvPatchField, volMesh> volVector6Field;
	typedef GeometricField<vector8, fvPatchField, volMesh> volVector8Field;

		
	typedef GeometricField<tensor2, fvPatchField, volMesh> volTensor2Field;
	typedef GeometricField<tensor3, fvPatchField, volMesh> volTensor3Field;
	typedef GeometricField<tensor4, fvPatchField, volMesh> volTensor4Field;
	typedef GeometricField<tensor6, fvPatchField, volMesh> volTensor6Field;
	typedef GeometricField<tensor8, fvPatchField, volMesh> volTensor8Field;

		
	typedef GeometricField<diagTensor2, fvPatchField, volMesh> volDiagTensor2Field;
	typedef GeometricField<diagTensor3, fvPatchField, volMesh> volDiagTensor3Field;
	typedef GeometricField<diagTensor4, fvPatchField, volMesh> volDiagTensor4Field;
	typedef GeometricField<diagTensor6, fvPatchField, volMesh> volDiagTensor6Field;
	typedef GeometricField<diagTensor8, fvPatchField, volMesh> volDiagTensor8Field;

		
	typedef GeometricField<sphericalTensor2, fvPatchField, volMesh> volSphericalTensor2Field;
	typedef GeometricField<sphericalTensor3, fvPatchField, volMesh> volSphericalTensor3Field;
	typedef GeometricField<sphericalTensor4, fvPatchField, volMesh> volSphericalTensor4Field;
	typedef GeometricField<sphericalTensor6, fvPatchField, volMesh> volSphericalTensor6Field;
	typedef GeometricField<sphericalTensor8, fvPatchField, volMesh> volSphericalTensor8Field;

#undef doMakeTypedefs

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volVectorNFieldsFwd_Header
