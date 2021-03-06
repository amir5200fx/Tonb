#pragma once
#ifndef _processorCyclicGAMGInterfaceField_Header
#define _processorCyclicGAMGInterfaceField_Header

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
	tnbLib::processorCyclicGAMGInterfaceField

Description
	GAMG agglomerated processor interface field.

SourceFiles
	processorCyclicGAMGInterfaceField.C

\*---------------------------------------------------------------------------*/

#include <processorGAMGInterfaceField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
				   Class processorCyclicGAMGInterfaceField Declaration
	\*---------------------------------------------------------------------------*/

	class processorCyclicGAMGInterfaceField
		:
		public processorGAMGInterfaceField
	{
		// Private Member Functions

			//- Disallow default bitwise copy construction
		FoamBase_EXPORT processorCyclicGAMGInterfaceField
		(
			const processorCyclicGAMGInterfaceField&
		);

		//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const processorCyclicGAMGInterfaceField&) = delete;


	public:

		//- Runtime type information
		//TypeName("processorCyclic");
		static const char* typeName_() { return "processorCyclic"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from GAMG interface and fine level interface field
		FoamBase_EXPORT processorCyclicGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const lduInterfaceField& fineInterface
		);

		//- Construct from GAMG interface and fine level interface field
		FoamBase_EXPORT processorCyclicGAMGInterfaceField
		(
			const GAMGInterface& GAMGCp,
			const bool doTransform,
			const int rank
		);


		// Destructor

		FoamBase_EXPORT virtual ~processorCyclicGAMGInterfaceField();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorCyclicGAMGInterfaceField_Header
