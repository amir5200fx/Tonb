#include <cyclicGgiFvPatchFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>
#include <scalarCoeffField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<>
	void cyclicGgiFvPatchField<scalar>::initInterfaceMatrixUpdate
	(
		const Field<scalar>& psiInternal,
		Field<scalar>& result,
		const BlockLduMatrix<scalar>& m,
		const CoeffField<scalar>& coeffs,
		const Pstream::commsTypes commsType
	) const
	{
		// Communication is allowed either before or after processor
		// patch comms.  HJ, 11/Jul/2011

		// Get shadow face-cells and assemble shadow field
		const unallocLabelList& sfc = cyclicGgiPatch_.shadow().faceCells();

		scalarField sField(sfc.size());

		forAll(sField, i)
		{
			sField[i] = psiInternal[sfc[i]];
		}

		// Note: scalar interpolate does not get a transform, so this is safe
		// HJ, 12/Jan/2009
		scalarField pnf = cyclicGgiPatch_.interpolate(sField);

		// Multiply the field by coefficients and add into the result
		const unallocLabelList& fc = cyclicGgiPatch_.faceCells();

		forAll(fc, elemI)
		{
			result[fc[elemI]] -= coeffs[elemI] * pnf[elemI];
		};
	}


	template<>
	void cyclicGgiFvPatchField<vector>::initInterfaceMatrixUpdate
	(
		const Field<vector>& psiInternal,
		Field<vector>& result,
		const BlockLduMatrix<vector>& m,
		const CoeffField<vector>& coeffs,
		const Pstream::commsTypes commsType
	) const
	{
		// Communication is allowed either before or after processor
		// patch comms.  HJ, 11/Jul/2011

		// Get shadow face-cells and assemble shadow field
		const unallocLabelList& sfc = cyclicGgiPatch_.shadow().faceCells();

		Field<vector> sField(sfc.size());

		forAll(sField, i)
		{
			sField[i] = psiInternal[sfc[i]];
		}

		// Transformation is handled in interpolation.  HJ, 7/Jan/2009
		Field<vector> pnf = cyclicGgiPatch_.interpolate(sField);

		if (coeffs.activeType() == blockCoeffBase::SCALAR)
		{
			pnf = coeffs.asScalar() * pnf;
		}
		else if (coeffs.activeType() == blockCoeffBase::LINEAR)
		{
			pnf = cmptMultiply(coeffs.asLinear(), pnf);
		}
		else if (coeffs.activeType() == blockCoeffBase::SQUARE)
		{
			pnf = coeffs.asSquare() & pnf;
		}

		// Multiply the field by coefficients and add into the result
		const unallocLabelList& fc = cyclicGgiPatch_.faceCells();

		// Multiply the field by coefficients and add into the result
		forAll(fc, elemI)
		{
			result[fc[elemI]] -= pnf[elemI];
		}
	}


	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	makePatchFields(cyclicGgi);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //