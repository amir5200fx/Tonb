#include <IOLongListInstances.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineCompoundTypeName(IOLongList<label>, labelIOListPMG);
	defineCompoundTypeName(IOLongList<point>, pointIOFieldPMG);
	//defineCompoundTypeName(IOLongList<face>, faceIOListPMG);
	//defineCompoundTypeName(IOLongList<cell>, cellIOListPMG);
	//addCompoundToRunTimeSelectionTable(IOLongList<label>, labelIOLongList);

	defineTemplateTypeNameAndDebugWithName(labelIOListPMG, "labelList", 0);
	defineTemplateTypeNameAndDebugWithName(pointIOFieldPMG, "vectorField", 0);
	//defineTemplateTypeNameAndDebugWithName(faceIOListPMG, "faceList", 0);
	//defineTemplateTypeNameAndDebugWithName(cellIOListPMG, "cellList", 0);
}

// ************************************************************************* //