#include <createFundamentalSheets.hxx>

#include <demandDrivenData.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(createFundamentalSheets, 0);
	defineRunTimeSelectionTable(createFundamentalSheets, polyMeshGen);

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Construct from mesh, octree, regions for boundary vertices
	createFundamentalSheets::createFundamentalSheets
	(
		polyMeshGen& mesh,
		const bool createWrapperSheet
	)
		:
		mesh_(mesh),
		createWrapperSheet_(createWrapperSheet)
	{}

	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	createFundamentalSheets::~createFundamentalSheets()
	{}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //