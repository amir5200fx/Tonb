#include <Mesh3d_UniformFeatureSizeMapControl.hxx>

#include <BoundarySizeMap3d_UniformSegmentTool.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::BoundarySizeMap3d_UniformSegmentTool> 
tnbLib::Mesh3d_UniformFeatureSizeMapControl::SelectMap
(
	const word & theName
) const
{
	auto iter = Maps().find(theName);
	if (iter IS_EQUAL Maps().end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map <" << theName << "> is not found." << endl
			<< abort(FatalError);
	}
	auto t = std::dynamic_pointer_cast<BoundarySizeMap3d_UniformSegmentTool>(iter->second);
	Debug_Null_Pointer(t);
	return std::move(t);
}

void tnbLib::Mesh3d_UniformFeatureSizeMapControl::CreateSizeMap
(
	const word & theName,
	const std::shared_ptr<Cad_TModel>& theGeometry
)
{
	auto sizeMapTool = std::make_shared<BoundarySizeMap3d_UniformSegmentTool>(References(), Domain(), theGeometry);
	this->Import(theName, sizeMapTool);
}