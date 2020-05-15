#include <cartesianMeshExtractor.hxx>

#include <demandDrivenData.hxx>
#include <decomposeFaces.hxx>
#include <decomposeCells.hxx>
#include <hexMatcher.hxx>
#include <PstreamReduceOps.hxx>

//#define DEBUGMesh

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void cartesianMeshExtractor::decomposeSplitHexesIntoTetsAndPyramids()
	{
		if (!decomposeSplitHexes_) return;

		Info << "Decomposing split-hex cells" << endl;

		const faceListPMG& faces = mesh_.faces();

		//- decompose faces which have more than 4 vertices
		boolList decompose(faces.size(), false);

		label nDecomposed(0);
		forAll(faces, faceI)
		{
			if (faces[faceI].size() > 4)
			{
				++nDecomposed;

				decompose[faceI] = true;
			}
		}

		reduce(nDecomposed, sumOp<label>());

		Info << "Decomposing " << nDecomposed
			<< " faces with more than 4 vertices" << endl;

		if (nDecomposed != 0)
		{
			//- decompose marked faces into triangles
			decomposeFaces(mesh_).decomposeMeshFaces(decompose);
		}

		//- decompose cells with 24 faces
		const cellListPMG& cells = mesh_.cells();
		decompose.setSize(cells.size());
		decompose = false;

		hexMatcher hex;
		forAll(cells, cellI)
		{
			if (!hex.matchShape(true, faces, mesh_.owner(), cellI, cells[cellI]))
			{
				++nDecomposed;
				decompose[cellI] = true;
			}
		}

		reduce(nDecomposed, sumOp<label>());

		Info << "Decomposing " << nDecomposed
			<< " cells into tetrahedra and pyramids" << endl;

		if (nDecomposed)
		{
			//- decompose marked cells into tets and pyramids
			decomposeCells dc(mesh_);
			dc.decomposeMesh(decompose);
		}

		Info << "Finished decomposing split-hex cells" << endl;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //