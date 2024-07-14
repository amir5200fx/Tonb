#include <Mesh2d_SizeMapControl.hxx>

#include <Cad2d_Plane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_SizeMapTool.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Geo2d_SegmentCloud.hxx>
#include <Entity2d_Box.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Mesh2d_SizeMapControl::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar& boost::serialization::base_object<Global_Done>(*this);
		ar& theReference_;
		ar& theDomain_;

		ar& theBoundaries_;
		ar& theBackground_;

		//ar & theCloud_;
	}

	template<>
	template<>
	void Mesh2d_SizeMapControl::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar& boost::serialization::base_object<Global_Done>(*this);
		ar& theReference_;
		ar& theDomain_;

		ar& theBoundaries_;
		ar& theBackground_;

		//ar & theCloud_;
	}
}