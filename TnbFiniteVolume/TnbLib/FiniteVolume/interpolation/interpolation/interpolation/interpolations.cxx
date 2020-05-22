#include <interpolation.hxx>

#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
	// Define the constructor function hash tables

	defineTemplateRunTimeSelectionTable(interpolation<scalar>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<vector>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<sphericalTensor>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<symmTensor>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<symmTensor4thOrder>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<diagTensor>, dictionary);
	defineTemplateRunTimeSelectionTable(interpolation<tensor>, dictionary);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //