#include <Mesh2d_UniformBoundarySizeMapControl.hxx>

#include <BoundarySizeMap2d_UniformSegmentTool.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::BoundarySizeMap2d_UniformSegmentTool>
tnbLib::Mesh2d_UniformBoundarySizeMapControl::SelectMap
(
	const word& theName
) const
{
	auto iter = Maps().find(theName);
	if (iter IS_EQUAL Maps().end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map <" << theName << "> is not found." << endl
			<< abort(FatalError);
	}
	auto t = std::dynamic_pointer_cast<BoundarySizeMap2d_UniformSegmentTool>(iter->second);
	Debug_Null_Pointer(t);
	return std::move(t);
}

void tnbLib::Mesh2d_UniformBoundarySizeMapControl::CreateSizeMap
(
	const word& theName,
	const std::shared_ptr<Cad2d_Plane>& theGeometry,
	const std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info>& theInfo
)
{
	auto sizeMapTool =
		std::make_shared<BoundarySizeMap2d_UniformSegmentTool>
		(References(), Domain(), Cloud(), theGeometry, theInfo);
	this->Import(theName, sizeMapTool);
}