#include <Mesh_SizeMapControl.hxx>

#include <Mesh_SizeMapControl_Info.hxx>

const std::shared_ptr<tnbLib::Mesh_SizeMapControl_Info> tnbLib::Mesh_SizeMapControl_Base::DEFAULT_INFO =
std::make_shared<tnbLib::Mesh_SizeMapControl_Info>();

unsigned short tnbLib::Mesh_SizeMapControl_Base::verbose(0);

tnbLib::Mesh_SizeMapControl_Base::Mesh_SizeMapControl_Base()
	: theInfo_(DEFAULT_INFO)
{
	// empty body [7/18/2022 Amir]
}