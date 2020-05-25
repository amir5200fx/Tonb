#pragma once
#ifndef _coupledFvsPatchField_Header
#define _coupledFvsPatchField_Header

#include <fvsPatchField.hxx>
#include <coupledFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class coupledFvsPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class coupledFvsPatchField
		:
		public fvsPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName(coupledFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct from patch and internal field and patch field
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const Field<Type>&
		);

		//- Construct from patch, internal field and dictionary
		coupledFvsPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const dictionary&,
			const bool valueRequired = false
		);

		//- Construct by mapping the given coupledFvsPatchField onto a new patch
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, surfaceMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type> > clone() const = 0;

		//- Construct as copy setting internal field reference
		coupledFvsPatchField
		(
			const coupledFvsPatchField<Type>&,
			const DimensionedField<Type, surfaceMesh>&
		);

		//- Construct and return a clone
		virtual tmp<fvsPatchField<Type> > clone
		(
			const DimensionedField<Type, surfaceMesh>&
		) const = 0;


		// Member functions

			// Access

				//- Return true if this patch field is derived from
				//  coupledFvsPatchField<Type>.
		virtual bool coupled() const
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
#   include <coupledFvsPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_coupledFvsPatchField_Header
