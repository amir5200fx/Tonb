#include <Mesh_SizeMapControl.hxx>

#include <Mesh_SizeMapControl_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_SizeMapControl_Base)
{
	ar & theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_SizeMapControl_Base)
{
	ar & theInfo_;
}