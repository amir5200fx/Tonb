#include <Mesh_SizeMapControl_Info.hxx>

#include <GeoMesh_Background_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_SizeMapControl_Info)
{
	ar & theMaxUnbalancing_;
	ar & theTol_;
	ar & theHvCorrInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_SizeMapControl_Info)
{
	ar & theMaxUnbalancing_;
	ar & theTol_;
	ar & theHvCorrInfo_;
}