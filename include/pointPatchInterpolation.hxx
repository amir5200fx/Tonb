#pragma once
#ifndef _pointPatchInterpolation_Header
#define _pointPatchInterpolation_Header

#include <primitivePatchInterpolation.hxx>
#include <PtrList.hxx>
#include <volFieldsFwd.hxx>
#include <pointFieldsFwd.hxx>
#include <scalarList.hxx>
#include <className.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;
	class pointMesh;

	/*---------------------------------------------------------------------------*\
						   Class pointPatchInterpolation Declaration
	\*---------------------------------------------------------------------------*/

	class pointPatchInterpolation
	{
		// Private data

			//- Reference to volume mesh
		const fvMesh& fvMesh_;

		//- Primitive patch interpolators
		PtrList<primitivePatchInterpolation> patchInterpolators_;

		//- List of patch-patch edge points that require special treatement
		labelList patchPatchPoints_;

		//- Weights for patch-patch boundary points
		scalarListList patchPatchPointWeights_;

		labelList patchPatchPointConstraintPoints_;
		tensorField patchPatchPointConstraintTensors_;


		// Private member functions

			//- Construct addressing for patch-patch boundary points
		void makePatchPatchAddressing();

		//- Construct weights for patch-patch boundary points
		void makePatchPatchWeights();


		//- Disallow default bitwise copy construct
		pointPatchInterpolation(const pointPatchInterpolation&);

		//- Disallow default bitwise assignment
		void operator=(const pointPatchInterpolation&);


	public:

		// Declare name of the class and its debug switch
		ClassName("pointPatchInterpolation");


		// Constructors

			//- Constructor given fvMesh and pointMesh.
		pointPatchInterpolation(const fvMesh&);


		// Destructor

		~pointPatchInterpolation();


		// Member functions

			// Access

		const fvMesh& mesh() const
		{
			return fvMesh_;
		}


		// Edit

			//- Update mesh topology using the morph engine
		void updateMesh();

		//- Correct weighting factors for moving mesh.
		bool movePoints();


		// Interpolation functions

		template<class Type>
		void interpolate
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			GeometricField<Type, pointPatchField, pointMesh>&,
			bool overrideFixedValue
		) const;

		template<class Type>
		void applyCornerConstraints
		(
			GeometricField<Type, pointPatchField, pointMesh>& pf
		) const;
	};


	template<>
	void pointPatchInterpolation::applyCornerConstraints<scalar>
		(
			GeometricField<scalar, pointPatchField, pointMesh>& pf
			) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <pointPatchInterpolate.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pointPatchInterpolation_Header
