#pragma once
#ifndef _calculatedFvPatchField_Header
#define _calculatedFvPatchField_Header

#include <fvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					  Class calculatedFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class calculatedFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName("calculated");


		// Constructors

			//- Construct from patch and internal field
		calculatedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		calculatedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&,
			const bool valueRequired = false
		);

		//- Construct by mapping given patchField<Type> onto a new patch
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new calculatedFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		calculatedFvPatchField
		(
			const calculatedFvPatchField<Type>&,
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
					new calculatedFvPatchField<Type>(*this, iF)
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


		// Evaluation functions

			//- Return the matrix diagonal coefficients corresponding to the
			//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type> > valueInternalCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the value of this patchField with given weights
		virtual tmp<Field<Type> > valueBoundaryCoeffs
		(
			const tmp<scalarField>&
		) const;

		//- Return the matrix diagonal coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		tmp<Field<Type> > gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		tmp<Field<Type> > gradientBoundaryCoeffs() const;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <calculatedFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calculatedFvPatchField_Header
