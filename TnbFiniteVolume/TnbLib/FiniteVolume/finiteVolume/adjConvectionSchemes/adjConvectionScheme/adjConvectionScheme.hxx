#pragma once
#ifndef _adjConvectionScheme_Header
#define _adjConvectionScheme_Header

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <typeInfo.hxx>
#include <runTimeSelectionTables.hxx>
#include <multivariateSurfaceInterpolationScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type>
	class fvMatrix;

	class fvMesh;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class adjConvectionScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class adjConvectionScheme
			:
			public refCount
		{
			// Private data

			const fvMesh& mesh_;


		public:

			//- Runtime type information
			virtual const word& type() const = 0;


			// Declare run-time constructor selection tables

			declareRunTimeSelectionTable
			(
				tmp,
				adjConvectionScheme,
				Istream,
				(
					const fvMesh& mesh,
					const volVectorField& Up,
					Istream& schemeData
					),
					(mesh, Up, schemeData)
			);


			// Constructors

				//- Copy construct
			adjConvectionScheme(const adjConvectionScheme&);

			//- Construct from mesh, flux and Istream
			adjConvectionScheme
			(
				const fvMesh& mesh,
				const volVectorField&
			)
				:
				mesh_(mesh)
			{}


			// Selectors

				//- Return a pointer to a new adjConvectionScheme created on freestore
			static tmp<adjConvectionScheme<Type> > New
			(
				const fvMesh& mesh,
				const volVectorField& Up,
				Istream& schemeData
			);


			// Destructor

			virtual ~adjConvectionScheme();


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return mesh_;
			}

			virtual tmp<fvMatrix<Type> > fvmAdjDiv
			(
				const volVectorField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;

			virtual tmp<GeometricField<Type, fvPatchField, volMesh> > fvcAdjDiv
			(
				const volVectorField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			) const = 0;


			// Member operators

			void operator=(const adjConvectionScheme<Type>&);
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makeFvAdjConvectionTypeScheme(SS, Type)                               \
                                                                              \
defineNamedTemplateTypeNameAndDebug(SS<Type>, 0);                             \
                                                                              \
adjConvectionScheme<Type>::addIstreamConstructorToTable<SS<Type> >            \
    add##SS##Type##IstreamConstructorToTable_;

#define makeFvAdjConvectionScheme(SS)                                         \
                                                                              \
makeFvAdjConvectionTypeScheme(SS, vector)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "adjConvectionScheme.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_adjConvectionScheme_Header
