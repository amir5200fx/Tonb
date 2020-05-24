#pragma once
#ifndef _volFieldsFwd_Header
#define _volFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class volMesh;

	template<class Type>
	class fvPatchField;

	template<class Type, template<class> class PatchField, class GeoMesh>
	class GeometricField;

	typedef GeometricField<scalar, fvPatchField, volMesh> volScalarField;
	typedef GeometricField<vector, fvPatchField, volMesh> volVectorField;
	typedef GeometricField<sphericalTensor, fvPatchField, volMesh>
		volSphericalTensorField;
	typedef GeometricField<symmTensor, fvPatchField, volMesh> volSymmTensorField;
	typedef GeometricField<symmTensor4thOrder, fvPatchField, volMesh>
		volSymmTensor4thOrderField;
	typedef GeometricField<diagTensor, fvPatchField, volMesh> volDiagTensorField;
	typedef GeometricField<tensor, fvPatchField, volMesh> volTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volFieldsFwd_Header
