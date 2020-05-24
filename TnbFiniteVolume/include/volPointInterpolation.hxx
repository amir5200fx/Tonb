#pragma once
#ifndef _volPointInterpolation_Header
#define _volPointInterpolation_Header

#include <MeshObject.hxx>
#include <pointPatchInterpolation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;
	class pointMesh;

	/*---------------------------------------------------------------------------*\
						   Class volPointInterpolation Declaration
	\*---------------------------------------------------------------------------*/

	class volPointInterpolation
		:
		public MeshObject<fvMesh, volPointInterpolation>
	{
		// Private data

			//- Boundary interpolation engine
		pointPatchInterpolation boundaryInterpolator_;

		//- Interpolation scheme weighting factor array
		//  Updated for MeshObject.  HJ, 30/Aug/2010
		mutable scalarListList pointWeights_;


		// Private member functions

			//- Construct point weighting factors
		void makeWeights() const;

		//- Disallow default bitwise copy construct
		volPointInterpolation(const volPointInterpolation&);

		//- Disallow default bitwise assignment
		void operator=(const volPointInterpolation&);


	public:

		// Declare name of the class and its debug switch
		TypeName("volPointInterpolation");


		// Constructors

			//- Constructor given fvMesh.  pointMesh will be created or
			//  looked up from objectRegistry
		explicit volPointInterpolation(const fvMesh&);


		// Destructor

		~volPointInterpolation();


		// Member functions

			// Access

		const fvMesh& mesh() const
		{
			return boundaryInterpolator_.mesh();
		}


		// Edit

			//- Correct weighting factors for moving mesh.
			//  Updated for MeshObject.  HJ, 30/Aug/2010
		virtual bool movePoints() const;

		//- Update mesh topology using the morph engine
		//  Updated for MeshObject.  HJ, 30/Aug/2010
		virtual bool updateMesh(const mapPolyMesh&) const;


		// Interpolation functions

			//- Interpolate internal field from volField to pointField
			//  using inverse distance weighting
		template<class Type>
		void interpolateInternalField
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			GeometricField<Type, pointPatchField, pointMesh>&
		) const;

		//- Interpolate from volField to pointField
		//  using inverse distance weighting
		template<class Type>
		void interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			GeometricField<Type, pointPatchField, pointMesh>&
		) const;

		//- Interpolate volField using inverse distance weighting
		//  returning pointField with the same patchField types
		template<class Type>
		tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const wordList& patchFieldTypes
		) const;

		//- Interpolate tmp<volField> using inverse distance weighting
		//  returning pointField with the same patchField types
		template<class Type>
		tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const wordList& patchFieldTypes
		) const;

		//- Interpolate volField using inverse distance weighting
		//  returning pointField
		template<class Type>
		tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		) const;

		//- Interpolate tmp<volField> using inverse distance weighting
		//  returning pointField
		template<class Type>
		tmp<GeometricField<Type, pointPatchField, pointMesh> > interpolate
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <volPointInterpolate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_volPointInterpolation_Header
