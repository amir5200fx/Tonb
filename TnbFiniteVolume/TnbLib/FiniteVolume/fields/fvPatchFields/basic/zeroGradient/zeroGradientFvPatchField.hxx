#pragma once
#ifndef _zeroGradientFvPatchField_Header
#define _zeroGradientFvPatchField_Header

#include <fvPatchField.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class zeroGradientFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class zeroGradientFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName("zeroGradient");


		// Constructors

			//- Construct from patch and internal field
		zeroGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		zeroGradientFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given zeroGradientFvPatchField<Type>
		//  onto a new patch
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new zeroGradientFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		zeroGradientFvPatchField
		(
			const zeroGradientFvPatchField<Type>&,
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
					new zeroGradientFvPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Evaluation functions

				//- Return gradient at boundary
		virtual tmp<Field<Type> > snGrad() const
		{
			return tmp<Field<Type> >
				(
					new Field<Type>(this->size(), pTraits<Type>::zero)
					);
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
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <zeroGradientFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_zeroGradientFvPatchField_Header
