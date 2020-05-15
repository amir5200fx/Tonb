#include <triSurfaceDetectFeatureEdges.hxx>

#include <helperFunctions.hxx>
#include <demandDrivenData.hxx>
#include <labelPair.hxx>

# ifdef USE_OMP
#include <omp.h>
# endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceDetectFeatureEdges::detectFeatureEdgesAngleCriterion()
	{
		const scalar tol = tnbLib::cos(angleTolerance_*M_PI / 180.0);

		const vectorField& normals = surf_.facetNormals();

		const VRWGraph& edgeFaces = surf_.edgeFacets();

# ifdef USE_OMP
# pragma omp parallel for schedule(dynamic, 40)
# endif
		forAll(edgeFaces, edgeI)
		{
			const constRow eFaces = edgeFaces[edgeI];

			if (edgeFaces.sizeOfRow(edgeI) != 2)
			{
				featureEdges_[edgeI] |= 8;
				continue;
			}

			scalar cosAngle =
				(normals[eFaces[0]] & normals[eFaces[1]]) /
				(mag(normals[eFaces[0]]) * mag(normals[eFaces[1]]) + VSMALL);

			//- check the orientation of triangles at this edge
			//- check the sign of the angle if the orientation  is not consistent
			const labelledTri& tri0 = surf_[edgeFaces(edgeI, 0)];
			const labelledTri& tri1 = surf_[edgeFaces(edgeI, 1)];
			DynList<labelPair> sharedIndices;
			forAll(tri0, i)
			{
				forAll(tri1, j)
				{
					if (tri0[i] == tri1[j])
						sharedIndices.append(labelPair(i, j));
				}
			}

			if (sharedIndices.size() == 2)
			{
				const labelPair& pair0 = sharedIndices[0];
				const labelPair& pair1 = sharedIndices[1];
				if (((pair0.first() + 1) % 3) == pair1.first())
				{
					if ((pair0.second() + 1) % 3 == pair1.second())
						cosAngle *= -1.0;
				}
				else
				{
					if ((pair1.second() + 1) % 3 == pair0.second())
						cosAngle *= -1.0;
				}
			}

			if (cosAngle < tol)
				featureEdges_[edgeI] |= 1;
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //