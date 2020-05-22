#include <cyclicFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	cyclicFvPatchField<Type>::cyclicFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		coupledFvPatchField<Type>(p, iF),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{}


	template<class Type>
	cyclicFvPatchField<Type>::cyclicFvPatchField
	(
		const cyclicFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvPatchField<Type>(ptf, p, iF, mapper),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{
		if (!isType<cyclicFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"cyclicFvPatchField<Type>::cyclicFvPatchField\n"
				"(\n"
				"    const cyclicFvPatchField<Type>& ptf,\n"
				"    const fvPatch& p,\n"
				"    const DimensionedField<Type, volMesh>& iF,\n"
				"    const fvPatchFieldMapper& mapper\n"
				")\n"
			) << "\n    patch type '" << p.type()
				<< "' not constraint type '" << typeName << "'"
				<< "\n    for patch " << p.name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalIOError);
		}
	}


	template<class Type>
	cyclicFvPatchField<Type>::cyclicFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvPatchField<Type>(p, iF, dict),
		cyclicPatch_(refCast<const cyclicFvPatch>(p))
	{
		if (!isType<cyclicFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"cyclicFvPatchField<Type>::cyclicFvPatchField\n"
				"(\n"
				"    const fvPatch& p,\n"
				"    const Field<Type>& field,\n"
				"    const dictionary& dict\n"
				")\n",
				dict
			) << "\n    patch type '" << p.type()
				<< "' not constraint type '" << typeName << "'"
				<< "\n    for patch " << p.name()
				<< " of field " << this->dimensionedInternalField().name()
				<< " in file " << this->dimensionedInternalField().objectPath()
				<< exit(FatalIOError);
		}

		this->evaluate(Pstream::blocking);
	}


	template<class Type>
	cyclicFvPatchField<Type>::cyclicFvPatchField
	(
		const cyclicFvPatchField<Type>& ptf
	)
		:
		cyclicLduInterfaceField(),
		coupledFvPatchField<Type>(ptf),
		cyclicPatch_(ptf.cyclicPatch_)
	{}


	template<class Type>
	cyclicFvPatchField<Type>::cyclicFvPatchField
	(
		const cyclicFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		coupledFvPatchField<Type>(ptf, iF),
		cyclicPatch_(ptf.cyclicPatch_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<Field<Type> > cyclicFvPatchField<Type>::patchNeighbourField() const
	{
		const Field<Type>& iField = this->internalField();
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();

		tmp<Field<Type> > tpnf(new Field<Type>(this->size()));
		Field<Type>& pnf = tpnf();

		label sizeby2 = this->size() / 2;

		if (doTransform())
		{
			for (label facei = 0; facei < sizeby2; facei++)
			{
				pnf[facei] = transform
				(
					forwardT()[0], iField[faceCells[facei + sizeby2]]
				);

				pnf[facei + sizeby2] = transform
				(
					reverseT()[0], iField[faceCells[facei]]
				);
			}
		}
		else
		{
			for (label facei = 0; facei < sizeby2; facei++)
			{
				pnf[facei] = iField[faceCells[facei + sizeby2]];
				pnf[facei + sizeby2] = iField[faceCells[facei]];
			}
		}

		return tpnf;
	}


	template<class Type>
	void cyclicFvPatchField<Type>::updateInterfaceMatrix
	(
		const scalarField& psiInternal,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes,
		const bool switchToLhs
	) const
	{
		scalarField pnf(this->size());

		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();

		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}

		// Transform according to the transformation tensors
		transformCoupleField(pnf, cmpt);

		// Multiply the field by coefficients and add into the result
		if (switchToLhs)
		{
			forAll(faceCells, elemI)
			{
				result[faceCells[elemI]] += coeffs[elemI] * pnf[elemI];
			}
		}
		else
		{
			forAll(faceCells, elemI)
			{
				result[faceCells[elemI]] -= coeffs[elemI] * pnf[elemI];
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //