#pragma once
#ifndef _electromagneticConstants_Header
#define _electromagneticConstants_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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

Namespace
	tnbLib::constant::electromagnetic

Description
	Electromagnetic constants

\*---------------------------------------------------------------------------*/

#include <dimensionedScalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{
		namespace electromagnetic
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

				//- Group name for electromagnetic constants
			FoamBase_EXPORT extern const char* const group;

			//- Magnetic constant/permeability of free space: default SI units: [H/m]
			FoamBase_EXPORT extern const dimensionedScalar mu0;

			//- Electric constant: default SI units: [F/m]
			FoamBase_EXPORT extern const dimensionedScalar epsilon0;

			//- Characteristic impedance of a vacuum: default SI units: [ohm]
			FoamBase_EXPORT extern const dimensionedScalar Z0;

			//- Coulomb constant: default SI units: [N.m2/C2]
			FoamBase_EXPORT extern const dimensionedScalar kappa;

			//- Conductance quantum: default SI units: [S]
			FoamBase_EXPORT extern const dimensionedScalar G0;

			//- Josephson constant: default SI units: [Hz/V]
			FoamBase_EXPORT extern const dimensionedScalar KJ;

			//- Magnetic flux quantum: default SI units: [Wb]
			FoamBase_EXPORT extern const dimensionedScalar phi0;

			//- Von Klitzing constant: default SI units: [ohm]
			FoamBase_EXPORT extern const dimensionedScalar RK;


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace electromagnetic
	} // End namespace constant
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_electromagneticConstants_Header
