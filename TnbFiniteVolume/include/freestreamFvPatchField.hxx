#pragma once
#ifndef _freestreamFvPatchField_Header
#define _freestreamFvPatchField_Header

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
	tnbLib::freestreamFvPatchField

Description
	tnbLib::freestreamFvPatchField

SourceFiles
	freestreamFvPatchField.C

\*---------------------------------------------------------------------------*/

#include <inletOutletFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class freestreamFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class freestreamFvPatchField
		:
		public inletOutletFvPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName("freestream");


		// Constructors

			//- Construct from patch and internal field
		freestreamFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		freestreamFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given freestreamFvPatchField onto a new patch
		freestreamFvPatchField
		(
			const freestreamFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		freestreamFvPatchField
		(
			const freestreamFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new freestreamFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		freestreamFvPatchField
		(
			const freestreamFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type> > clone
		(
			const DimensionedField<Type, volMesh>& iF
		) const
		{
			return tmp<fvPatchField<Type> >
				(
					new freestreamFvPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Return defining fields

		const Field<Type>& freestreamValue() const
		{
			return this->refValue();
		}

		Field<Type>& freestreamValue()
		{
			return this->refValue();
		}


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <freestreamFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_freestreamFvPatchField_Header
