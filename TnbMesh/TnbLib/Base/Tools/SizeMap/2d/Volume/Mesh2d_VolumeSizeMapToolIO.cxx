#include <Mesh2d_VolumeSizeMapTool.hxx>

#include <Mesh2d_VolumeSizeMapTool_Info.hxx>
#include <Mesh2d_SizeMapVolume.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_VolumeSizeMapTool)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapTool>(*this);
	ar& theVolumes_;
	ar& theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_VolumeSizeMapTool)
{
	ar& boost::serialization::base_object<Mesh2d_SizeMapTool>(*this);
	ar& theVolumes_;
	ar& theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_VolumeSizeMapTool)