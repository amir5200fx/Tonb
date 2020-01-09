#include <blockLduSmoothers.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarSmoother, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorSmoother, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorSmoother, 0);

	defineTemplateRunTimeSelectionTable(blockScalarSmoother, dictionary);
	defineTemplateRunTimeSelectionTable(blockVectorSmoother, dictionary);
	defineTemplateRunTimeSelectionTable(blockTensorSmoother, dictionary);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //