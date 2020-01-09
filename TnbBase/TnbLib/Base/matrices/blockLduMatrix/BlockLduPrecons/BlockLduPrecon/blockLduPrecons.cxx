#include <blockLduPrecons.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineNamedTemplateTypeNameAndDebug(blockScalarPrecon, 0);
	defineNamedTemplateTypeNameAndDebug(blockVectorPrecon, 0);
	defineNamedTemplateTypeNameAndDebug(blockTensorPrecon, 0);

	defineTemplateRunTimeSelectionTable(blockScalarPrecon, dictionary);
	defineTemplateRunTimeSelectionTable(blockVectorPrecon, dictionary);
	defineTemplateRunTimeSelectionTable(blockTensorPrecon, dictionary);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //