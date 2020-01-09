#ifndef _sphericalTensorExtendedBlockLduMatrix_CXX
#define _sphericalTensorExtendedBlockLduMatrix_CXX

#include <extendedBlockLduMatrix.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<>
	void tnbLib::extendedBlockLduMatrix<tnbLib::sphericalTensor>::mapOffDiagCoeffs
	(
		const BlockLduMatrix<sphericalTensor>& blockLdum
	)
	{
		if (blockLdum.diagonal())
		{
			WarningIn
			(
				"void extendedBlockLduMatrix<sphericalTensor>::mapOffDiagCoeffs\n"
				"(\n"
				"    const BlockLduMatrix<sphericalTensor>& blockLdum\n"
				")"
			) << "Attempted to create extended lower/upper coeffs for block "
				<< "matrix that is diagonal."
				<< nl << endl;
		}
		else if (blockLdum.symmetric())
		{
			// Get reference to faceMap in extended addressing
			const unallocLabelList& faceMap = extLduAddr_.faceMap();

			// Avoid assuming it's upper if the matrix is symmetric
			if (blockLdum.thereIsUpper())
			{
				// Allocate extended upper only
				extendedUpperPtr_ = new TypeCoeffField
				(
					extLduAddr_.extendedUpperAddr().size()
				);
				TypeCoeffField& extUpper = *extendedUpperPtr_;

				// Get upper coeffs from underlying lduMatrix
				const TypeCoeffField& upper = blockLdum.upper();

				if (upper.activeType() == blockCoeffBase::SCALAR)
				{
					// Helper type definition
					typedef CoeffField<sphericalTensor>::scalarTypeField
						activeType;

					// Get references to fields
					const activeType& activeUpper = upper.asScalar();
					activeType& activeExtUpper = extUpper.asScalar();

					// Copy non-zero coeffs from basic lduMatrix into corresponding
					// positions
					forAll(upper, faceI)
					{
						activeExtUpper[faceMap[faceI]] = activeUpper[faceI];
					}
				}
				else if (upper.activeType() == blockCoeffBase::LINEAR)
				{
					// Helper type definition
					typedef CoeffField<sphericalTensor>::linearTypeField
						activeType;

					// Get references to fields
					const activeType& activeUpper = upper.asLinear();
					activeType& activeExtUpper = extUpper.asLinear();

					// Copy non-zero coeffs from basic lduMatrix into corresponding
					// positions
					forAll(upper, faceI)
					{
						activeExtUpper[faceMap[faceI]] = activeUpper[faceI];
					}
				}
				else
				{
					FatalErrorIn
					(
						"void extendedBlockLduMatrix<sphericalTensor>::"
						"mapOffDiagCoeffs\n"
						"(\n"
						"    const BlockLduMatrix<sphericalTensor>& blockLdum\n"
						")"
					) << "Problem between ordinary block matrix and extended"
						<< " block matrix upper coeffs type morphing."
						<< abort(FatalError);
				}
			}
			else
			{
				// Allocate extended lower only
				extendedLowerPtr_ = new TypeCoeffField
				(
					extLduAddr_.extendedLowerAddr().size()
				);
				TypeCoeffField& extLower = *extendedLowerPtr_;

				// Get lower coeffs from underlying lduMatrix
				const TypeCoeffField& lower = blockLdum.lower();

				if (lower.activeType() == blockCoeffBase::SCALAR)
				{
					// Helper type definition
					typedef CoeffField<sphericalTensor>::scalarTypeField
						activeType;

					// Get references to fields
					const activeType& activeLower = lower.asScalar();
					activeType& activeExtLower = extLower.asScalar();

					// Copy non-zero coeffs from basic lduMatrix into corresponding
					// positions
					forAll(lower, faceI)
					{
						activeExtLower[faceMap[faceI]] = activeLower[faceI];
					}
				}
				else if (lower.activeType() == blockCoeffBase::LINEAR)
				{
					// Helper type definition
					typedef CoeffField<sphericalTensor>::linearTypeField
						activeType;

					// Get references to fields
					const activeType& activeLower = lower.asLinear();
					activeType& activeExtLower = extLower.asLinear();

					// Copy non-zero coeffs from basic lduMatrix into corresponding
					// positions
					forAll(lower, faceI)
					{
						activeExtLower[faceMap[faceI]] = activeLower[faceI];
					}
				}
				else
				{
					FatalErrorIn
					(
						"void extendedBlockLduMatrix<sphericalTensor>::"
						"mapOffDiagCoeffs\n"
						"(\n"
						"    const BlockLduMatrix<sphericalTensor>& blockLdum\n"
						")"
					) << "Problem between ordinary block matrix and extended"
						<< " block matrix lower coeffs type morphing."
						<< abort(FatalError);
				}
			}
		}
		else
		{
			// Get reference to faceMap in extended addressing
			const unallocLabelList& faceMap = extLduAddr_.faceMap();

			// Get number of extended faces
			const label nExtFaces = extLduAddr_.extendedUpperAddr().size();

			// Allocate extended upper and lower
			extendedUpperPtr_ = new TypeCoeffField(nExtFaces);
			TypeCoeffField& extUpper = *extendedUpperPtr_;

			extendedLowerPtr_ = new TypeCoeffField(nExtFaces);
			TypeCoeffField& extLower = *extendedLowerPtr_;

			// Get upper and lower coeffs from underlying lduMatrix
			const TypeCoeffField& upper = blockLdum.upper();
			const TypeCoeffField& lower = blockLdum.lower();

			// Assuming lower and upper have the same active type
			if (upper.activeType() == blockCoeffBase::SCALAR)
			{
				// Helper type definition
				typedef CoeffField<sphericalTensor>::scalarTypeField
					activeType;

				// Get references to fields
				const activeType& activeUpper = upper.asScalar();
				activeType& activeExtUpper = extUpper.asScalar();
				const activeType& activeLower = lower.asScalar();
				activeType& activeExtLower = extLower.asScalar();

				// Copy non-zero coeffs from basic lduMatrix into corresponding
				// positions
				forAll(upper, faceI)
				{
					activeExtUpper[faceMap[faceI]] = activeUpper[faceI];
					activeExtLower[faceMap[faceI]] = activeLower[faceI];
				}
			}
			else if (upper.activeType() == blockCoeffBase::LINEAR)
			{
				// Helper type definition
				typedef CoeffField<sphericalTensor>::linearTypeField
					activeType;

				// Get references to fields
				const activeType& activeUpper = upper.asLinear();
				activeType& activeExtUpper = extUpper.asLinear();
				const activeType& activeLower = lower.asLinear();
				activeType& activeExtLower = extLower.asLinear();

				// Copy non-zero coeffs from basic lduMatrix into corresponding
				// positions
				forAll(upper, faceI)
				{
					activeExtUpper[faceMap[faceI]] = activeUpper[faceI];
					activeExtLower[faceMap[faceI]] = activeLower[faceI];
				}
			}
			else
			{
				FatalErrorIn
				(
					"void extendedBlockLduMatrix<sphericalTensor>::"
					"mapOffDiagCoeffs\n"
					"(\n"
					"    const BlockLduMatrix<sphericalTensor>& blockLdum\n"
					")"
				) << "Problem between ordinary block matrix and extended"
					<< " block matrix upper/lower coeffs type morphing."
					<< abort(FatalError);
			}
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sphericalTensorExtendedBlockLduMatrix_CXX

