#pragma once
#ifndef _basicSymmetryFvPatchField_Header
#define _basicSymmetryFvPatchField_Header

#include <transformFvPatchFields.hxx>
#include <symmetryFvPatch.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					 Class basicSymmetryFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class basicSymmetryFvPatchField
		:
		public transformFvPatchField<Type>
	{
		// Private Data

			//- Skew correction
		Switch skewCorrected_;

		//- Second order accuracy correction
		Switch secondOrder_;


	public:

		//- Runtime type information
		TypeName(symmetryFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		basicSymmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		basicSymmetryFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given basicSymmetryFvPatchField onto a
		//  new patch
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new basicSymmetryFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		basicSymmetryFvPatchField
		(
			const basicSymmetryFvPatchField<Type>&,
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
					new basicSymmetryFvPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Evaluation functions

				//- Return gradient at boundary
		virtual tmp<Field<Type> > snGrad() const;

		//- Evaluate the patch field
		//  Default argument needed to allow call in constructors
		//  HJ, 30/Jun/2009
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::blocking
		);

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type> > snGradTransformDiag() const;


		// I-O

			//- Write
		virtual void write(Ostream& os) const;
	};


	// * * * * * * * * * * * Template Specialisations  * * * * * * * * * * * * * //

	template<>
	tmp<scalarField> basicSymmetryFvPatchField<scalar>::snGrad() const;

	template<>
	void basicSymmetryFvPatchField<scalar>::evaluate
	(
		const Pstream::commsTypes commsType
	);

	template<>
	tmp<vectorField> basicSymmetryFvPatchField<vector>::snGrad() const;

	template<>
	void basicSymmetryFvPatchField<vector>::evaluate
	(
		const Pstream::commsTypes commsType
	);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <basicSymmetryFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_basicSymmetryFvPatchField_Header
