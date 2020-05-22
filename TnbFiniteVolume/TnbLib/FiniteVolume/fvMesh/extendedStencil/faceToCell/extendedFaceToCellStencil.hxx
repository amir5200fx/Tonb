#pragma once
#ifndef _extendedFaceToCellStencil_Header
#define _extendedFaceToCellStencil_Header

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
	tnbLib::extendedFaceToCellStencil

Description
	Note: transformations on coupled patches not supported. Problem is the
	positions of cells reachable through these patches.

SourceFiles
	extendedFaceToCellStencil.C
	extendedFaceToCellStencilTemplates.C

\*---------------------------------------------------------------------------*/

#include <objectRegistry.hxx>
#include <mapDistribute.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class globalIndex;

	/*---------------------------------------------------------------------------*\
							   Class extendedFaceToCellStencil Declaration
	\*---------------------------------------------------------------------------*/

	class extendedFaceToCellStencil
	{
	protected:

		// Protected data

		const polyMesh& mesh_;

	private:

		// Private Member Functions

			//- Disallow default bitwise copy construct
		extendedFaceToCellStencil(const extendedFaceToCellStencil&);

		//- Disallow default bitwise assignment
		void operator=(const extendedFaceToCellStencil&);


	public:

		// Constructors

			//- Construct from mesh
		explicit extendedFaceToCellStencil(const polyMesh&);


		// Member Functions

			//- Use map to get the data into stencil order
		template<class T>
		static void collectData
		(
			const mapDistribute& map,
			const labelListList& stencil,
			const GeometricField<T, fvsPatchField, surfaceMesh>& fld,
			List<List<T> >& stencilFld
		);

		//- Sum surface field contributions to create cell values
		template<class Type>
		static tmp<GeometricField<Type, fvPatchField, volMesh> > weightedSum
		(
			const mapDistribute& map,
			const labelListList& stencil,
			const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
			const List<List<scalar> >& stencilWeights
		);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <extendedFaceToCellStencilTemplates.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_extendedFaceToCellStencil_Header
