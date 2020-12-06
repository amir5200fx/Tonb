#pragma once
#ifndef _dummyAgglomeration_Header
#define _dummyAgglomeration_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2019 OpenFOAM Foundation
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
	tnbLib::dummyAgglomeration

Description
	Agglomerate without combining cells. Used for testing.

SourceFiles
	dummyAgglomeration.C

\*---------------------------------------------------------------------------*/

#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class dummyAgglomeration Declaration
	\*---------------------------------------------------------------------------*/

	class dummyAgglomeration
		:
		public GAMGAgglomeration
	{
		// Private Data

			//- Preset number of levels
		label nLevels_;


	public:

		//- Runtime type information
		//TypeName("dummy");
		static const char* typeName_() { return "dummy"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct given mesh and controls
		FoamBase_EXPORT dummyAgglomeration
		(
			const lduMesh& mesh,
			const dictionary& controlDict
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT dummyAgglomeration(const dummyAgglomeration&) = delete;



		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const dummyAgglomeration&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dummyAgglomeration_Header
