#pragma once
#ifndef _steadyStateDdtScheme_Header
#define _steadyStateDdtScheme_Header

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
	tnbLib::fv::steadyStateDdtScheme

Description
	SteadyState implicit/explicit ddt which returns 0.

SourceFiles
	steadyStateDdtScheme.C

\*---------------------------------------------------------------------------*/

#include <ddtScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		/*---------------------------------------------------------------------------*\
							   Class steadyStateDdtScheme Declaration
		\*---------------------------------------------------------------------------*/

		template<class Type>
		class steadyStateDdtScheme
			:
			public fv::ddtScheme<Type>
		{
			// Private Member Functions

				//- Disallow default bitwise copy construct
			steadyStateDdtScheme(const steadyStateDdtScheme&);

			//- Disallow default bitwise assignment
			void operator=(const steadyStateDdtScheme&);


		public:

			//- Runtime type information
			TypeName("steadyState");


			// Constructors

				//- Construct from mesh
			steadyStateDdtScheme(const fvMesh& mesh)
				:
				ddtScheme<Type>(mesh)
			{}

			//- Construct from mesh and Istream
			steadyStateDdtScheme(const fvMesh& mesh, Istream& is)
				:
				ddtScheme<Type>(mesh, is)
			{}


			// Member Functions

				//- Return mesh reference
			const fvMesh& mesh() const
			{
				return fv::ddtScheme<Type>::mesh();
			}

			tmp<GeometricField<Type, fvPatchField, volMesh> > fvcDdt
			(
				const dimensioned<Type>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh> > fvcDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh> > fvcDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<GeometricField<Type, fvPatchField, volMesh> > fvcDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type> > fvmDdt
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type> > fvmDdt
			(
				const dimensionedScalar&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			tmp<fvMatrix<Type> > fvmDdt
			(
				const volScalarField&,
				const GeometricField<Type, fvPatchField, volMesh>&
			);

			typedef typename ddtScheme<Type>::fluxFieldType fluxFieldType;

			tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			);

			tmp<fluxFieldType> fvcDdtPhiCorr
			(
				const volScalarField& rA,
				const volScalarField& rho,
				const GeometricField<Type, fvPatchField, volMesh>& U,
				const fluxFieldType& phi
			);

			tmp<surfaceScalarField> meshPhi
			(
				const GeometricField<Type, fvPatchField, volMesh>&
			);
		};


		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtPhiCorr
		(
			const volScalarField& rA,
			const volScalarField& U,
			const surfaceScalarField& phi
		);


		template<>
		tmp<surfaceScalarField> steadyStateDdtScheme<scalar>::fvcDdtPhiCorr
		(
			const volScalarField& rA,
			const volScalarField& rho,
			const volScalarField& U,
			const surfaceScalarField& phi
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <steadyStateDdtScheme.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_steadyStateDdtScheme_Header
