#include <boundaryLayers.hxx>

#include <meshSurfaceEngine.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void boundaryLayers::addWrapperLayer()
	{
		createOTopologyLayers();

		if (treatedPatch_[0]) return;

		const meshSurfaceEngine& mse = surfaceEngine();

		const labelList& bPoints = mse.boundaryPoints();

		boolList treatPatches(mesh_.boundaries().size(), true);

		labelLongList newLabelForVertex(nPoints_, -1);

		pointFieldPMG& points = mesh_.points();
		points.setSize(points.size() + bPoints.size());
		forAll(bPoints, bpI)
		{
			points[nPoints_] = points[bPoints[bpI]];
			newLabelForVertex[bPoints[bpI]] = nPoints_++;
		}

		createNewFacesAndCells(treatPatches);

		forAll(treatPatches, patchI)
			if (treatPatches[patchI])
				treatedPatch_[patchI] = true;

		//- delete surface engine
		clearOut();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //