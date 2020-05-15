#include <polyMeshGenModifier.hxx>

#include <demandDrivenData.hxx>
#include <Pstream.hxx>
#include <PstreamReduceOps.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGenModifier::removeCells
	(
		const boolList& removeCell,
		const bool removeProcFaces
	)
	{
		Info << "Removing selected cells from the mesh" << endl;

		//mesh_.clearOut();

		faceListPMG& faces = mesh_.faces_;
		cellListPMG& cells = mesh_.cells_;

		if (removeCell.size() != cells.size())
		{
			Info << "Size of cells " << cells.size() << endl;
			Info << "Size of list for removal " << removeCell.size() << endl;
			FatalErrorIn
			(
				"void polyMeshGenModifier::removeCells(const boolList& removeCell)"
			) << "Incorrect number of entries in removeCell list!"
				<< abort(FatalError);
		}

		//- flip internal faces which will become boundary ones
		const labelList& owner = mesh_.owner();
		const labelList& neighbour = mesh_.neighbour();

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 40)
# endif
		forAll(faces, faceI)
		{
			if (neighbour[faceI] == -1)
			{
				faceI = faces.size();
				continue;
			}

			if (removeCell[owner[faceI]] && !removeCell[neighbour[faceI]])
				faces[faceI] = faces[faceI].reverseFace();
		}

		mesh_.clearOut();

		//- remove unwanted cells
		label nCells(0);
		labelLongList newCellLabel(cells.size(), -1);
		forAll(newCellLabel, cellI)
			if (!removeCell[cellI])
				newCellLabel[cellI] = nCells++;

		forAll(cells, cellI)
			if ((newCellLabel[cellI] != -1) && (newCellLabel[cellI] < cellI))
			{
				cells[newCellLabel[cellI]].transfer(cells[cellI]);
			}

		cells.setSize(nCells);

		//- update cell subsets in the mesh
		mesh_.updateCellSubsets(newCellLabel);

		reduce(nCells, sumOp<label>());
		Info << "New cells size " << nCells << endl;

		//- reorder positions of boundary faces
		//- this outs the newly-created bnd faces at the end of the list
		this->reorderBoundaryFaces();

		mesh_.clearOut();
		//- remove unused faces
		boolList removeFace(faces.size(), true);

# ifdef USE_OMP
# pragma omp parallel if( cells.size() > 1000 )
# endif
		{
# ifdef USE_OMP
# pragma omp for schedule(dynamic, 40)
# endif
			forAll(cells, cellI)
			{
				const cell& c = cells[cellI];

				forAll(c, fI)
					removeFace[c[fI]] = false;
			}

			if (Pstream::parRun() && !removeProcFaces)
			{
				const PtrList<processorBoundaryPatch>& procBoundaries =
					mesh_.procBoundaries_;

# ifdef USE_OMP
# pragma omp for
# endif
				for (label fI = procBoundaries[0].patchStart(); fI < faces.size(); ++fI)
					removeFace[fI] = false;
			}
		}

		mesh_.clearOut();

		this->removeFaces(removeFace);

		Info << "Finished removing selected cells from the mesh" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //