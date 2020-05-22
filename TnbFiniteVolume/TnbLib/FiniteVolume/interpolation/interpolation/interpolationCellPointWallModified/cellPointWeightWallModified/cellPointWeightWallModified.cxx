#include <cellPointWeightWallModified.hxx>

#include <polyMesh.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellPointWeightWallModified::cellPointWeightWallModified
(
	const polyMesh& mesh,
	const vector& position,
	const label cellIndex,
	const label faceIndex
)
	:
	cellPointWeight(mesh, position, cellIndex, faceIndex)
{
	if (faceIndex < 0)
	{
		findTetrahedron(mesh, position, cellIndex);
	}
	else
	{
		const polyBoundaryMesh& bm = mesh.boundaryMesh();
		label patchI = bm.whichPatch(faceIndex);
		if (patchI != -1)
		{
			if (bm[patchI].isWall())
			{
				// Apply cell centre value wall faces
				weights_[0] = 0.0;
				weights_[1] = 0.0;
				weights_[2] = 0.0;
				weights_[3] = 1.0;
			}
		}
		else
		{
			// Interpolate
			findTriangle(mesh, position, faceIndex);
		}
	}
}


// ************************************************************************* //