#include <Mesh_SurfaceSizeValues.hxx>

const Standard_Real tnbLib::Mesh_SurfaceSizeValues::DEFAULT_MIN_SIZE = 20.0;
const Standard_Real tnbLib::Mesh_SurfaceSizeValues::DEFAULT_TARGET_SIZE = 100.0;


tnbLib::Mesh_SurfaceSizeValues::Mesh_SurfaceSizeValues()
	: theMinSize_(DEFAULT_MIN_SIZE)
	, theTargetSize_(DEFAULT_TARGET_SIZE)
{
	theSizeMethod_ = Mesh_SizeMethodInfo::minAndTerget;
	theRelativeAbsolute_ = Mesh_RelativeAbsoluteInfo::relativeToBase;
}