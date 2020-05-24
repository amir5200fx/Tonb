#pragma once
#ifndef _fvcLaplacian_Header
#define _fvcLaplacian_Header

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
	tnbLib::fvc

Description
	Calculate the laplacian of the given field.

SourceFiles
	fvcLaplacian.C

\*---------------------------------------------------------------------------*/

#include <tmp.hxx>
#include <volFieldsFwd.hxx>
#include <surfaceFieldsFwd.hxx>
#include <dimensionedTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Namespace fvc functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace fvc
	{
		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const dimensioned<GType>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const dimensioned<GType>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const dimensioned<GType>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh> >&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh> >&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh> >&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvPatchField, volMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvPatchField, volMesh> >&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);


		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh> >&,
			const GeometricField<Type, fvPatchField, volMesh>&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh> >&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
			const word&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh> >&,
			const GeometricField<Type, fvPatchField, volMesh>&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const GeometricField<GType, fvsPatchField, surfaceMesh>&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);

		template<class Type, class GType>
		tmp<GeometricField<Type, fvPatchField, volMesh> > laplacian
		(
			const tmp<GeometricField<GType, fvsPatchField, surfaceMesh> >&,
			const tmp<GeometricField<Type, fvPatchField, volMesh> >&
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <fvcLaplacian.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvcLaplacian_Header
