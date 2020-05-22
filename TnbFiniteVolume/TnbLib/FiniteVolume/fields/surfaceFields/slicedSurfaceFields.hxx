#pragma once
#ifndef _slicedSurfaceFields_Header
#define _slicedSurfaceFields_Header

#include <SlicedGeometricField.hxx>
#include <slicedFvsPatchField.hxx>
#include <surfaceMesh.hxx>
#include <slicedSurfaceFieldsFwd.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	inline void
		SlicedGeometricField<scalar, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<vector, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<sphericalTensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<symmTensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}

	template<>
	inline void
		SlicedGeometricField<tensor, fvsPatchField, slicedFvsPatchField, surfaceMesh>::
		correctBoundaryConditions()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_slicedSurfaceFields_Header
