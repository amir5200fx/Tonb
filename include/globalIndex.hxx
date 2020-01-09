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
	Foam::globalIndex

Description
	Calculates a unique integer (label so might not have enough room - 2G max)
	for processor + local index. E.g.

	globalIndex globalFaces(mesh.nFaces());
	label globalFaceI = globalFaces.toGlobal(faceI);


SourceFiles
	globalIndex.C

\*---------------------------------------------------------------------------*/
#ifndef _globalIndex_Header
#define _globalIndex_Header

#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class globalIndex;

	Istream& operator>>(Istream& is, globalIndex& gi);
	Ostream& operator<<(Ostream& os, const globalIndex& gi);


	/*---------------------------------------------------------------------------*\
							   Class globalIndex Declaration
	\*---------------------------------------------------------------------------*/

	class globalIndex
	{
		// Private data

			//- Start off procI+1. (so like CompactListList)
		labelList offsets_;


	public:

		// Constructors

			//- Construct from local max size
		globalIndex(const label localSize);

		//- Construct from Istream
		globalIndex(Istream& is);


		// Member Functions

		////- Start of procI+1 data
		//const labelList& offsets() const;


		// Queries relating to my processor

		//- my local size
		label localSize() const;

		//- From local to global
		label toGlobal(const label i) const;

		//- Is on local processor
		bool isLocal(const label i) const;

		//- From global to local on current processor.
		//  FatalError if not on local processor.
		label toLocal(const label i) const;


		// Global queries

			//- Global sum of localSizes
		label size() const;

		//- Size of procI data
		label localSize(const label procI) const;

		//- From local to global on procI
		label toGlobal(const label procI, const label i) const;

		//- Is on processor procI
		bool isLocal(const label procI, const label i) const;

		//- From global to local on procI
		label toLocal(const label procI, const label i) const;

		//- Which processor does global come from? Binary search.
		label whichProcID(const label i) const;

		//- Start of procI data
		label offset(const label procI) const;



		// IOstream Operators

		friend Istream& operator>>(Istream& is, globalIndex& gi);
		friend Ostream& operator<<(Ostream& os, const globalIndex& gi);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <globalIndexI.hxx>

#endif // !_globalIndex_Header
