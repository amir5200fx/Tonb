#include <mixingPlaneEnthalpyJumpFvPatchField.hxx>

#include <IOmanip.hxx>
#include <fvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	mixingPlaneEnthalpyJumpFvPatchField<Type>::mixingPlaneEnthalpyJumpFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		jumpMixingPlaneFvPatchField<Type>(p, iF),
		rotating_(false),
		jump_(this->size(), pTraits<Type>::zero)
	{}


	template<class Type>
	mixingPlaneEnthalpyJumpFvPatchField<Type>::mixingPlaneEnthalpyJumpFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		jumpMixingPlaneFvPatchField<Type>(p, iF),
		rotating_(dict.lookup("rotating")),
		jump_(this->size(), pTraits<Type>::zero)
	{
		if (dict.found("value"))
		{
			fvPatchField<Type>::operator=
				(
					Field<Type>("value", dict, p.size())
					);
		}
		else
		{
			this->evaluate(Pstream::blocking);
		}
	}


	template<class Type>
	mixingPlaneEnthalpyJumpFvPatchField<Type>::mixingPlaneEnthalpyJumpFvPatchField
	(
		const mixingPlaneEnthalpyJumpFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		jumpMixingPlaneFvPatchField<Type>(ptf, p, iF, mapper),
		rotating_(ptf.rotating_),
		jump_(ptf.jump_, mapper)
	{}


	template<class Type>
	mixingPlaneEnthalpyJumpFvPatchField<Type>::mixingPlaneEnthalpyJumpFvPatchField
	(
		const mixingPlaneEnthalpyJumpFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		jumpMixingPlaneFvPatchField<Type>(ptf, iF),
		rotating_(ptf.rotating_),
		jump_(ptf.jump_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	void mixingPlaneEnthalpyJumpFvPatchField<Type>::autoMap
	(
		const fvPatchFieldMapper& m
	)
	{
		jumpMixingPlaneFvPatchField<Type>::autoMap(m);
		jump_.autoMap(m);
	}


	template<class Type>
	void mixingPlaneEnthalpyJumpFvPatchField<Type>::rmap
	(
		const fvPatchField<Type>& ptf,
		const labelList& addr
	)
	{
		jumpMixingPlaneFvPatchField<Type>::rmap(ptf, addr);

		// rmap jump
		const mixingPlaneEnthalpyJumpFvPatchField<Type>& ejPtf =
			refCast<const mixingPlaneEnthalpyJumpFvPatchField<Type> >(ptf);

		jump_.rmap(ejPtf.jump_, addr);
	}


	template<class Type>
	void mixingPlaneEnthalpyJumpFvPatchField<Type>::write(Ostream& os) const
	{
		fvPatchField<Type>::write(os);
		os.writeKeyword("patchType")
			<< mixingPlaneFvPatch::typeName << token::END_STATEMENT << nl;
		os.writeKeyword("rotating")
			<< rotating_ << token::END_STATEMENT << nl;

		IOstream::streamFormat fmt0 = os.format(IOstream::ASCII);
		os.format(fmt0);

		this->writeEntry("value", os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //