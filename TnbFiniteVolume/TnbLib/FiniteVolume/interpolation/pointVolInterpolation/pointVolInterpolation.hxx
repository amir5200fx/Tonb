#pragma once
#ifndef _pointVolInterpolation_Header
#define _pointVolInterpolation_Header

#include <primitiveFieldsFwd.hxx>
#include <primitivePatchInterpolation.hxx>
#include <volFieldsFwd.hxx>
#include <pointFieldsFwd.hxx>
#include <scalarList.hxx>
#include <tmp.hxx>
#include <className.hxx>
#include <FieldFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;
	class pointMesh;

	/*---------------------------------------------------------------------------*\
						  Class pointVolInterpolation Declaration
	\*---------------------------------------------------------------------------*/

	class pointVolInterpolation
	{
		// Private data

		const pointMesh& pointMesh_;
		const fvMesh& fvMesh_;

		//- Interpolation scheme weighting factor array.
		mutable FieldField<Field, scalar>* volWeightsPtr_;

		//- Primitive patch interpolators
		mutable PtrList<primitivePatchInterpolation>* patchInterpolatorsPtr_;


		// Private member functions

			//- Return patch interpolators
		const PtrList<primitivePatchInterpolation>& patchInterpolators() const;

		//- Construct point weighting factors
		void makeWeights() const;

		//- Clear addressing
		void clearAddressing() const;

		//- Clear geometry
		void clearGeom() const;


	protected:

		const pointMesh& pMesh() const
		{
			return pointMesh_;
		}

		const fvMesh& vMesh() const
		{
			return fvMesh_;
		}


	public:

		// Declare name of the class and it's debug switch
		ClassName("pointVolInterpolation");


		// Constructors

			//- Constructor given pointMesh and fvMesh.
		pointVolInterpolation(const pointMesh&, const fvMesh&);


		// Destructor

		~pointVolInterpolation();


		// Member functions

			// Access

				//- Return reference to weights arrays.
				//  This also constructs the weighting factors if neccessary.
		const FieldField<Field, scalar>& volWeights() const;


		// Edit

			//- Update mesh topology using the morph engine
		void updateTopology();

		//- Correct weighting factors for moving mesh.
		bool movePoints();


		// Interpolation functions

			//- Interpolate from pointField to volField
			//  using inverse distance weighting
		template<class Type>
		void interpolate
		(
			const GeometricField<Type, pointPatchField, pointMesh>&,
			GeometricField<Type, fvPatchField, volMesh>&
		) const;

		//- Interpolate pointField returning volField
		//  using inverse distance weighting
		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > interpolate
		(
			const GeometricField<Type, pointPatchField, pointMesh>&
		) const;

		//- Interpolate tmp<pointField> returning volField
		//  using inverse distance weighting
		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > interpolate
		(
			const tmp<GeometricField<Type, pointPatchField, pointMesh> >&
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <pointVolInterpolate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointVolInterpolation_Header
