#pragma once
#ifndef _surfaceInterpolationScheme_Header
#define _surfaceInterpolationScheme_Header

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	/*---------------------------------------------------------------------------*\
					 Class surfaceInterpolationScheme Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class surfaceInterpolationScheme
		:
		public refCount
	{
		// Private data

			//- Hold reference to mesh
		const fvMesh& mesh_;


		// Private Member Functions

			//- Disallow copy construct
		surfaceInterpolationScheme(const surfaceInterpolationScheme&);

		//- Disallow default bitwise assignment
		void operator=(const surfaceInterpolationScheme&);


	public:

		//- Runtime type information
		TypeName("surfaceInterpolationScheme");


		// Declare run-time constructor selection tables

		declareRunTimeSelectionTable
		(
			tmp,
			surfaceInterpolationScheme,
			Mesh,
			(
				const fvMesh& mesh,
				Istream& schemeData
				),
				(mesh, schemeData)
		);

		declareRunTimeSelectionTable
		(
			tmp,
			surfaceInterpolationScheme,
			MeshFlux,
			(
				const fvMesh& mesh,
				const surfaceScalarField& faceFlux,
				Istream& schemeData
				),
				(mesh, faceFlux, schemeData)
		);


		// Constructors

			//- Construct from mesh
		surfaceInterpolationScheme(const fvMesh& mesh)
			:
			mesh_(mesh)
		{}


		// Selectors

			//- Return new tmp interpolation scheme
		static tmp<surfaceInterpolationScheme<Type> > New
		(
			const fvMesh& mesh,
			Istream& schemeData
		);

		//- Return new tmp interpolation scheme
		static tmp<surfaceInterpolationScheme<Type> > New
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		);


		//- Destructor
		virtual ~surfaceInterpolationScheme();


		// Member Functions

			//- Return mesh reference
		const fvMesh& mesh() const
		{
			return mesh_;
		}


		//- Return the face-interpolate of the given cell field
		//  with the given owner and neighbour weigting factors
		static tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			interpolate
			(
				const GeometricField<Type, fvPatchField, volMesh>&,
				const tmp<surfaceScalarField>&,
				const tmp<surfaceScalarField>&
			);

		//- Return the face-interpolate of the given cell field
		//  with the given weighting factors
		static tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			interpolate
			(
				const GeometricField<Type, fvPatchField, volMesh>&,
				const tmp<surfaceScalarField>&
			);


		//- Return the interpolation weighting factors for the given field
		virtual tmp<surfaceScalarField> weights
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const = 0;

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return false;
		}

		//- Return the explicit correction to the face-interpolate
		//  for the given field
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			correction(const GeometricField<Type, fvPatchField, volMesh>&) const
		{
			return tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >(NULL);
		}

		//- Return the face-interpolate of the given cell field
		//  with explicit correction
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			interpolate(const GeometricField<Type, fvPatchField, volMesh>&) const;

		//- Return the face-interpolate of the given tmp cell field
		//  with explicit correction
		tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			interpolate
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >&
			) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeSurfaceInterpolationTypeScheme(SS, Type)                           \
                                                                               \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                              \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshConstructorToTable<SS<Type> >         \
    add##SS##Type##MeshConstructorToTable_;                                    \
                                                                               \
surfaceInterpolationScheme<Type>::addMeshFluxConstructorToTable<SS<Type> >     \
    add##SS##Type##MeshFluxConstructorToTable_;

#define makeSurfaceInterpolationScheme(SS)                                     \
                                                                               \
makeSurfaceInterpolationTypeScheme(SS, scalar)                                 \
makeSurfaceInterpolationTypeScheme(SS, vector)                                 \
makeSurfaceInterpolationTypeScheme(SS, sphericalTensor)                        \
makeSurfaceInterpolationTypeScheme(SS, symmTensor)                             \
makeSurfaceInterpolationTypeScheme(SS, symmTensor4thOrder)                     \
makeSurfaceInterpolationTypeScheme(SS, diagTensor)                             \
makeSurfaceInterpolationTypeScheme(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <surfaceInterpolationScheme.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_surfaceInterpolationScheme_Header
