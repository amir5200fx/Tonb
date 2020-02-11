#pragma once
#ifndef _volFields_Header
#define _volFields_Header

#include <objectRegistry.hxx>
#include <GeometricFields.hxx>
#include <volMesh.hxx>
#include <fvMesh.hxx>
#include <fvPatchFields.hxx>
#include <volFieldsFwd.hxx>
#include <calculatedFvPatchFields.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	tmp<GeometricField<scalar, fvPatchField, volMesh> >
		GeometricField<scalar, fvPatchField, volMesh>::component
		(
			const direction
		) const;

	template<>
	void GeometricField<scalar, fvPatchField, volMesh>::replace
	(
		const direction,
		const GeometricField<scalar, fvPatchField, volMesh>& sf
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volFields_Header
