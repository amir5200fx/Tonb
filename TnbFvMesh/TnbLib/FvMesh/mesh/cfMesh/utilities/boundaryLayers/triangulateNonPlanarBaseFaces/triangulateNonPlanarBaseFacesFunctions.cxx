#include <triangulateNonPlanarBaseFaces.hxx>

#include <decomposeFaces.hxx>
#include <decomposeCells.hxx>
#include <helperFunctions.hxx>
#include <meshSurfacePartitioner.hxx>
#include <triangle.hxx>
#include <PstreamReduceOps.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

//#define DEBUGLayer

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool triangulateNonPlanarBaseFaces::findNonPlanarBoundaryFaces()
	{
		const pointFieldPMG& points = mesh_.points();
		const label nInternalFaces = mesh_.nInternalFaces();

		meshSurfacePartitioner mPart(mesh_);
		const meshSurfaceEngine& mse = mPart.surfaceEngine();
		const labelList& faceOwner = mse.faceOwners();
		const faceList::subList& bFaces = mse.boundaryFaces();

		bool hasInvalid(false);

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 50)
# endif
		forAll(bFaces, bfI)
		{
			const face& bf = bFaces[bfI];

			//- triangle shall not be decomposed, they are flat
			if (bf.size() == 3)
				continue;

			//- calculate min face diagonal
			scalar minDist(VGREAT);
			const point c = bf.centre(points);
			forAll(bf, pI)
			{
				minDist = tnbLib::min(minDist, tnbLib::mag(c - points[bf[pI]]));
			}

			forAll(bf, eI)
			{
				triangle<point, point> tri
				(
					points[bf[eI]],
					points[bf.nextLabel(eI)],
					c
				);

				const point triCentre = tri.centre();
				vector n = tri.normal();
				n /= (mag(n) + VSMALL);

				forAll(bf, pI)
				{
					const scalar d = (points[bf[pI]] - triCentre) & n;

					if (d > tol_ * minDist)
					{
						invertedCell_[faceOwner[bfI]] = true;

						decomposeFace_[nInternalFaces + bfI] = true;
						hasInvalid = true;
					}
				}
			}
		}

		reduce(hasInvalid, maxOp<bool>());

		return hasInvalid;
	}

	void triangulateNonPlanarBaseFaces::decomposeBoundaryFaces()
	{
		//- decompose base faces into triangles
		decomposeFaces triangulator(mesh_);
		triangulator.decomposeMeshFaces(decomposeFace_);
		const VRWGraph& newFacesFromFace = triangulator.newFacesForFace();

		//- update face subsets
		mesh_.updateFaceSubsets(newFacesFromFace);
	}

	void triangulateNonPlanarBaseFaces::decomposeCellsIntoPyramids()
	{
		decomposeCells sc(mesh_);
		sc.decomposeMesh(invertedCell_);
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //