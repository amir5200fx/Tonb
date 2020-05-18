#pragma once
#ifndef _gaussGrad_Header
#define _gaussGrad_Header

#include <gradScheme.hxx>
#include <surfaceInterpolationScheme.hxx>
#include <linear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
								   Class gaussGrad Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class gaussGrad
			:
			public fv::gradScheme<Type>
		{
			// Private data

			tmp<surfaceInterpolationScheme<Type> > tinterpScheme_;


			// Private Member Functions

				//- Disallow default bitwise copy construct
			gaussGrad(const gaussGrad&);

			//- Disallow default bitwise assignment
			void operator=(const gaussGrad&);


		public:

			//- Runtime type information
			TypeName("Gauss");


			// Constructors

				//- Construct from mesh
			gaussGrad(const fvMesh& mesh)
				:
				gradScheme<Type>(mesh),
				tinterpScheme_(new linear<Type>(mesh))
			{}

			//- Construct from mesh and Istream
			gaussGrad(const fvMesh& mesh, Istream& is)
				:
				gradScheme<Type>(mesh),
				tinterpScheme_(NULL)
			{
				if (is.eof())
				{
					tinterpScheme_ =
						tmp<surfaceInterpolationScheme<Type> >
						(
							new linear<Type>(mesh)
							);
				}
				else
				{
					tinterpScheme_ =
						tmp<surfaceInterpolationScheme<Type> >
						(
							surfaceInterpolationScheme<Type>::New(mesh, is)
							);
				}
			}


			// Member Functions

				//- Return the gradient of the given field
				//  calculated using Gauss' theorem on the given surface field
			static
				tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> gradf
				(
					const GeometricField<Type, fvsPatchField, surfaceMesh>&,
					const word& name
				);

			//- Return the gradient of the given field calculated
			//  using Gauss' theorem on the interpolated field
			virtual tmp
				<
				GeometricField
				<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
				> calcGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>& vsf,
					const word& name
				) const;

			//- Return the BlockLduSystem corresponding to the implicit grad
			// discretization. For block coupled systems.
			tmp
				<
				BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
				> fvmGrad
				(
					const GeometricField<Type, fvPatchField, volMesh>&
				) const;

			// Correct boundary conditions moved to base class
			// HJ, 14/Jun/2013
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <scalarGaussGrad.hxx>

#ifdef NoRepository
#   include <gaussGrad.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_gaussGrad_Header
