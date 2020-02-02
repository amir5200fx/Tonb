#pragma once
#ifndef _interpolation_Header
#define _interpolation_Header

#include <faceList.hxx>
#include <volFieldsFwd.hxx>
#include <pointFields.hxx>
#include <typeInfo.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class polyMesh;

	/*---------------------------------------------------------------------------*\
						   Class interpolation Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class interpolation
	{

	protected:

		// Protected data

		const GeometricField<Type, fvPatchField, volMesh>& psi_;

		const polyMesh& pMesh_;
		const vectorField& pMeshPoints_;
		const faceList& pMeshFaces_;
		const vectorField& pMeshFaceCentres_;
		const vectorField& pMeshFaceAreas_;


	public:

		//- Runtime type information
		virtual const word& type() const = 0;


		// Declare run-time constructor selection table

		declareRunTimeSelectionTable
		(
			autoPtr,
			interpolation,
			dictionary,
			(
				const GeometricField<Type, fvPatchField, volMesh>& psi
				),
				(psi)
		);


		// Selectors

			//- Return a reference to the specified interpolation scheme
		static autoPtr<interpolation<Type> > New
		(
			const word& interpolationType,
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);

		//- Return a reference to the selected interpolation scheme
		static autoPtr<interpolation<Type> > New
		(
			const dictionary& interpolationSchemes,
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Constructors

			//- Construct from components
		interpolation
		(
			const GeometricField<Type, fvPatchField, volMesh>& psi
		);


		// Destructor

		virtual ~interpolation()
		{}


		// Member Functions

			//- Return the field to be interpolated
		const GeometricField<Type, fvPatchField, volMesh>& psi() const
		{
			return psi_;
		}

		//- Interpolate field to the given point in the given cell
		virtual Type interpolate
		(
			const vector& position,
			const label nCell,
			const label facei = -1
		) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeInterpolationType(SS, Type)                                       \
                                                                              \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                             \
                                                                              \
interpolation<Type>::adddictionaryConstructorToTable<SS<Type> >               \
    add##SS##Type##ConstructorToTable_;


#define makeInterpolation(SS)                                                 \
                                                                              \
makeInterpolationType(SS, scalar)                                             \
makeInterpolationType(SS, vector)                                             \
makeInterpolationType(SS, sphericalTensor)                                    \
makeInterpolationType(SS, symmTensor)                                         \
makeInterpolationType(SS, symmTensor4thOrder)                                 \
makeInterpolationType(SS, diagTensor)                                         \
makeInterpolationType(SS, tensor)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <interpolation.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_interpolation_Header
