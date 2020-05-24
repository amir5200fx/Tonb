#pragma once
#ifndef _transformFvPatchField_Header
#define _transformFvPatchField_Header

#include <fvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class transformFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class transformFvPatchField
		:
		public fvPatchField<Type>
	{

	public:

		//- Runtime type information
		TypeName("transform");


		// Constructors

			//- Construct from patch and internal field
		transformFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		transformFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping the given transformFvPatchField<Type>
		//  onto a new patch
		transformFvPatchField
		(
			const transformFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		transformFvPatchField
		(
			const transformFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const = 0;

		//- Construct as copy setting internal field reference
		transformFvPatchField
		(
			const transformFvPatchField<Type>&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct and return a clone setting internal field reference
		virtual tmp<fvPatchField<Type> > clone
		(
			const DimensionedField<Type, volMesh>&
		) const = 0;


		// Member functions

			// Evaluation functions

				//- Return gradient at boundary
		virtual tmp<Field<Type> > snGrad() const = 0;

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type> > snGradTransformDiag() const = 0;

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


		// Member operators

		virtual void operator=(const fvPatchField<Type>&);
	};


	// * * * * * * * * * * * Template Specialisations  * * * * * * * * * * * * * //

	template<>
	tmp<scalarField>
		transformFvPatchField<scalar>::gradientInternalCoeffs() const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <transformFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformFvPatchField_Header
