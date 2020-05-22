#include <calculatedFvsPatchField.hxx>

#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type>
	const word& fvsPatchField<Type>::calculatedType()
	{
		return calculatedFvsPatchField<Type>::typeName;
	}

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	calculatedFvsPatchField<Type>::calculatedFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(p, iF)
	{}


	template<class Type>
	calculatedFvsPatchField<Type>::calculatedFvsPatchField
	(
		const calculatedFvsPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvsPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	calculatedFvsPatchField<Type>::calculatedFvsPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, surfaceMesh>& iF,
		const dictionary& dict
	)
		:
		fvsPatchField<Type>(p, iF, Field<Type>("value", dict, p.size()))
	{}


	template<class Type>
	calculatedFvsPatchField<Type>::calculatedFvsPatchField
	(
		const calculatedFvsPatchField<Type>& ptf
	)
		:
		fvsPatchField<Type>(ptf)
	{}


	template<class Type>
	calculatedFvsPatchField<Type>::calculatedFvsPatchField
	(
		const calculatedFvsPatchField<Type>& ptf,
		const DimensionedField<Type, surfaceMesh>& iF
	)
		:
		fvsPatchField<Type>(ptf, iF)
	{}


	template<class Type>
	template<class Type2>
	tmp<fvsPatchField<Type> > fvsPatchField<Type>::NewCalculatedType
	(
		const fvsPatchField<Type2>& pf
	)
	{
		typename patchConstructorTable::iterator patchTypeCstrIter =
			patchConstructorTablePtr_->find(pf.patch().type());

		if (patchTypeCstrIter != patchConstructorTablePtr_->end())
		{
			return patchTypeCstrIter()
				(
					pf.patch(),
					Field<Type>::null()
					);
		}
		else
		{
			return tmp<fvsPatchField<Type> >
				(
					new calculatedFvsPatchField<Type>
					(
						pf.patch(),
						Field<Type>::null()
						)
					);
		}
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Write
	template<class Type>
	void calculatedFvsPatchField<Type>::write(Ostream& os) const
	{
		fvsPatchField<Type>::write(os);
		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //