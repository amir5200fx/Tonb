#include <polyMeshGenAddressing.hxx>

#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(polyMeshGenAddressing, 0);

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	polyMeshGenAddressing::polyMeshGenAddressing(const polyMeshGenCells& mesh)
		:
		mesh_(mesh),
		edgesPtr_(NULL),
		ccPtr_(NULL),
		ecPtr_(NULL),
		pcPtr_(NULL),
		efPtr_(NULL),
		pfPtr_(NULL),

		cePtr_(NULL),
		fePtr_(NULL),
		pePtr_(NULL),
		ppPtr_(NULL),
		cpPtr_(NULL),
		cellCentresPtr_(NULL),
		faceCentresPtr_(NULL),
		cellVolumesPtr_(NULL),
		faceAreasPtr_(NULL),
		globalPointLabelPtr_(NULL),
		globalFaceLabelPtr_(NULL),
		globalCellLabelPtr_(NULL),
		globalEdgeLabelPtr_(NULL),
		pProcsPtr_(NULL),
		globalToLocalPointAddressingPtr_(NULL),
		pointNeiProcsPtr_(NULL),
		eProcsPtr_(NULL),
		globalToLocalEdgeAddressingPtr_(NULL),
		edgeNeiProcsPtr_(NULL)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	polyMeshGenAddressing::~polyMeshGenAddressing()
	{
		clearAll();
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //