#include <triSurfaceDetectFeatureEdges.hxx>

#include <demandDrivenData.hxx>
#include <helperFunctions.hxx>
#include <triSurfModifier.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	triSurfaceDetectFeatureEdges::triSurfaceDetectFeatureEdges
	(
		triSurf& surface,
		const scalar angleDeviation
	)
		:
		surf_(surface),
		featureEdges_(surf_.edges().size(), direction(0)),
		angleTolerance_(angleDeviation)
	{
		if (Pstream::parRun())
			FatalError << "Feature edges detection does not run in parallel"
			<< exit(FatalError);

		detectFeatureEdgesAngleCriterion();
	}

	triSurfaceDetectFeatureEdges::~triSurfaceDetectFeatureEdges()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	void triSurfaceDetectFeatureEdges::detectFeatureEdges()
	{
		const edgeLongList& edges = surf_.edges();
		triSurfModifier surfMod(surf_);
		edgeLongList& featureEdges = surfMod.featureEdgesAccess();
		featureEdges.clear();

		forAll(featureEdges_, eI)
		{
			if (featureEdges_[eI])
				featureEdges.append(edges[eI]);
		}
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //