#include <processorFvPatchField.hxx>

#include <processorFvPatch.hxx>
#include <IPstream.hxx>
#include <OPstream.hxx>
#include <transformField.hxx>
#include <coeffFields.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

	template<class Type>
	processorFvPatchField<Type>::processorFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		coupledFvPatchField<Type>(p, iF),
		procPatch_(refCast<const processorFvPatch>(p))
	{}


	template<class Type>
	processorFvPatchField<Type>::processorFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const Field<Type>& f
	)
		:
		coupledFvPatchField<Type>(p, iF, f),
		procPatch_(refCast<const processorFvPatch>(p))
	{}


	// Construct by mapping given processorFvPatchField<Type>
	template<class Type>
	processorFvPatchField<Type>::processorFvPatchField
	(
		const processorFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		coupledFvPatchField<Type>(ptf, p, iF, mapper),
		procPatch_(refCast<const processorFvPatch>(p))
	{
		if (!isType<processorFvPatch>(this->patch()))
		{
			FatalErrorIn
			(
				"processorFvPatchField<Type>::processorFvPatchField\n"
				"(\n"
				"    const processorFvPatchField<Type>& ptf,\n"
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
	processorFvPatchField<Type>::processorFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		coupledFvPatchField<Type>(p, iF, dict),
		procPatch_(refCast<const processorFvPatch>(p))
	{
		if (!isType<processorFvPatch>(p))
		{
			FatalIOErrorIn
			(
				"processorFvPatchField<Type>::processorFvPatchField\n"
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
	}


	template<class Type>
	processorFvPatchField<Type>::processorFvPatchField
	(
		const processorFvPatchField<Type>& ptf
	)
		:
		processorLduInterfaceField(),
		coupledFvPatchField<Type>(ptf),
		procPatch_(refCast<const processorFvPatch>(ptf.patch()))
	{}


	template<class Type>
	processorFvPatchField<Type>::processorFvPatchField
	(
		const processorFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		coupledFvPatchField<Type>(ptf, iF),
		procPatch_(refCast<const processorFvPatch>(ptf.patch()))
	{}


	// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

	template<class Type>
	processorFvPatchField<Type>::~processorFvPatchField()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<Field<Type> > processorFvPatchField<Type>::patchNeighbourField() const
	{
		// Warning: returning own patch field, which on update stores
		// actual neighbour data
		// HJ, 14/May/2009
		return *this;
	}


	template<class Type>
	void processorFvPatchField<Type>::initEvaluate
	(
		const Pstream::commsTypes commsType
	)
	{
		if (Pstream::parRun())
		{
			procPatch_.compressedSend(commsType, this->patchInternalField()());
		}
	}


	template<class Type>
	void processorFvPatchField<Type>::evaluate
	(
		const Pstream::commsTypes commsType
	)
	{
		if (Pstream::parRun())
		{
			procPatch_.compressedReceive<Type>(commsType, *this);

			if (doTransform())
			{
				transform(*this, procPatch_.forwardT(), *this);
			}
		}
	}


	template<class Type>
	tmp<Field<Type> > processorFvPatchField<Type>::snGrad() const
	{
		return this->patch().deltaCoeffs()*(*this - this->patchInternalField());
	}


	template<class Type>
	void processorFvPatchField<Type>::initInterfaceMatrixUpdate
	(
		const scalarField& psiInternal,
		scalarField&,
		const lduMatrix&,
		const scalarField&,
		const direction,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		procPatch_.compressedSend
		(
			commsType,
			this->patch().patchInternalField(psiInternal)()
		);
	}


	template<class Type>
	void processorFvPatchField<Type>::updateInterfaceMatrix
	(
		const scalarField&,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction cmpt,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		scalarField pnf
		(
			procPatch_.compressedReceive<scalar>(commsType, this->size())()
		);

		// Transform according to the transformation tensor
		transformCoupleField(pnf, cmpt);

		// Multiply the field by coefficients and add into the result
		const unallocLabelList& faceCells = this->patch().faceCells();

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


	template<class Type>
	void processorFvPatchField<Type>::initInterfaceMatrixUpdate
	(
		const Field<Type>& psiInternal,
		Field<Type>&,
		const BlockLduMatrix<Type>&,
		const CoeffField<Type>&,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		procPatch_.compressedSend
		(
			commsType,
			this->patch().patchInternalField(psiInternal)()
		);
	}


	template<class Type>
	void processorFvPatchField<Type>::updateInterfaceMatrix
	(
		const Field<Type>& psiInternal,
		Field<Type>& result,
		const BlockLduMatrix<Type>&,
		const CoeffField<Type>& coeffs,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		Field<Type> pnf
		(
			procPatch_.compressedReceive<Type>(commsType, this->size())()
		);

		// Multiply neighbour field with coeffs and re-use pnf for result
		// of multiplication
		multiply(pnf, coeffs, pnf);

		const unallocLabelList& faceCells = this->patch().faceCells();

		if (switchToLhs)
		{
			forAll(faceCells, elemI)
			{
				result[faceCells[elemI]] += pnf[elemI];
			}
		}
		else
		{
			forAll(faceCells, elemI)
			{
				result[faceCells[elemI]] -= pnf[elemI];
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //