#pragma once
#ifndef _fvmD2dt2_Header
#define _fvmD2dt2_Header

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
	Calculate the matrix for the second-order temporal derivative.

SourceFiles
	fvmD2dt2.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <fvMatrices.hxx>
#include <dimensionedTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvm functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvm
	{
		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const dimensionedScalar&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);

		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);

		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);

		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const dimensionedScalar&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word& name
		);

		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<fvMatrix<Type> > d2dt2
		(
			const volScalarField&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <fvmD2dt2.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvmD2dt2_Header
