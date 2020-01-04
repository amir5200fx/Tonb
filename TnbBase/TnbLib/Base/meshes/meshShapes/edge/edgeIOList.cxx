#include <edgeIOList.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<edge>, edgeList);
	addCompoundToRunTimeSelectionTable(List<edge>, edgeList);

	defineTemplateTypeNameAndDebugWithName(edgeIOList, "edgeList", 0);
}

// ************************************************************************* //