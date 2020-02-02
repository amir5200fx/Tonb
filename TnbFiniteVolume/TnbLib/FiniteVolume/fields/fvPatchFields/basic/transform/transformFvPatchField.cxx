#include <transformFvPatchField.hxx>

#include <IOstreams.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	transformFvPatchField<Type>::transformFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(p, iF)
	{}


	template<class Type>
	transformFvPatchField<Type>::transformFvPatchField
	(
		const transformFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		fvPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	transformFvPatchField<Type>::transformFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		fvPatchField<Type>(p, iF, dict)
	{}


	template<class Type>
	transformFvPatchField<Type>::transformFvPatchField
	(
		const transformFvPatchField<Type>& ptf
	)
		:
		fvPatchField<Type>(ptf)
	{}


	template<class Type>
	transformFvPatchField<Type>::transformFvPatchField
	(
		const transformFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		fvPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<Field<Type> > transformFvPatchField<Type>::valueInternalCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return pTraits<Type>::one - this->snGradTransformDiag();
	}


	template<class Type>
	tmp<Field<Type> > transformFvPatchField<Type>::valueBoundaryCoeffs
	(
		const tmp<scalarField>&
	) const
	{
		return
			*this
			- cmptMultiply
			(
				this->valueInternalCoeffs(this->patch().weights()),
				this->patchInternalField()
			);
	}


	template<class Type>
	tmp<Field<Type> > transformFvPatchField<Type>::gradientInternalCoeffs() const
	{
		return -this->patch().deltaCoeffs()*this->snGradTransformDiag();
	}


	template<class Type>
	tmp<Field<Type> > transformFvPatchField<Type>::gradientBoundaryCoeffs() const
	{
		return
			this->snGrad()
			- cmptMultiply
			(
				this->gradientInternalCoeffs(),
				this->patchInternalField()
			);
	}


	// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

	template<class Type>
	void transformFvPatchField<Type>::operator=
		(
			const fvPatchField<Type>& ptf
			)
	{
		this->evaluate();
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //