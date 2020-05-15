#include <meshSurfaceEdgeExtractor.hxx>

#include <demandDrivenData.hxx>

// #define DEBUGSearch

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh, octree, regions for boundary vertices
	meshSurfaceEdgeExtractor::meshSurfaceEdgeExtractor
	(
		polyMeshGen& mesh,
		const meshOctree& octree,
		const labelList& pointRegion
	)
		:
		mesh_(mesh),
		nPoints_(mesh.points().size()),
		boundaryCell_(mesh.cells().size(), false),
		nFacesInCell_(mesh.cells().size(), direction(0)),
		meshOctree_(octree),
		pointRegions_(pointRegion.size())
	{
		forAll(pointRegion, pointI)
			if (pointRegion[pointI] != -1)
				pointRegions_.append(pointI, pointRegion[pointI]);

		createEdgeVertices();

		removeOldBoundaryFaces();

		createBoundaryFaces();
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	meshSurfaceEdgeExtractor::~meshSurfaceEdgeExtractor()
	{
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void meshSurfaceEdgeExtractor::removeOldBoundaryFaces()
	{
		const labelList neighbour_ = mesh_.neighbour();
		polyMeshGenModifier meshModifier_(mesh_);
		cellListPMG& cells_ = meshModifier_.cellsAccess();

		forAll(cells_, cellI)
		{
			const cell& c = cells_[cellI];

			cell newC(c);

			forAll(c, fI)
				if (neighbour_[c[fI]] != -1)
				{
					boundaryCell_[cellI] = true;
					newC[nFacesInCell_[cellI]++] = c[fI];
				}

			if (nFacesInCell_[cellI] < direction(c.size()))
			{
				newC.setSize(nFacesInCell_[cellI]);

				cells_[cellI] = newC;
			};
		}

		PtrList<boundaryPatch>& boundaries = meshModifier_.boundariesAccess();
		boundaries.setSize(1);
		boundaries[0].patchSize() = 0;
		meshModifier_.facesAccess().setSize(boundaries[0].patchStart());
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //