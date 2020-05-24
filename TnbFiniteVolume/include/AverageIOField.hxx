#pragma once
#ifndef _AverageIOField_Header
#define _AverageIOField_Header

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
	tnbLib::AverageIOField

Description
	A primitive field + average with IO.

SourceFiles
	AverageIOField.C

\*---------------------------------------------------------------------------*/

#include <regIOobject.hxx>
#include <Field.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class AverageIOField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class AverageIOField
		:
		public regIOobject,
		public Field<Type>
	{
		// Private data

			//- The average of the field
		Type average_;


	public:

		TypeName("AverageField");


		// Constructors

			//- Construct from IOobject
		AverageIOField
		(
			const IOobject&
		);

		//- Construct from IOobject and size (does not set values)
		AverageIOField
		(
			const IOobject&,
			const label size
		);

		//- Construct from components
		AverageIOField
		(
			const IOobject&,
			const Type& average,
			const Field<Type>&
		);


		// Member functions

		const Type& average() const
		{
			return average_;
		}

		Type& average()
		{
			return average_;
		}

		bool writeData(Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <AverageIOField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_AverageIOField_Header
