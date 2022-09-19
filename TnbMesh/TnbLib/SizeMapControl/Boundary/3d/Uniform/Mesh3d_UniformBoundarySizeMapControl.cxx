#include <Mesh3d_UniformBoundarySizeMapControl.hxx>

#include <BoundarySizeMap3d_UniformFaceTool.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::BoundarySizeMap3d_UniformFaceTool>
tnbLib::Mesh3d_UniformBoundarySizeMapControl::SelectMap(const word & theName) const
{
	auto iter = Maps().find(theName);
	if (iter IS_EQUAL Maps().end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map <" << theName << "> is not found." << endl
			<< abort(FatalError);
	}
	auto t = std::dynamic_pointer_cast<BoundarySizeMap3d_UniformFaceTool>(iter->second);
	Debug_Null_Pointer(t);
	return std::move(t);
}

void tnbLib::Mesh3d_UniformBoundarySizeMapControl::CreateSizeMap
(
	const word & theName,
	const std::shared_ptr<Cad_TModel>& theGeometry,
	const std::shared_ptr<BoundarySizeMap3d_UniformFaceTool_Info>& theInfo
)
{
	auto sizeMapTool = std::make_shared<BoundarySizeMap3d_UniformFaceTool>(References(), Domain(), theGeometry, theInfo);
	this->Import(theName, sizeMapTool);
}