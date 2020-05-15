#include <boundaryLayers.hxx>

#include <meshSurfaceEngine.hxx>
#include <decomposeCells.hxx>
#include <helperFunctions.hxx>
#include <HashSet.hxx>
#include <PstreamReduceOps.hxx>

#include <set>

//#define DEBUGLayer

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void boundaryLayers::checkTopologyOfBoundaryFaces(const labelList& patchLabels)
	{
		if (!patchWiseLayers_)
			return;

		Info << "Checking topology of boundary faces" << endl;

		labelHashSet usedPatches;
		forAll(patchLabels, i)
			usedPatches.insert(patchLabels[i]);

		//- create a set of patch pairs. These are pairs at which the layers
		//- shall be terminated
		std::set<std::pair<label, label> > terminatedPairs;
		forAll(treatPatchesWithPatch_, patchI)
		{
			const DynList<label>& otherPatches = treatPatchesWithPatch_[patchI];

			forAll(otherPatches, patchJ)
			{
				if (patchI == otherPatches[patchJ])
					continue;

				terminatedPairs.insert
				(
					std::make_pair
					(
						tnbLib::min(patchI, otherPatches[patchJ]),
						tnbLib::max(patchI, otherPatches[patchJ])
					)
				);
			}
		}

		bool changed;
		label nDecomposed(0);
		boolList decomposeCell(mesh_.cells().size(), false);

		do
		{
			changed = false;

			const meshSurfaceEngine& mse = this->surfaceEngine();
			const faceList::subList& bFaces = mse.boundaryFaces();
			const labelList& faceOwner = mse.faceOwners();
			const labelList& facePatches = mse.boundaryFacePatches();
			const VRWGraph& faceEdges = mse.faceEdges();
			const VRWGraph& edgeFaces = mse.edgeFaces();

			const Map<label>& otherProcPatch = mse.otherEdgeFacePatch();

			VRWGraph newBoundaryFaces;
			labelLongList newBoundaryOwners;
			labelLongList newBoundaryPatches;

			forAll(bFaces, bfI)
			{
				const face& bf = bFaces[bfI];
				const label fPatch = facePatches[bfI];

				if (!usedPatches.found(fPatch))
					continue;

				//- find patches of neighbour faces
				labelList neiPatches(bf.size());
				forAll(bf, eI)
				{
					const label beI = faceEdges(bfI, eI);

					if (edgeFaces.sizeOfRow(beI) == 2)
					{
						label neiFace = edgeFaces(beI, 0);
						if (neiFace == bfI)
							neiFace = edgeFaces(beI, 1);

						neiPatches[eI] = facePatches[neiFace];
					}
					else if (edgeFaces.sizeOfRow(beI) == 1)
					{
						//- edge is at a parallel boundary
						neiPatches[eI] = otherProcPatch[beI];
					}
				}

				//- find feature edges and check if the patches meeting there
				//- shall be treated together.
				bool storedFace(false);
				forAll(neiPatches, eI)
				{
					if (neiPatches[eI] == fPatch)
						continue;

					std::pair<label, label> pp
					(
						tnbLib::min(fPatch, neiPatches[eI]),
						tnbLib::max(fPatch, neiPatches[eI])
					);

					if (terminatedPairs.find(pp) == terminatedPairs.end())
						continue;

					//- create a new face from this edge and the neighbouring edges
					bool usePrev(false), useNext(false);
					if (neiPatches[neiPatches.rcIndex(eI)] == fPatch)
					{
						usePrev = true;
					}
					else
					{
						std::pair<label, label> ppPrev
						(
							tnbLib::min(fPatch, neiPatches[neiPatches.rcIndex(eI)]),
							tnbLib::max(fPatch, neiPatches[neiPatches.rcIndex(eI)])
						);

						if (terminatedPairs.find(ppPrev) == terminatedPairs.end())
							usePrev = true;
					}

					if (neiPatches[neiPatches.fcIndex(eI)] == fPatch)
					{
						useNext = true;
					}
					else
					{
						std::pair<label, label> ppNext
						(
							tnbLib::min(fPatch, neiPatches[neiPatches.fcIndex(eI)]),
							tnbLib::max(fPatch, neiPatches[neiPatches.fcIndex(eI)])
						);

						if (terminatedPairs.find(ppNext) == terminatedPairs.end())
							useNext = true;
					}

					DynList<edge> removeEdges;
					if (useNext && usePrev)
					{
						removeEdges.setSize(3);
						removeEdges[0] = bf.faceEdge(neiPatches.rcIndex(eI));
						removeEdges[1] = bf.faceEdge(eI);
						removeEdges[2] = bf.faceEdge(neiPatches.fcIndex(eI));
					}
					else if (useNext)
					{
						removeEdges.setSize(2);
						removeEdges[0] = bf.faceEdge(neiPatches.fcIndex(eI));
						removeEdges[1] = bf.faceEdge(eI);
					}
					else if (usePrev)
					{
						removeEdges.setSize(2);
						removeEdges[0] = bf.faceEdge(neiPatches.rcIndex(eI));
						removeEdges[1] = bf.faceEdge(eI);
					}

					const face cutFace = help::removeEdgesFromFace(bf, removeEdges);
					if (cutFace.size() > 2)
					{
						newBoundaryFaces.appendList(cutFace);
						newBoundaryOwners.append(faceOwner[bfI]);
						newBoundaryPatches.append(fPatch);
					}
					const face rFace = help::createFaceFromRemovedPart(bf, cutFace);
					if (rFace.size() > 2)
					{
						newBoundaryFaces.appendList(rFace);
						newBoundaryOwners.append(faceOwner[bfI]);
						newBoundaryPatches.append(fPatch);
					}

					if ((cutFace.size() > 2) && (rFace.size() > 2))
					{
						decomposeCell[faceOwner[bfI]] = true;
						changed = true;
						++nDecomposed;
					}

					storedFace = true;

					break;
				}

				if (!storedFace)
				{
					newBoundaryFaces.appendList(bf);
					newBoundaryOwners.append(faceOwner[bfI]);
					newBoundaryPatches.append(fPatch);
				}
			}

			//- Finally, replace the boundary faces
			reduce(changed, maxOp<bool>());

			if (changed)
			{
				polyMeshGenModifier meshModifier(mesh_);
				meshModifier.replaceBoundary
				(
					patchNames_,
					newBoundaryFaces,
					newBoundaryOwners,
					newBoundaryPatches
				);

				PtrList<boundaryPatch>& boundaries =
					meshModifier.boundariesAccess();
				forAll(boundaries, patchI)
					boundaries[patchI].patchType() = patchTypes_[patchI];

				clearOut();
			}

		} while (changed);

		//- decompose owner cells adjacent to the decomposed faces
		reduce(nDecomposed, sumOp<label>());

		if (nDecomposed != 0)
		{
			FatalError << "Critical. Not tested" << exit(FatalError);
			decomposeCells dc(mesh_);
			dc.decomposeMesh(decomposeCell);

			clearOut();
		}

		mesh_.write();
		Info << "Finished checking topology" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //