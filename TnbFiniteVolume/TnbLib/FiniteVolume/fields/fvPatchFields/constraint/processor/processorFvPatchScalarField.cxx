#include <processorFvPatchScalarField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<>
	void processorFvPatchField<scalar>::initInterfaceMatrixUpdate
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
			patch().patchInternalField(psiInternal)()
		);
	}


	template<>
	void processorFvPatchField<scalar>::updateInterfaceMatrix
	(
		const scalarField&,
		scalarField& result,
		const lduMatrix&,
		const scalarField& coeffs,
		const direction,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		scalarField pnf
		(
			procPatch_.compressedReceive<scalar>(commsType, this->size())()
		);

		const unallocLabelList& faceCells = patch().faceCells();

		if (switchToLhs)
		{
			forAll(faceCells, facei)
			{
				result[faceCells[facei]] += coeffs[facei] * pnf[facei];
			}
		}
		else
		{
			forAll(faceCells, facei)
			{
				result[faceCells[facei]] -= coeffs[facei] * pnf[facei];
			}
		}
	}


	template<>
	void processorFvPatchField<scalar>::initInterfaceMatrixUpdate
	(
		const scalarField& psiInternal,
		scalarField&,
		const BlockLduMatrix<scalar>&,
		const CoeffField<scalar>&,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		procPatch_.compressedSend
		(
			commsType,
			patch().patchInternalField(psiInternal)()
		);
	}


	template<>
	void processorFvPatchField<scalar>::updateInterfaceMatrix
	(
		const scalarField&,
		scalarField& result,
		const BlockLduMatrix<scalar>&,
		const CoeffField<scalar>& coeffs,
		const Pstream::commsTypes commsType,
		const bool switchToLhs
	) const
	{
		scalarField pnf
		(
			procPatch_.compressedReceive<scalar>(commsType, this->size())()
		);

		const unallocLabelList& faceCells = patch().faceCells();
		const scalarField& scalarCoeffs = coeffs.asScalar();

		if (switchToLhs)
		{
			forAll(faceCells, facei)
			{
				result[faceCells[facei]] += scalarCoeffs[facei] * pnf[facei];
			}
		}
		else
		{
			forAll(faceCells, facei)
			{
				result[faceCells[facei]] -= scalarCoeffs[facei] * pnf[facei];
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //