#pragma once
#ifndef _CFCCellToFaceStencil_Header
#define _CFCCellToFaceStencil_Header

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
	tnbLib::CFCCellToFaceStencil

Description
	Combined corresponding cellToCellStencil of owner and neighbour.

SourceFiles
	CFCCellToFaceStencil.C

\*---------------------------------------------------------------------------*/

#include <cellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class CFCCellToFaceStencil Declaration
	\*---------------------------------------------------------------------------*/

	class CFCCellToFaceStencil
		:
		public cellToFaceStencil
	{
	public:

		// Constructors

			//- Construct from mesh
		explicit CFCCellToFaceStencil(const polyMesh& mesh);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_CFCCellToFaceStencil_Header
