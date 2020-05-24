#pragma once
#ifndef _fixedGradientFvPatchField_Header
#define _fixedGradientFvPatchField_Header

#include <fvPatchField.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class fixedGradientFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class fixedGradientFvPatchField
		:
		public fvPatchField<Type>
	{
		// Private data

		Field<Type> gradient_;


	public:

		//- Runtime type information
		TypeName("fixedGradient");


		// Constructors

			//- Construct from patch and internal field
		fixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		fixedGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given fixedGradientFvPatchField
		//  onto a new patch
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new fixedGradientFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		fixedGradientFvPatchField
		(
			const fixedGradientFvPatchField<Type>&,
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
					new fixedGradientFvPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Return defining fields

				//- Return gradient at boundary
		virtual Field<Type>& gradient()
		{
			return gradient_;
		}

		virtual const Field<Type>& gradient() const
		{
			return gradient_;
		}


		// Mapping functions

			//- Map (and resize as needed) from self given a mapping object
		virtual void autoMap
		(
			const fvPatchFieldMapper&
		);

		//- Reverse map the given fvPatchField onto this fvPatchField
		virtual void rmap
		(
			const fvPatchField<Type>&,
			const labelList&
		);


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type> > snGrad() const
		{
			return gradient_;
		}

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::blocking
		);

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
		virtual tmp<Field<Type> > gradientInternalCoeffs() const;

		//- Return the matrix source coefficients corresponding to the
		//  evaluation of the gradient of this patchField
		virtual tmp<Field<Type> > gradientBoundaryCoeffs() const;


		//- Write
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <fixedGradientFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedGradientFvPatchField_Header
