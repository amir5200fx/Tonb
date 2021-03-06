#pragma once
#ifndef _sigWriteNow_Header
#define _sigWriteNow_Header

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
	tnbLib::sigWriteNow

Description
	Signal handler for interrupt defined by OptimisationSwitches::writeNowSignal

	Write once and continue.

SourceFiles
	sigWriteNow.C

\*---------------------------------------------------------------------------*/

#include <includeModule.hxx>

#include <signal.h>

typedef	void(*__p_sig_fn_t)(int);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Time;

	/*---------------------------------------------------------------------------*\
							   Class sigWriteNow Declaration
	\*---------------------------------------------------------------------------*/

	class sigWriteNow
	{
		// Private Data

			//- Number of signal to use
		static FoamBase_EXPORT int signal_;

		//- Pointer to Time
		static FoamBase_EXPORT Time* runTimePtr_;

		//- Saved old signal trapping setting
		//static struct sigaction oldAction_;
		static FoamBase_EXPORT __p_sig_fn_t oldAction_;


		// Private Member Functions

		static FoamBase_EXPORT void sigHandler(int);


	public:

		friend class sigStopAtWriteNow;

		//- wip. Have setter have access to signal_
		friend class addwriteNowSignalToOpt;

		// Constructors

			//- Construct null
		FoamBase_EXPORT sigWriteNow();

		//- Construct from components
		FoamBase_EXPORT sigWriteNow(const bool verbose, Time& runTime);


		//- Destructor
		FoamBase_EXPORT ~sigWriteNow();


		// Member Functions

			//- (re)set signal catcher
		static FoamBase_EXPORT void set(const bool verbose);

		//- Is active?
		FoamBase_EXPORT bool active() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sigWriteNow_Header
