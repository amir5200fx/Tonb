#pragma once
#ifndef _IODynList_Header
#define _IODynList_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | cfMesh: A library for mesh generation
   \\    /   O peration     |
	\\  /    A nd           | Author: Franjo Juretic (franjo.juretic@c-fields.com)
	 \\/     M anipulation  | Copyright (C) Creative Fields, Ltd.
-------------------------------------------------------------------------------
License
	This file is part of cfMesh.

	cfMesh is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation; either version 3 of the License, or (at your
	option) any later version.

	cfMesh is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with cfMesh.  If not, see <http://www.gnu.org/licenses/>.

Class
	IODynList

Description
	An IODynList of a given type is a DynList of that type which supports
	automated input and output.

SourceFiles
	IODynList.C

\*---------------------------------------------------------------------------*/

#include <DynList.hxx>
#include <regIOobject.hxx>
#include <label.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class IODynList Declaration
	\*---------------------------------------------------------------------------*/

	template<class T, label staticSize>
	class IODynList
		: public regIOobject
		, public DynList<T, staticSize>
	{

	public:

		//- Runtime type information
		TypeName("DynList");


		// Constructors

			//- Construct from IOobject
		IODynList(const IOobject&);

		//- Construct from IOobject and size of IODynList
		IODynList(const IOobject&, const label);

		//- Construct from IOobject and a List
		IODynList(const IOobject&, const DynList<T, staticSize>&);


		// Member functions

		bool writeData(Ostream&) const;


		// Member operators

		void operator=(const IODynList<T, staticSize>&);

		void operator=(const DynList<T, staticSize>&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <IODynList.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_IODynList_Header
