#pragma once
#ifndef _surfaceInterpolate_Header
#define _surfaceInterpolate_Header

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <surfaceInterpolationScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		//- Return weighting factors for scheme given from Istream
		template<class Type>
		extern tmp<surfaceInterpolationScheme<Type> > scheme
		(
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);

		//- Return weighting factors for scheme given by name in dictionary
		template<class Type>
		extern tmp<surfaceInterpolationScheme<Type> > scheme
		(
			const surfaceScalarField& faceFlux,
			const word& name
		);


		//- Return weighting factors for scheme given from Istream
		template<class Type>
		extern tmp<surfaceInterpolationScheme<Type> > scheme
		(
			const fvMesh& mesh,
			Istream& schemeData
		);

		//- Return weighting factors for scheme given by name in dictionary
		template<class Type>
		extern tmp<surfaceInterpolationScheme<Type> > scheme
		(
			const fvMesh& mesh,
			const word& name
		);


		//- Interpolate field onto faces using scheme given by Istream
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const surfaceScalarField& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf,
			const surfaceScalarField& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const tmp<surfaceScalarField>& faceFlux,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf,
			const tmp<surfaceScalarField>& faceFlux,
			const word& name
		);


		//- Interpolate field onto faces using scheme given by Istream
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			Istream& schemeData
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf,
			const word& name
		);

		//- Interpolate field onto faces using scheme given by name in fvSchemes
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf,
			const word& name
		);


		//- Interpolate tmp field onto faces using central differencing
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvf
		);

		//- Interpolate field onto faces using central differencing
		template<class Type>
		extern tmp<GeometricField<Type, fvsPatchField, surfaceMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>& tvf
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <surfaceInterpolateI.hxx>

#ifdef NoRepository
#   include <surfaceInterpolate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolate_Header
