#pragma once
#ifndef _calculatedFvsPatchField_Header
#define _calculatedFvsPatchField_Header

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
	tnbLib::calculatedFvsPatchField

Description
	tnbLib::calculatedFvsPatchField

SourceFiles
	calculatedFvsPatchField.C

\*---------------------------------------------------------------------------*/

#include <fvsPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class calculatedFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class calculatedFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName("calculated");


		// Constructors

			//- Construct from patch and internal field
		calculatedFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch, internal field and dictionary
		calculatedFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		calculatedFvsPatchField
		(
			const calculatedFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		calculatedFvsPatchField
		(
			const calculatedFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type> > clone() const
		{
			return tmp<fvsPatchField<Type> >
				(
					new calculatedFvsPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		calculatedFvsPatchField
		(
			const calculatedFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvsPatchField<Type> > clone
		(
			const DimensionedField<Type, surfaceMesh>& iF
		) const
		{
			return tmp<fvsPatchField<Type> >
				(
					new calculatedFvsPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Access

				//- Return true if this patch field fixes a value.
				//  Needed to check if a level has to be specified while solving
				//  Poissons equations.
		virtual bool fixesValue() const
		{
			return true;
		}


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <calculatedFvsPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calculatedFvsPatchField_Header
