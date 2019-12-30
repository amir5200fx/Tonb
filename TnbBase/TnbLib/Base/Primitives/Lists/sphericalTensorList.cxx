#include <sphericalTensorList.hxx>

#include <token.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineCompoundTypeName(List<sphericalTensor>, sphericalTensorList);
	addCompoundToRunTimeSelectionTable(List<sphericalTensor>, sphericalTensorList);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //