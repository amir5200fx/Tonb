#include <jumpMixingPlaneFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Type>
	jumpMixingPlaneFvPatchField<Type>::jumpMixingPlaneFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixingPlaneFvPatchField<Type>(p, iF)
	{}


	template<class Type>
	jumpMixingPlaneFvPatchField<Type>::jumpMixingPlaneFvPatchField
	(
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const dictionary& dict
	)
		:
		mixingPlaneFvPatchField<Type>(p, iF, dict)
	{}


	template<class Type>
	jumpMixingPlaneFvPatchField<Type>::jumpMixingPlaneFvPatchField
	(
		const jumpMixingPlaneFvPatchField<Type>& ptf,
		const fvPatch& p,
		const DimensionedField<Type, volMesh>& iF,
		const fvPatchFieldMapper& mapper
	)
		:
		mixingPlaneFvPatchField<Type>(ptf, p, iF, mapper)
	{}


	template<class Type>
	jumpMixingPlaneFvPatchField<Type>::jumpMixingPlaneFvPatchField
	(
		const jumpMixingPlaneFvPatchField<Type>& ptf
	)
		:
		mixingPlaneFvPatchField<Type>(ptf)
	{}


	template<class Type>
	jumpMixingPlaneFvPatchField<Type>::jumpMixingPlaneFvPatchField
	(
		const jumpMixingPlaneFvPatchField<Type>& ptf,
		const DimensionedField<Type, volMesh>& iF
	)
		:
		mixingPlaneFvPatchField<Type>(ptf, iF)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


	template<class Type>
	tmp<Field<Type> >
		jumpMixingPlaneFvPatchField<Type>::patchNeighbourField() const
	{
		// Get shadow patch internalField field
		Field<Type> sField = this->shadowPatchField().patchInternalField();

		if (this->mixing() == mixingPlaneInterpolation::AREA_AVERAGING)
		{
			// Area-weighted averaging
			return this->mixingPlanePatch().interpolate(sField);
		}
		else if (this->mixing() == mixingPlaneInterpolation::FLUX_AVERAGING)
		{
			// Flux averaging
			// - for outgoing flux, use zero gradient condition
			// - for incoming flux, use interpolated flux-weighted value

			const scalarField& mask = this->fluxMask();

			const scalarField& shadowFluxWeights =
				this->shadowPatchField().fluxWeights();

			// For outgoing flux, the value is identical to internal value
			// For incoming flux, calculate the average value of the
			// flux-weight shadow values coming out
			return
				this->mixingPlanePatch().fromProfile
				(
					mask*this->mixingPlanePatch().shadow().toProfile
					(
						sField*shadowFluxWeights
					)
				)
				+ this->mixingPlanePatch().fromProfile(1 - mask)*
				this->patchInternalField();
		}
		else if (this->mixing() == mixingPlaneInterpolation::ZERO_GRADIENT)
		{
			return this->patchInternalField();
		}
		else
		{
			FatalErrorIn
			(
				"tmp<Field<Type> > jumpMixingPlaneFvPatchField<Type>::"
				"patchNeighbourField() const"
			) << "Unknown mixing type for patch " << this->patch().name()
				<< " for field "
				<< this->dimensionedInternalField().name()
				<< abort(FatalError);
		}

		// Dummy return to keep compiler happy
		return this->patchInternalField();
	}



	template<class Type>
	void jumpMixingPlaneFvPatchField<Type>::initInterfaceMatrixUpdate
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

		if
			(
				this->mixing() == mixingPlaneInterpolation::AREA_AVERAGING
				|| this->mixing() == mixingPlaneInterpolation::FLUX_AVERAGING
				)
		{
			// Get shadow face-cells and assemble shadow field
			const unallocLabelList& sfc =
				this->mixingPlanePatch().shadow().faceCells();

			scalarField sField(sfc.size());

			forAll(sField, i)
			{
				sField[i] = psiInternal[sfc[i]];
			}

			// Get local faceCells
			const unallocLabelList& fc = this->mixingPlanePatch().faceCells();

			scalarField pnf = this->mixingPlanePatch().interpolate(sField);

			// Multiply the field by coefficients and add into the result
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
		else if (this->mixing() == mixingPlaneInterpolation::ZERO_GRADIENT)
		{
			// Do nothing
		}
		else
		{
			FatalErrorIn
			(
				"void jumpMixingPlaneFvPatchField<Type>::"
				"initInterfaceMatrixUpdate\n"
				"(\n"
				"    const scalarField& psiInternal,\n"
				"    scalarField& result,\n"
				"    const lduMatrix&,\n"
				"    const scalarField& coeffs,\n"
				"    const direction cmpt,\n"
				"    const Pstream::commsTypes commsType,\n"
				"    const bool switchToLhs\n"
				") const"
			) << "Unknown mixing type for patch " << this->patch().name()
				<< " for field "
				<< this->dimensionedInternalField().name()
				<< abort(FatalError);
		}

	}


	template<class Type>
	void jumpMixingPlaneFvPatchField<Type>::updateInterfaceMatrix
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