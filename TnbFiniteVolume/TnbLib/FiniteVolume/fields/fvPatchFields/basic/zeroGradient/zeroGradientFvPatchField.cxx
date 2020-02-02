#include <zeroGradientFvPatchField.hxx>

#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(p, iF)
	{}


	template<class Type>
	zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
	(
		const zeroGradientFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fvPatchField<Type>(p, iF, dict)
	{
		fvPatchField<Type>::operator=(this->patchInternalField());
	}


	template<class Type>
	zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
	(
		const zeroGradientFvPatchField& zgpf
	)
		:
		fvPatchField<Type>(zgpf)
	{}


	template<class Type>
	zeroGradientFvPatchField<Type>::zeroGradientFvPatchField
	(
		const zeroGradientFvPatchField& zgpf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(zgpf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void zeroGradientFvPatchField<Type>::evaluate(const Pstream::commsTypes)
	{
		if (!this->updated())
		{
			this->updateCoeffs();
		}

		fvPatchField<Type>::operator==(this->patchInternalField());
		fvPatchField<Type>::evaluate();
	}


	template<class Type>
	tmp<Field<Type> > zeroGradientFvPatchField<Type>::valueInternalCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return tmp<Field<Type> >
			(
				new Field<Type>(this->size(), pTraits<Type>::one)
				);
	}


	template<class Type>
	tmp<Field<Type> > zeroGradientFvPatchField<Type>::valueBoundaryCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return tmp<Field<Type> >
			(
				new Field<Type>(this->size(), pTraits<Type>::zero)
				);
	}


	template<class Type>
	tmp<Field<Type> >
		zeroGradientFvPatchField<Type>::gradientInternalCoeffs() const
	{
		return tmp<Field<Type> >
			(
				new Field<Type>(this->size(), pTraits<Type>::zero)
				);
	}


	template<class Type>
	tmp<Field<Type> >
		zeroGradientFvPatchField<Type>::gradientBoundaryCoeffs() const
	{
		return tmp<Field<Type> >
			(
				new Field<Type>(this->size(), pTraits<Type>::zero)
				);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //