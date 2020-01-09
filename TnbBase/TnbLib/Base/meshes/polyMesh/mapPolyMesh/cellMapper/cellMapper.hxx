#pragma once
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
	Foam::cellMapper

Description
	This object provides mapping and fill-in information for cell data
	between the two meshes after the topological change.  It is
	constructed from mapPolyMesh.

SourceFiles
	cellMapper.C

\*---------------------------------------------------------------------------*/
#ifndef _cellMapper_Header
#define _cellMapper_Header

#include <morphFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class polyMesh;
	class mapPolyMesh;

	/*---------------------------------------------------------------------------*\
							   Class cellMapper Declaration
	\*---------------------------------------------------------------------------*/

	class cellMapper
		:
		public morphFieldMapper
	{
		// Private data

			//- Reference to polyMesh
		const polyMesh& mesh_;

		//- Reference to mapPolyMesh
		const mapPolyMesh& mpm_;

		//- Are there any inserted (unmapped) cells
		bool insertedCells_;

		//- Is the mapping direct
		bool direct_;


		// Demand-driven private data

			//- Direct addressing (only one form of addressing is used)
		mutable labelList* directAddrPtr_;

		//- Interpolated addressing (only one form of addressing is used)
		mutable labelListList* interpolationAddrPtr_;

		//- Interpolation weights
		mutable scalarListList* weightsPtr_;

		//- Inserted cells
		mutable labelList* insertedCellLabelsPtr_;


		// Private Member Functions

			//- Disallow default bitwise copy construct
		cellMapper(const cellMapper&);

		//- Disallow default bitwise assignment
		void operator=(const cellMapper&);


		//- Calculate addressing for mapping with inserted cells
		void calcAddressing() const;

		//- Clear out local storage
		void clearOut();


	public:

		// Static data members

		// Constructors

			//- Construct from mapPolyMesh
		cellMapper(const mapPolyMesh& mpm);


		// Destructor

		virtual ~cellMapper();


		// Member Functions

			//- Return size
		virtual label size() const;

		//- Return size before mapping
		virtual label sizeBeforeMapping() const;

		//- Is the mapping direct
		virtual bool direct() const
		{
			return direct_;
		}

		//- Return direct addressing
		virtual const unallocLabelList& directAddressing() const;

		//- Return interpolated addressing
		virtual const labelListList& addressing() const;

		//- Return interpolaion weights
		virtual const scalarListList& weights() const;

		//- Are there any inserted cells
		bool insertedObjects() const
		{
			return insertedCells_;
		}

		//- Return list of inserted cells
		const labelList& insertedObjectLabels() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellMapper_Header
