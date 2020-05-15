#include <surfaceMorpherCells.hxx>

#include <demandDrivenData.hxx>

//#define DEBUGMorph

# ifdef DEBUGMorph
#include <sstream>
#include "polyMeshGenAddressing.H"
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void surfaceMorpherCells::replaceMeshBoundary()
	{
		wordList patchNames(1);
		patchNames[0] = "defaultFaces";

		polyMeshGenModifier(mesh_).replaceBoundary
		(
			patchNames,
			newBoundaryFaces_,
			newBoundaryOwners_,
			newBoundaryPatches_
		);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	surfaceMorpherCells::surfaceMorpherCells
	(
		polyMeshGen& mesh
	)
		:
		mesh_(mesh),
		nIntFaces_(0),
		boundaryVertex_(mesh.points().size()),
		cellFlags_(mesh.cells().size()),
		newBoundaryFaces_(),
		newBoundaryOwners_(),
		newBoundaryPatches_()
	{
	}

	surfaceMorpherCells::~surfaceMorpherCells()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void surfaceMorpherCells::morphMesh()
	{
		//- perform surface morphing
		bool changed;

# ifdef DEBUGMorph
		label iter(0);
# endif

		do
		{
			changed = false;
# ifdef DEBUGMorph
			Info << "Iteration " << ++iter << endl;
# endif

			findBoundaryVertices();

			findBoundaryCells();

			if (removeCellsWithAllVerticesAtTheBoundary())
			{
				changed = true;
				continue;
			}

			if (morphInternalFaces())
			{
				changed = true;
				continue;
			}

			if (morphBoundaryFaces())
			{
				changed = true;
				continue;
			}

# ifdef DEBUGMorph
			mesh_.write();
			mesh_.addressingData().checkMesh(true);
			fileName name("morphedMesh");
			std::ostringstream ss;
			ss << iter;
			name += ss.str();
			Info << "name " << name << endl;
			++iter;

			const cellListPMG& cells = mesh_.cells();
			const faceListPMG& faces = mesh_.faces();
			forAll(cells, cellI)
			{
				const cell& c = cells[cellI];

				const edgeList edges = c.edges(faces);
				List<direction> nAppearances(edges.size(), direction(0));

				forAll(c, fI)
				{
					const edgeList fEdges = faces[c[fI]].edges();

					forAll(fEdges, eI)
						forAll(edges, eJ)
						if (fEdges[eI] == edges[eJ])
						{
							++nAppearances[eJ];
							break;
						}
				}

				bool closed(true);
				forAll(nAppearances, eI)
					if (nAppearances[eI] != 2)
					{
						closed = false;
						Info << "Edge " << edges[eI] << " appears "
							<< label(nAppearances[eI]) << " times in cell "
							<< cellI << endl;
					}

				if (!closed)
				{
					Info << "Cell " << cellI << " consists of faces " << c << endl;
					forAll(c, fI)
						Info << "Face " << c[fI] << " is " << faces[c[fI]] << endl;
					FatalErrorIn
					(
						"void surfaceMorpherCells::morphMesh()"
					) << "Cell " << cellI << " is not topologically closed"
						<< abort(FatalError);
				}
			}
# endif

		} while (changed);

		polyMeshGenModifier(mesh_).removeUnusedVertices();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //