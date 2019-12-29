#include <labelIOList.hxx>

#include <token.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<label>, labelList);
	addCompoundToRunTimeSelectionTable(List<label>, labelList);

	defineTemplateTypeNameAndDebugWithName(labelIOList, "labelList", 0);
	defineTemplateTypeNameAndDebugWithName(labelListIOList, "labelListList", 0);
}

// ************************************************************************* //