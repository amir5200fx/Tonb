#include <topologicalCleaner.hxx>

#include <demandDrivenData.hxx>
#include <decomposeFaces.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

//#define DEBUGCleaner

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void topologicalCleaner::checkNonConsecutiveBoundaryVertices()
	{
		Info << "Checking for invalid face connections" << endl;

		const faceListPMG& faces = mesh_.faces();
		const labelList& owner = mesh_.owner();
		const cellListPMG& cells = mesh_.cells();

		const label nIntFaces = mesh_.nInternalFaces();

		boolList decomposeFace(faces.size(), false);
		bool changed(false);

		const PtrList<boundaryPatch>& boundaries = mesh_.boundaries();
		forAll(boundaries, patchI)
		{
			const label start = boundaries[patchI].patchStart();
			const label end = start + boundaries[patchI].patchSize();

			for (label faceI = start; faceI < end; ++faceI)
			{
				const face& bf = faces[faceI];

# ifdef DEBUGCleaner
				Info << "Checking boundary face " << faceI << " with vertices "
					<< bf << endl;
# endif

				const label bfsize = bf.size();

				const cell& c = cells[owner[faceI]];

				forAll(c, fI)
					if (
						(c[fI] < nIntFaces) ||
						(mesh_.faceIsInProcPatch(c[fI]) != -1)
						)
					{
						const face& f = faces[c[fI]];

						DynList<label> shN;

						forAll(bf, pI)
							forAll(f, pJ)
							if (bf[pI] == f[pJ])
							{
								shN.append(pI);
							}

# ifdef DEBUGCleaner
						Info << "Shared vertices with internal face " << f
							<< " are " << shN << endl;
# endif

						if (shN.size() > 2)
						{
# ifdef DEBUGCleaner
							Info << "1. Face has to be split" << endl;
# endif

							decomposeFace[faceI] = true;
							decomposeCell_[owner[faceI]] = true;
							changed = true;
						}
						else if (shN.size() == 2)
						{
							if (!(
								(shN[0] == ((shN[1] + 1) % bfsize)) ||
								(shN[0] == ((shN[1] + bfsize - 1) % bfsize))
								)
								)
							{
# ifdef DEBUGCleaner
								Info << "2. Face has to be split" << endl;
# endif

								decomposeFace[faceI] = true;
								decomposeCell_[owner[faceI]] = true;
								changed = true;
							}
						}
					}
			}
		}

		if (Pstream::parRun())
			reduce(changed, maxOp<bool>());

		if (changed)
		{
			changed_ = true;
			decomposeFaces(mesh_).decomposeMeshFaces(decomposeFace);
		}

		Info << "Finished checking for invalid face connections" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //