#pragma once
#ifndef _directionMixedFvPatchField_Header
#define _directionMixedFvPatchField_Header

#include <transformFvPatchFields.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class directionMixedFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class directionMixedFvPatchField
		:
		public transformFvPatchField<Type>
	{
		// Private data

			//- Value field
		Field<Type> refValue_;

		//- Normal gradient field
		Field<Type> refGrad_;

		//- Fraction (0-1) of value used for boundary condition
		symmTensorField valueFraction_;


	public:

		//- Runtime type information
		TypeName("directionMixed");


		// Constructors

			//- Construct from patch and internal field
		directionMixedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		directionMixedFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given directionMixedFvPatchField onto
		//  a new patch
		directionMixedFvPatchField
		(
			const directionMixedFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new directionMixedFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy
		directionMixedFvPatchField
		(
			const directionMixedFvPatchField<Type>&
		);

		//- Construct as copy setting internal field reference
		directionMixedFvPatchField
		(
			const directionMixedFvPatchField<Type>&,
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
					new directionMixedFvPatchField<Type>(*this, iF)
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


		// Return defining fields

			//- Return reference value
		virtual const Field<Type>& refValue() const
		{
			return refValue_;
		}

		//- Return access to reference value
		virtual Field<Type>& refValue()
		{
			return refValue_;
		}

		//- Return reference gradient
		virtual const Field<Type>& refGrad() const
		{
			return refGrad_;
		}

		//- Return access to reference gradient
		virtual Field<Type>& refGrad()
		{
			return refGrad_;
		}

		//- Return value fraction
		virtual const symmTensorField& valueFraction() const
		{
			return valueFraction_;
		}

		//- Return access to value fraction
		virtual symmTensorField& valueFraction()
		{
			return valueFraction_;
		}


		// Evaluation functions

			//- Return gradient at boundary
		virtual tmp<Field<Type> > snGrad() const;

		//- Evaluate the patch field
		virtual void evaluate
		(
			const Pstream::commsTypes commsType = Pstream::blocking
		);

		//- Return face-gradient transform diagonal
		virtual tmp<Field<Type> > snGradTransformDiag() const;


		//- Write
		virtual void write(Ostream&) const;


		// Member operators

		virtual void operator=(const fvPatchField<Type>&) {}
		virtual void operator+=(const fvPatchField<Type>&) {}
		virtual void operator-=(const fvPatchField<Type>&) {}
		virtual void operator*=(const fvPatchField<Type>&) {}
		virtual void operator/=(const fvPatchField<Type>&) {}

		virtual void operator=(const Field<Type>&) {}
		virtual void operator+=(const Field<Type>&) {}
		virtual void operator-=(const Field<Type>&) {}
		virtual void operator*=(const Field<scalar>&) {}
		virtual void operator/=(const Field<scalar>&) {}

		virtual void operator=(const Type&) {}
		virtual void operator+=(const Type&) {}
		virtual void operator-=(const Type&) {}
		virtual void operator*=(const scalar) {}
		virtual void operator/=(const scalar) {}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <directionMixedFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_directionMixedFvPatchField_Header
