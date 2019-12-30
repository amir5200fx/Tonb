#include <wordIOList.hxx>

#include <token.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(List<word>, wordList);
	addCompoundToRunTimeSelectionTable(List<word>, wordList);

	defineTemplateTypeNameAndDebugWithName(wordIOList, "wordList", 0);
	defineTemplateTypeNameAndDebugWithName(wordListIOList, "wordListList", 0);
}

// ************************************************************************* //