#pragma once
#ifndef _pureMixture_Header
#define _pureMixture_Header

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
	tnbLib::pureMixture

Description
	tnbLib::pureMixture

SourceFiles
	pureMixture.C

\*---------------------------------------------------------------------------*/

#include <basicMixture.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class pureMixture Declaration
	\*---------------------------------------------------------------------------*/

	template<class ThermoType>
	class pureMixture
		:
		public basicMixture
	{
		// Private data

		ThermoType mixture_;

		//- Construct as copy (not implemented)
		pureMixture(const pureMixture<ThermoType>&);


	public:

		//- The type of thermodynamics this mixture is instantiated for
		typedef ThermoType thermoType;


		//- Runtime type information
		TypeName("pureMixture");


		// Constructors

			//- Construct from dictionary, mesh and object registry
		pureMixture(const dictionary&, const fvMesh&, const objectRegistry&);


		// Destructor

		~pureMixture();


		// Member functions

		const ThermoType& cellMixture(const label) const
		{
			return mixture_;
		}

		const ThermoType& patchFaceMixture
		(
			const label,
			const label
		) const
		{
			return mixture_;
		}

		//- Read dictionary
		void read(const dictionary&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <pureMixture.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_pureMixture_Header
