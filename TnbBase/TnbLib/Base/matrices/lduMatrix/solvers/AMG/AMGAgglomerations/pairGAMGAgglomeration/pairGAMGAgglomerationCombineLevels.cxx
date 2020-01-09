#include <pairGAMGAgglomeration.hxx>

#include <lduInterfaceFieldPtrsList.hxx>
#include <AMGInterface.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pairGAMGAgglomeration::combineLevels(const label curLevel)
{
	label prevLevel = curLevel - 1;

	// Set the previous level nCells to the current
	nCells_[prevLevel] = nCells_[curLevel];

	// Map the restrictAddressing from the coarser level into the previous
	// finer level

	const labelList& curResAddr = restrictAddressing_[curLevel];
	labelList& prevResAddr = restrictAddressing_[prevLevel];

	const labelList& curFaceResAddr = faceRestrictAddressing_[curLevel];
	labelList& prevFaceResAddr = faceRestrictAddressing_[prevLevel];

	forAll(prevFaceResAddr, i)
	{
		if (prevFaceResAddr[i] >= 0)
		{
			prevFaceResAddr[i] = curFaceResAddr[prevFaceResAddr[i]];
		}
		else
		{
			prevFaceResAddr[i] = -curResAddr[-prevFaceResAddr[i] - 1] - 1;
		}
	}

	// Delete the restrictAddressing for the coarser level
	faceRestrictAddressing_.set(curLevel, NULL);

	forAll(prevResAddr, i)
	{
		prevResAddr[i] = curResAddr[prevResAddr[i]];
	}

	// Delete the restrictAddressing for the coarser level
	restrictAddressing_.set(curLevel, NULL);


	// Delete the matrix addressing and coefficients from the previous level
	// and replace with the corresponding entried from the coarser level
	meshLevels_.set(prevLevel, meshLevels_.set(curLevel, NULL));

	// Same for the lduInterfaceFields taking care to delete the sub-entries
	// held on List<T*>
	const lduInterfacePtrsList& curInterLevel = interfaceLevels_[curLevel + 1];
	lduInterfacePtrsList& prevInterLevel = interfaceLevels_[prevLevel + 1];

	forAll(prevInterLevel, inti)
	{
		if (prevInterLevel.set(inti))
		{
			refCast<AMGInterface>(const_cast<lduInterface&>
				(
					prevInterLevel[inti]
					)).combine(refCast<const AMGInterface>(curInterLevel[inti]));

			delete curInterLevel(inti);
		}
	}

	interfaceLevels_.set(curLevel + 1, NULL);
}


// ************************************************************************* //