#pragma once
#ifndef _fvBoundaryMeshMapper_Header
#define _fvBoundaryMeshMapper_Header

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
	tnbLib::fvBoundaryMeshMapper

Description
	tnbLib::fvBoundaryMeshMapper

\*---------------------------------------------------------------------------*/

#include <PtrList.hxx>
#include <fvPatchMapper.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class fvBoundaryMeshMapper Declaration
	\*---------------------------------------------------------------------------*/

	class fvBoundaryMeshMapper
		:
		public PtrList<fvPatchMapper>
	{
		// Private Member Functions

			//- Disallow default bitwise copy construct
		fvBoundaryMeshMapper(const fvBoundaryMeshMapper&);

		//- Disallow default bitwise assignment
		void operator=(const fvBoundaryMeshMapper&);


	public:

		// Constructors

			//- Construct from components
		fvBoundaryMeshMapper
		(
			const fvMesh& mesh,
			const faceMapper& faceMap
		)
			:
			PtrList<fvPatchMapper>(mesh.boundary().size())
		{
			const fvBoundaryMesh& patches = mesh.boundary();

			forAll(patches, patchI)
			{
				set
				(
					patchI,
					new fvPatchMapper
					(
						patches[patchI],
						faceMap
					)
				);
			}
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvBoundaryMeshMapper_Header
