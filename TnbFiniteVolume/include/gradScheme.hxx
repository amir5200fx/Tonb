#pragma once
#ifndef _gradScheme_Header
#define _gradScheme_Header

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <BlockLduSystem.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class fvMesh;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class gradScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class gradScheme
			:
			public refCount
		{
		public:

			// Public typedefs

			typedef Field<Type> FieldType;
			typedef GeometricField<Type, fvPatchField, volMesh> GeoFieldType;
			typedef typename GeoFieldType::GeometricBoundaryField GeoBoundaryFieldType;

			typedef Field<typename outerProduct<vector, Type>::type> GradFieldType;
			typedef GeometricField
				<
				typename outerProduct<vector, Type>::type,
				fvPatchField,
				volMesh
				> GeoGradFieldType;
			typedef BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
				GradMatrixType;


			// Private data

			const fvMesh& mesh_;


			// Private Member Functions

				//- Disallow copy construct
			gradScheme(const gradScheme&);

			//- Disallow default bitwise assignment
			void operator=(const gradScheme&);


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			declareRunTimeSelectionTable
			(
				tmp,
				gradScheme,
				Istream,
				(const fvMesh& mesh, Istream& schemeData),
				(mesh, schemeData)
			);


			// Constructors

				//- Construct from mesh
			gradScheme(const fvMesh& mesh)
				:
				mesh_(mesh)
			{}


			// Selectors

				//- Return a pointer to a new gradScheme created on freestore
			static tmp<gradScheme<Type> > New
			(
				const fvMesh& mesh,
				Istream& schemeData
			);


			// Destructor

			virtual ~gradScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			//  Moved from gaussGrad into base class.  HJ, 14/Jun/2013
			//- Correct the boundary values of the gradient using the patchField
			//  snGrad functions
			static void correctBoundaryConditions
			(
				const GeoFieldType&,
				GeoGradFieldType&
			);


			// Gradient functions

				//- Calculate and return the grad of the given field
				//  which may have been cached
			tmp<GeoGradFieldType> grad
			(
				const GeoFieldType&,
				const word& name
			) const;

			//- Calculate and return the grad of the given field
			//  with the default name which may have been cached
			tmp<GeoGradFieldType> grad
			(
				const GeoFieldType&
			) const;

			//- Calculate and return the grad of the given field
			//  with the default name which may have been cached
			tmp<GeoGradFieldType> grad
			(
				const tmp<GeoFieldType>&
			) const;


			// Virtual function interface

				//- Calculate and return the grad of the given field.
				//  Used by grad either to recalculate the cached gradient when
				//  out of date with respect to the field or when it is not cached.
			virtual tmp<GeoGradFieldType> calcGrad
			(
				const GeoFieldType&,
				const word& name
			) const = 0;

			//- Return the BlockLduSystem corresponding to the implicit grad
			// discretization. For block coupled systems.
			virtual tmp<GradMatrixType> fvmGrad
			(
				const GeoFieldType&
			) const;
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvGradTypeScheme(SS, Type)                                        \
                                                                              \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                             \
                                                                              \
gradScheme<Type>::addIstreamConstructorToTable<SS<Type> >                     \
    add##SS##Type##IstreamConstructorToTable_;


#define makeFvGradScheme(SS)                                                  \
                                                                              \
makeFvGradTypeScheme(SS, scalar)                                              \
makeFvGradTypeScheme(SS, vector)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "gradScheme.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gradScheme_Header
