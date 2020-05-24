#pragma once
#ifndef _linearUpwindV_Header
#define _linearUpwindV_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
	\\  /    A nd           | Web:         http://www.foam-extend.org
	 \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
	This file is part of foam-extend.

	foam-extend is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	foam-extend is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::linearUpwindV

Description
	linearUpwindV interpolation scheme class derived from upwind and returns
	upwind weighting factors but also applies an explicit correction.

SourceFiles
	linearUpwindV.C

\*---------------------------------------------------------------------------*/

#include <upwind.hxx>
#include <gaussGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class linearUpwindV Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class linearUpwindV
		:
		public upwind<Type>
	{
		// Private Data

			//- Name of gradient scheme
		word gradSchemeName_;

		//- Gradient scheme
		tmp<fv::gradScheme<Type> > gradScheme_;


		// Private Member Functions

			//- Disallow default bitwise copy construct
		linearUpwindV(const linearUpwindV&);

		//- Disallow default bitwise assignment
		void operator=(const linearUpwindV&);


	public:

		//- Runtime type information
		TypeName("linearUpwindV");


		// Constructors

			//- Construct from faceFlux
		linearUpwindV
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux
		)
			:
			upwind<Type>(mesh, faceFlux),
			gradSchemeName_("grad"),
			gradScheme_
			(
				new fv::gaussGrad<Type>(mesh)
			)
		{}

		//- Construct from Istream.
		//  The name of the flux field is read from the Istream and looked-up
		//  from the mesh objectRegistry
		linearUpwindV
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, schemeData),
			gradSchemeName_(schemeData),
			gradScheme_
			(
				fv::gradScheme<Type>::New
				(
					mesh,
					mesh.schemesDict().gradScheme(gradSchemeName_)
				)
			)
		{}

		//- Construct from faceFlux and Istream
		linearUpwindV
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
			:
			upwind<Type>(mesh, faceFlux, schemeData),
			gradSchemeName_(schemeData),
			gradScheme_
			(
				fv::gradScheme<Type>::New
				(
					mesh,
					mesh.schemesDict().gradScheme(gradSchemeName_)
				)
			)
		{}


		// Member Functions

			//- Return true if this scheme uses an explicit correction
		virtual bool corrected() const
		{
			return true;
		}

		//- Return the explicit correction to the face-interpolate
		virtual tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
			correction
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_linearUpwindV_Header
