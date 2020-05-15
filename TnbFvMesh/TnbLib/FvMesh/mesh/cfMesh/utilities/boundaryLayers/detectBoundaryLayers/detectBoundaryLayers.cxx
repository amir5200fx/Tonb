#include <detectBoundaryLayers.hxx>

#include <meshSurfacePartitioner.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	detectBoundaryLayers::detectBoundaryLayers
	(
		const meshSurfacePartitioner& meshSurface,
		const bool is2DMesh
	)
		:
		meshSurface_(meshSurface),
		nFirstLayers_(0),
		layerAtBndFace_(),
		layerAtPatch_(),
		hairEdges_(),
		hairEdgesAtBoundaryPoint_(),
		is2DMesh_(is2DMesh)
	{
		Info << "Detecting layers" << endl;
		analyseLayers();

		Info << "Generating hair edges" << endl;
		generateHairEdges();

		Info << "Finished with bnd layer detection" << endl;
	}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	detectBoundaryLayers::~detectBoundaryLayers()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //