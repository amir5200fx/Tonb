#pragma once
#ifndef _cyclicFvPatchField_Header
#define _cyclicFvPatchField_Header

#include <coupledFvPatchField.hxx>
#include <cyclicLduInterfaceField.hxx>
#include <cyclicFvPatch.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class cyclicFvPatchField Declaration
	\*---------------------------------------------------------------------------*/

	template<class Type>
	class cyclicFvPatchField
		:
		virtual public cyclicLduInterfaceField,
		public coupledFvPatchField<Type>
	{
		// Private data

			//- Local reference cast into the cyclic patch
		const cyclicFvPatch& cyclicPatch_;


		// Private member functions

			//- Return neighbour side field given internal fields
		template<class Type2>
		tmp<Field<Type2> > neighbourSideField
		(
			const Field<Type2>&
		) const;


	public:

		//- Runtime type information
		TypeName(cyclicFvPatch::typeName_());


		// Constructors

			//- Construct from patch and internal field
		cyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&
		);

		//- Construct from patch, internal field and dictionary
		cyclicFvPatchField
		(
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const dictionary&
		);

		//- Construct by mapping given cyclicFvPatchField onto a new patch
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&,
			const fvPatch&,
			const DimensionedField<Type, volMesh>&,
			const fvPatchFieldMapper&
		);

		//- Construct as copy
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&
		);

		//- Construct and return a clone
		virtual tmp<fvPatchField<Type> > clone() const
		{
			return tmp<fvPatchField<Type> >
				(
					new cyclicFvPatchField<Type>(*this)
					);
		}

		//- Construct as copy setting internal field reference
		cyclicFvPatchField
		(
			const cyclicFvPatchField<Type>&,
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
					new cyclicFvPatchField<Type>(*this, iF)
					);
		}


		// Member functions

			// Access

				//- Retirn local reference cast into the cyclic patch
		const cyclicFvPatch& cyclicPatch() const
		{
			return cyclicPatch_;
		}


		// Evaluation functions

			//- Return neighbour coupled given internal cell data
		virtual tmp<Field<Type> > patchNeighbourField() const;


		// Coupled interface functionality

			//- Transform neighbour field
		virtual void transformCoupleField
		(
			scalarField& pnf,
			const direction cmpt
		) const
		{
			// See comments in cyclicLduInterfaceField
			// HJ, 3/Sep/2015
//                 cyclicLduInterfaceField::transformCoupleField(pnf, cmpt);
			if (doTransform())
			{
				label sizeby2 = pnf.size() / 2;

				Type powFwdTransform = transform
				(
					this->forwardT()[0],
					pTraits<Type>::one
				);

				scalar forwardScale =
					pow(component(powFwdTransform, cmpt), rank());

				Type powRevTransform = transform
				(
					this->reverseT()[0],
					pTraits<Type>::one
				);

				scalar reverseScale =
					pow(component(powRevTransform, cmpt), rank());

				for (label facei = 0; facei < sizeby2; facei++)
				{
					pnf[facei] *= forwardScale;
					pnf[facei + sizeby2] *= reverseScale;
				}
			}
		}

		//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			const scalarField& psiInternal,
			scalarField& result,
			const lduMatrix&,
			const scalarField& coeffs,
			const direction cmpt,
			const Pstream::commsTypes commsType,
			const bool switchToLhs
		) const;


		// Block coupled interface functionality

//             //- Transform given patch field
//             virtual void transformCoupleField
//             (
//                 Field<Type>& f
//             ) const;

			//- Update result field based on interface functionality
		virtual void updateInterfaceMatrix
		(
			const Field<Type>&,
			Field<Type>&,
			const BlockLduMatrix<Type>&,
			const CoeffField<Type>&,
			const Pstream::commsTypes commsType,
			const bool switchToLhs
		) const
		{
			notImplemented
			(
				"cyclicFvPatchField<Type>::"
				"updateInterfaceMatrix for block matrices"
			);
		}


		//- Cyclic coupled interface functions

			//- Does the patch field perform the transfromation
		virtual bool doTransform() const
		{
			return !(cyclicPatch_.parallel() || pTraits<Type>::rank == 0);
		}

		//- Return face transformation tensor
		virtual const tensorField& forwardT() const
		{
			return cyclicPatch_.forwardT();
		}

		//- Return neighbour-cell transformation tensor
		virtual const tensorField& reverseT() const
		{
			return cyclicPatch_.reverseT();
		}

		//- Return rank of component for transform
		virtual int rank() const
		{
			return pTraits<Type>::rank;
		}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <cyclicFvPatchField.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatchField_Header
