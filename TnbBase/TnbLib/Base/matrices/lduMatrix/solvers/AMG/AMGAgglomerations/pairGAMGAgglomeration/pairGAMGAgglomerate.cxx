#include <pairGAMGAgglomeration.hxx>

#include <scalarField.hxx>
#include <lduAddressing.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::pairGAMGAgglomeration::agglomerate
(
	label& nCoarseCells,
	const lduAddressing& fineMatrixAddressing,
	const scalarField& faceWeights
)
{
	const label nFineCells = fineMatrixAddressing.size();

	const unallocLabelList& upperAddr = fineMatrixAddressing.upperAddr();
	const unallocLabelList& lowerAddr = fineMatrixAddressing.lowerAddr();

	// For each cell calculate faces
	labelList cellFaces(upperAddr.size() + lowerAddr.size());
	labelList cellFaceOffsets(nFineCells + 1);

	// memory management
	{
		labelList nNbrs(nFineCells, 0);

		forAll(upperAddr, facei)
		{
			nNbrs[upperAddr[facei]]++;
		}

		forAll(lowerAddr, facei)
		{
			nNbrs[lowerAddr[facei]]++;
		}

		cellFaceOffsets[0] = 0;
		forAll(nNbrs, celli)
		{
			cellFaceOffsets[celli + 1] = cellFaceOffsets[celli] + nNbrs[celli];
		}

		// reset the whole list to use as counter
		nNbrs = 0;

		forAll(upperAddr, facei)
		{
			cellFaces
				[
					cellFaceOffsets[upperAddr[facei]] + nNbrs[upperAddr[facei]]
				] = facei;

			nNbrs[upperAddr[facei]]++;
		}

		forAll(lowerAddr, facei)
		{
			cellFaces
				[
					cellFaceOffsets[lowerAddr[facei]] + nNbrs[lowerAddr[facei]]
				] = facei;

			nNbrs[lowerAddr[facei]]++;
		}
	}


	// go through the faces and create clusters

	tmp<labelField> tcoarseCellMap(new labelField(nFineCells, -1));
	labelField& coarseCellMap = tcoarseCellMap();

	nCoarseCells = 0;

	for (label celli = 0; celli < nFineCells; celli++)
	{
		if (coarseCellMap[celli] < 0)
		{
			label matchFaceNo = -1;
			scalar maxFaceWeight = -GREAT;

			// check faces to find ungrouped neighbour with largest face weight
			for
				(
					label faceOs = cellFaceOffsets[celli];
					faceOs < cellFaceOffsets[celli + 1];
					faceOs++
					)
			{
				label facei = cellFaces[faceOs];

				// I don't know whether the current cell is owner or neighbour.
				// Therefore I'll check both sides
				if
					(
						coarseCellMap[upperAddr[facei]] < 0
						&& coarseCellMap[lowerAddr[facei]] < 0
						&& faceWeights[facei] > maxFaceWeight
						)
				{
					// Match found. Pick up all the necessary data
					matchFaceNo = facei;
					maxFaceWeight = faceWeights[facei];
				}
			}

			if (matchFaceNo >= 0)
			{
				// Make a new group
				coarseCellMap[upperAddr[matchFaceNo]] = nCoarseCells;
				coarseCellMap[lowerAddr[matchFaceNo]] = nCoarseCells;
				nCoarseCells++;
			}
			else
			{
				// No match. Find the best neighbouring cluster and
				// put the cell there
				label clusterMatchFaceNo = -1;
				scalar clusterMaxFaceCoeff = -GREAT;

				for
					(
						label faceOs = cellFaceOffsets[celli];
						faceOs < cellFaceOffsets[celli + 1];
						faceOs++
						)
				{
					label facei = cellFaces[faceOs];

					if (faceWeights[facei] > clusterMaxFaceCoeff)
					{
						clusterMatchFaceNo = facei;
						clusterMaxFaceCoeff = faceWeights[facei];
					}
				}

				if (clusterMatchFaceNo >= 0)
				{
					// Add the cell to the best cluster
					coarseCellMap[celli] = max
					(
						coarseCellMap[upperAddr[clusterMatchFaceNo]],
						coarseCellMap[lowerAddr[clusterMatchFaceNo]]
					);
				}
			}
		}
	}


	// Check that all cells are part of clusters,
	// if not create single-cell "clusters" for each
	for (label celli = 0; celli < nFineCells; celli++)
	{
		if (coarseCellMap[celli] < 0)
		{
			coarseCellMap[celli] = nCoarseCells;
			nCoarseCells++;
		}
	}

	// Reverese the map ordering to improve the next level of agglomeration
	// (doesn't always help and is sometimes detrimental)
	nCoarseCells--;

	forAll(coarseCellMap, celli)
	{
		coarseCellMap[celli] = nCoarseCells - coarseCellMap[celli];
	}

	nCoarseCells++;

	return tcoarseCellMap;
}


void tnbLib::pairGAMGAgglomeration::agglomerate
(
	const lduMesh& mesh,
	const scalarField& faceWeights
)
{
	// Get the finest-level interfaces from the mesh
	interfaceLevels_.set
	(
		0,
		new lduInterfacePtrsList(mesh.interfaces())
	);

	// Start geometric agglomeration from the given faceWeights
	scalarField* faceWeightsPtr = const_cast<scalarField*>(&faceWeights);

	// Agglomerate until the required number of cells in the coarsest level
	// is reached

	label nPairLevels = 0;
	label nCreatedLevels = 0;

	while (nCreatedLevels < maxLevels_ - 1)
	{
		label nCoarseCells = -1;

		tmp<labelField> finalAgglomPtr = agglomerate
		(
			nCoarseCells,
			meshLevel(nCreatedLevels).lduAddr(),
			*faceWeightsPtr
		);

		if (continueAgglomerating(nCoarseCells))
		{
			nCells_[nCreatedLevels] = nCoarseCells;
			restrictAddressing_.set(nCreatedLevels, finalAgglomPtr);
		}
		else
		{
			break;
		}

		agglomerateLduAddressing(nCreatedLevels);

		// Agglomerate the faceWeights field for the next level
		{
			scalarField* aggFaceWeightsPtr
			(
				new scalarField
				(
					meshLevels_[nCreatedLevels].upperAddr().size(),
					0.0
				)
			);

			restrictFaceField
			(
				*aggFaceWeightsPtr,
				*faceWeightsPtr,
				nCreatedLevels
			);

			if (nCreatedLevels)
			{
				delete faceWeightsPtr;
			}

			faceWeightsPtr = aggFaceWeightsPtr;
		}

		if (nPairLevels % mergeLevels_)
		{
			combineLevels(nCreatedLevels);
		}
		else
		{
			nCreatedLevels++;
		}

		nPairLevels++;
	}

	// Shrink the storage of the levels to those created
	compactLevels(nCreatedLevels);

	// Delete temporary geometry storage
	if (nCreatedLevels)
	{
		delete faceWeightsPtr;
	}
}


// ************************************************************************* //