#include <overlapGgiFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	overlapGgiFvPatchField<Type>::overlapGgiFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		coupledFvPatchField<Type>(p, iF),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{}


	template<class Type>
	overlapGgiFvPatchField<Type>::overlapGgiFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvPatchField<Type>(p, iF, dict, false),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{
		if (!isType<overlapGgiFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"overlapGgiFvPatchField<Type>::overlapGgiFvPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, volMesh>& iF,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "patch " << this->patch().index() << " not overlapGgi type. "
				<< "Patch type = " << p.type()
				<< exit(FatalIOError);
		}

		if (!dict.found("value"))
		{
			// Grab the internal value for initialisation. (?) HJ, 27/Feb/2009
			fvPatchField<Type>::operator=(this->patchInternalField()());
		}
	}


	template<class Type>
	overlapGgiFvPatchField<Type>::overlapGgiFvPatchField
	(
		const overlapGgiFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvPatchField<Type>(ptf, p, iF, mapper),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(p))
	{
		if (!isType<overlapGgiFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"overlapGgiFvPatchField<Type>::overlapGgiFvPatchField\n"
				"(\n"
				"    const overlapGgiFvPatchField<Type>& ptf,\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, volMesh>& iF,\n"
				"    const fvPatchFieldMapper& mapper\n"
				")\n"
			) << "Field type does not correspond to patch type for patch "
				<< this->patch().index() << "." << endl
				<< "Field type: " << typeName << endl
				<< "Patch type: " << this->patch().type()
				<< exit(FatalError);
		}
	}


	template<class Type>
	overlapGgiFvPatchField<Type>::overlapGgiFvPatchField
	(
		const overlapGgiFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		overlapGGILduInterfaceField(),
		coupledFvPatchField<Type>(ptf, iF),
		overlapGgiPatch_(refCast<const overlapGgiFvPatch>(ptf.patch()))
	{
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Return neighbour field
	template<class Type>
	tmp<Field<Type> > overlapGgiFvPatchField<Type>::patchNeighbourField() const
	{
		const Field<Type>& iField = this->internalField();

		// Get shadow face-cells and assemble shadow field
		const unallocLabelList& sfc = overlapGgiPatch_.shadow().faceCells();

		Field<Type> sField(sfc.size());

		forAll(sField, i)
		{
			sField[i] = iField[sfc[i]];
		}

		// Expansion and transformation is handled in interpolation
		// HJ, 7/Jan/2009
		return overlapGgiPatch_.interpolate(sField);
	}


	template<class Type>
	void overlapGgiFvPatchField<Type>::initEvaluate
	(
		const Pstream::commsTypes commsType
	)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}

		Field<Type>::operator=
			(
				this->patch().weights()*this->patchInternalField()
				+ (1.0 - this->patch().weights())*this->patchNeighbourField()
				);

	}


	template<class Type>
	void overlapGgiFvPatchField<Type>::evaluate
	(
		const Pstream::commsTypes
	)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}
	}


	template<class Type>
	void overlapGgiFvPatchField<Type>::initInterfaceMatrixUpdate
	(
		const scalarField& psiInternal,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		// Communication is allowed either before or after processor
		// patch comms.  HJ, 11/Jul/2011

		// Get shadow face-cells and assemble shadow field
		const unallocLabelList& sfc = overlapGgiPatch_.shadow().faceCells();

		scalarField sField(sfc.size());

		forAll(sField, i)
		{
			sField[i] = psiInternal[sfc[i]];
		}

		scalarField pnf = overlapGgiPatch_.interpolate(sField);

		// Multiply the field by coefficients and add into the result
		const unallocLabelList& fc = overlapGgiPatch_.faceCells();

		if (switchToLhs)
		{
			forAll(fc, elemI)
			{
				result[fc[elemI]] += coeffs[elemI] * pnf[elemI];
			}
		}
		else
		{
			forAll(fc, elemI)
			{
				result[fc[elemI]] -= coeffs[elemI] * pnf[elemI];
			}
		}
	}


	// Return matrix product for coupled boundary
	template<class Type>
	void overlapGgiFvPatchField<Type>::updateInterfaceMatrix
	(
		const scalarField& psiInternal,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes,
		const bool switchToLhs
	) const
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //