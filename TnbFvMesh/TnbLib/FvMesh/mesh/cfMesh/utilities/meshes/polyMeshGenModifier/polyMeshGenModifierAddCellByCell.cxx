#include <polyMeshGenModifierAddCellByCell.hxx>

#include <demandDrivenData.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	polyMeshGenModifierAddCellByCell::polyMeshGenModifierAddCellByCell
	(
		polyMeshGen& mesh
	)
		:
		polyMeshGenModifier(mesh),
		nFaces_(mesh.faces().size()),
		newFaces_(nFaces_),
		nCells_(mesh.cells().size()),
		newCells_(nCells_)
	{
		this->pointFaces();
		faceListPMG& faces = this->facesAccess();
		forAll(faces, faceI)
			newFaces_[faceI].transfer(faces[faceI]);

		cellListPMG& cells = this->cellsAccess();
		forAll(cells, cellI)
			newCells_[cellI].transfer(cells[cellI]);
	};

	// Destructor
	polyMeshGenModifierAddCellByCell::~polyMeshGenModifierAddCellByCell()
	{
		faceListPMG& faces = this->facesAccess();
		faces.setSize(nFaces_);
		forAll(faces, faceI)
			faces[faceI].transfer(newFaces_[faceI]);

		cellListPMG& cells = this->cellsAccess();
		cells.setSize(newCells_.size());
		forAll(cells, cellI)
			cells[cellI].transfer(newCells_[cellI]);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void polyMeshGenModifierAddCellByCell::addCell(const faceList& cellFaces)
	{
		cell c(cellFaces.size());

		VRWGraph& pointFaces = this->pointFaces();

		forAll(cellFaces, faceI)
		{
			const face& f = cellFaces[faceI];

			const label pointI = f[0];

			label fLabel(-1);
			forAllRow(pointFaces, pointI, pfI)
			{
				const label faceI = pointFaces(pointI, pfI);

				if (newFaces_[faceI] == f)
				{
					fLabel = faceI;
					break;
				}
			}

			if (fLabel == -1)
			{
				newFaces_.append(f);
				c[faceI] = nFaces_;
				forAll(f, pI)
					pointFaces.append(f[pI], nFaces_);

				++nFaces_;
			}
			else
			{
				c[faceI] = fLabel;
			}
		}

		newCells_.append(c);
		++nCells_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //