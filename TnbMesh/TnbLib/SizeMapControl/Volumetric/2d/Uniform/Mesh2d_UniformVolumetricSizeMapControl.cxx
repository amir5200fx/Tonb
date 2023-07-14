#include <Mesh2d_UniformVolumetricSizeMapControl.hxx>

#include <Mesh2d_VolumeSizeMapTool.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::Mesh2d_VolumeSizeMapTool>
tnbLib::Mesh2d_UniformVolumetricSizeMapControl::SelectMap
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
	auto t = std::dynamic_pointer_cast<Mesh2d_VolumeSizeMapTool>(iter->second);
	Debug_Null_Pointer(t);
	return std::move(t);
}

void tnbLib::Mesh2d_UniformVolumetricSizeMapControl::CreateSizeMap
(
	const word& theName, 
	const std::shared_ptr<Cad2d_Plane>& theGeometry,
	const std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info>& theInfo
)
{
	auto sizeMapTool =
		std::make_shared<Mesh2d_VolumeSizeMapTool>
		(theGeometry, Domain(), this->References(), theInfo);
	this->Import(theName, sizeMapTool);
}