#include <fixedInternalValueFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>
#include <fvMatrices.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::setInInternalField() const
{
	Field<Type>& vf = const_cast<Field<Type>&>
		(
			this->internalField()
			);

	const labelList& faceCells = this->patch().faceCells();

	// Apply the refValue into the cells next to the boundary
	forAll(faceCells, faceI)
	{
		vf[faceCells[faceI]] = refValue_[faceI];
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(p, iF),
	refValue_(p.size(), pTraits<Type>::zero)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const dictionary& dict
)
	:
	zeroGradientFvPatchField<Type>(p, iF, dict),
	refValue_(p.size())
{
	if (dict.found("refValue"))
	{
		refValue_ = Field<Type>("refValue", dict, p.size());
	}
	else
	{
		refValue_ = this->patchInternalField();
	}
}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField<Type>& ptf,
	const fvPatch& p,
	const DimensionedField<Type, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	zeroGradientFvPatchField<Type>(ptf, p, iF, mapper),
	refValue_(ptf.refValue_, mapper)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField& fivpf
)
	:
	zeroGradientFvPatchField<Type>(fivpf),
	refValue_(fivpf.refValue_)
{}


template<class Type>
tnbLib::fixedInternalValueFvPatchField<Type>::fixedInternalValueFvPatchField
(
	const fixedInternalValueFvPatchField& fivpf,
	const DimensionedField<Type, volMesh>& iF
)
	:
	zeroGradientFvPatchField<Type>(fivpf, iF),
	refValue_(fivpf.refValue_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::autoMap
(
	const fvPatchFieldMapper& m
)
{
	fvPatchField<Type>::autoMap(m);
	refValue_.autoMap(m);
}


template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::rmap
(
	const fvPatchField<Type>& ptf,
	const labelList& addr
)
{
	fvPatchField<Type>::rmap(ptf, addr);

	const fixedInternalValueFvPatchField<Type>& mptf =
		refCast<const fixedInternalValueFvPatchField<Type> >(ptf);

	refValue_.rmap(mptf.refValue_, addr);
}


template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::updateCoeffs()
{
	// Set refValue in internal field
	this->setInInternalField();

	fvPatchField<Type>::updateCoeffs();
}


template<class Type>
void
tnbLib::fixedInternalValueFvPatchField<Type>::evaluate
(
	const Pstream::commsTypes
)
{
	if (!this->updated())
	{
		this->updateCoeffs();
	}

	// Force reassingment of refValue in internal field
	this->setInInternalField();

	zeroGradientFvPatchField<Type>::evaluate();
}


template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::manipulateMatrix
(
	fvMatrix<Type>& matrix
)
{
	// Apply the refValue as a constraint in the matrix
	matrix.setValues(this->patch().faceCells(), refValue_);
}


template<class Type>
void tnbLib::fixedInternalValueFvPatchField<Type>::write(Ostream& os) const
{
	fvPatchField<Type>::write(os);
	refValue_.writeEntry("refValue", os);
	this->writeEntry("value", os);
}


// ************************************************************************* //