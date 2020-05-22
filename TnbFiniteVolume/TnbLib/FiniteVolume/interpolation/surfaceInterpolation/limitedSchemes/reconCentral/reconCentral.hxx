#pragma once
#ifndef _reconCentral_Header
#define _reconCentral_Header

#include <upwind.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class reconCentral Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class reconCentral
		:
		public upwind<Type>
	{
		// Private Data

		tmp<fv::gradScheme<Type> > gradScheme_;


		// Private Member Functions

			//- Disallow default bitwise copy construct
		reconCentral(const reconCentral&);

		//- Disallow default bitwise assignment
		void operator=(const reconCentral&);


	public:

		//- Runtime type information
		TypeName("reconCentral");


		// Constructors

			//- Construct from faceFlux
		reconCentral
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			upwind<Type>(mesh, faceFlux),
			gradScheme_
			(
				new fv::gaussGrad<Type>(mesh)
			)
		{}

		//- Construct from Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		reconCentral
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, schemeData),
			gradScheme_
			(
				fv::gradScheme<Type>::New
				(
					mesh,
					schemeData
				)
			)
		{}

		//- Construct from faceFlux and Istream
		reconCentral
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, faceFlux, schemeData),
			gradScheme_
			(
				fv::gradScheme<Type>::New
				(
					mesh,
					schemeData
				)
			)
		{}


		// Member Functions

			//- Return the face-interpolate of the given cell field
			//  with explicit correction
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			interpolate(const GeometricField<Type, fvPatchField, volMesh>&) const;

		//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return true;
		}

		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_reconCentral_Header
