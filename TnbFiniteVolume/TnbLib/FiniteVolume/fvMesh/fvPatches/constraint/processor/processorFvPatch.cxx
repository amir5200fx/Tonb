#include <processorFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(processorFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, processorFvPatch, polyPatch);


	// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

	void processorFvPatch::makeWeights(scalarField& w) const
	{
		if (Pstream::parRun())
		{
			// The face normals point in the opposite direction on the other side

			// Note: mag in the dot-product.
			// For all valid meshes, the non-orthogonality will be less than
			// 90 deg and the dot-product will be positive.  For invalid
			// meshes (d & s <= 0), this will stabilise the calculation
			// but the result will be poor.  HJ, 24/Aug/2011
			scalarField neighbFaceCentresCn =
				mag
				(
				(
					procPolyPatch_.neighbFaceAreas() /
					(mag(procPolyPatch_.neighbFaceAreas()) + VSMALL)
					)
					& (
						procPolyPatch_.neighbFaceCentres()
						- procPolyPatch_.neighbFaceCellCentres()
						)
				);

			w = neighbFaceCentresCn / (mag(nf() & fvPatch::delta())
				+ neighbFaceCentresCn);
		}
		else
		{
			w = 1.0;
		}
	}


	void processorFvPatch::makeDeltaCoeffs(scalarField& dc) const
	{
		if (Pstream::parRun())
		{
			vectorField d = delta();

			// Stabilised form for bad meshes.  HJ, 24/Aug/2011
			dc = 1.0 / max((nf() & d), 0.05*mag(d));
		}
		else
		{
			dc = 1.0 / (nf() & fvPatch::delta());
		}
	}


	tmp<vectorField> processorFvPatch::delta() const
	{
		if (Pstream::parRun())
		{
			// To the transformation if necessary
			if (parallel())
			{
				return
					fvPatch::delta()
					- (
						procPolyPatch_.neighbFaceCentres()
						- procPolyPatch_.neighbFaceCellCentres()
						);
			}
			else
			{
				return
					fvPatch::delta()
					- transform
					(
						forwardT(),
						(
							procPolyPatch_.neighbFaceCentres()
							- procPolyPatch_.neighbFaceCellCentres()
							)
					);
			}
		}
		else
		{
			return fvPatch::delta();
		}
	}


	tmp<labelField> processorFvPatch::interfaceInternalField
	(
		const unallocLabelList& internalData
	) const
	{
		return patchInternalField(internalData);
	}


	void processorFvPatch::initTransfer
	(
		const Pstream::commsTypes commsType,
		const unallocLabelList& interfaceData
	) const
	{
		send(commsType, interfaceData);
	}


	tmp<labelField> processorFvPatch::transfer
	(
		const Pstream::commsTypes commsType,
		const unallocLabelList&
	) const
	{
		return receive<label>(commsType, this->size());
	}


	void processorFvPatch::initInternalFieldTransfer
	(
		const Pstream::commsTypes commsType,
		const unallocLabelList& iF
	) const
	{
		send(commsType, patchInternalField(iF)());
	}


	tmp<labelField> processorFvPatch::internalFieldTransfer
	(
		const Pstream::commsTypes commsType,
		const unallocLabelList&
	) const
	{
		return receive<label>(commsType, this->size());
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //