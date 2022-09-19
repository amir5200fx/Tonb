#include <BoundarySizeMap3d_UniformFaceTool.hxx>

#include <BoundarySizeMap3d_UniformFaceTool_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformFaceTool)
{
	ar & boost::serialization::base_object<BoundarySizeMap3d_FaceTool>(*this);

	ar & theInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::BoundarySizeMap3d_UniformFaceTool)
{
	ar & boost::serialization::base_object<BoundarySizeMap3d_FaceTool>(*this);

	ar & theInfo_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::BoundarySizeMap3d_UniformFaceTool);