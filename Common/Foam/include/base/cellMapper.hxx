#pragma once
#ifndef _cellMapper_Header
#define _cellMapper_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::cellMapper

Description
	This object provides mapping and fill-in information for cell data
	between the two meshes after the topological change.  It is
	constructed from mapPolyMesh.

SourceFiles
	cellMapper.C

\*---------------------------------------------------------------------------*/

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
		// Private Data

			//- Reference to polyMesh
		const polyMesh& mesh_;

		//- Reference to mapPolyMesh
		const mapPolyMesh& mpm_;

		//- Are there any inserted (unmapped) cells
		bool insertedCells_;

		//- Is the mapping direct
		bool direct_;


		// Demand-driven private data

			//- Direct addressing (only one for of addressing is used)
		mutable labelList* directAddrPtr_;

		//- Interpolated addressing (only one for of addressing is used)
		mutable labelListList* interpolationAddrPtr_;

		//- Interpolation weights
		mutable scalarListList* weightsPtr_;

		//- Inserted cells
		mutable labelList* insertedCellLabelsPtr_;


		// Private Member Functions

			//- Calculate addressing for mapping with inserted cells
		FoamBase_EXPORT void calcAddressing() const;

		//- Clear out local storage
		FoamBase_EXPORT void clearOut();


	public:

		// Static Data Members

		// Constructors

			//- Construct from mapPolyMesh
		FoamBase_EXPORT cellMapper(const mapPolyMesh& mpm);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT cellMapper(const cellMapper&) = delete;


		//- Destructor
		FoamBase_EXPORT virtual ~cellMapper();


		// Member Functions

			//- Return size before mapping
		FoamBase_EXPORT virtual label sizeBeforeMapping() const;

		//- Is the mapping direct
		virtual bool direct() const
		{
			return direct_;
		}

		virtual bool hasUnmapped() const
		{
			return insertedObjects();
		}

		//- Return direct addressing
		FoamBase_EXPORT virtual const labelUList& directAddressing() const;

		//- Return interpolated addressing
		FoamBase_EXPORT virtual const labelListList& addressing() const;

		//- Return interpolaion weights
		FoamBase_EXPORT virtual const scalarListList& weights() const;

		//- Are there any inserted cells
		virtual bool insertedObjects() const
		{
			return insertedCells_;
		}

		//- Return list of inserted cells
		FoamBase_EXPORT const virtual labelList& insertedObjectLabels() const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const cellMapper&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellMapper_Header
