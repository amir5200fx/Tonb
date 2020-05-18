#pragma once
#ifndef _fvmAdjDiv_Header
#define _fvmAdjDiv_Header

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

InNamespace
	tnbLib::fvm

Description
	Calculate the matrix for the adjDivergence of the given field and flux.

SourceFiles
	fvmAdjDiv.C

\*---------------------------------------------------------------------------*/

#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <surfaceInterpolationScheme.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvm functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvm
	{
		template<class Type>
		tmp<fvMatrix<Type> > adjDiv
		(
			const volVectorField&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);

		template<class Type>
		tmp<fvMatrix<Type> > adjDiv
		(
			const tmp<volVectorField>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);


		template<class Type>
		tmp<fvMatrix<Type> > adjDiv
		(
			const volVectorField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type> > adjDiv
		(
			const tmp<volVectorField>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <fvmAdjDiv.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvmAdjDiv_Header

