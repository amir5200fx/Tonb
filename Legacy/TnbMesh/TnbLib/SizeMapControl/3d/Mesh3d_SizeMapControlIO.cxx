#include <Mesh3d_SizeMapControl.hxx>

#include <Geo3d_PatchCloud.hxx>
#include <Cad_TModel.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_SizeMapTool.hxx>
#include <Entity3d_Box.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Mesh3d_SizeMapControl::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theReference_;
		ar & theBoundaries_;
		ar & theDomain_;
		ar & theCloud_;
	}

	template<>
	template<>
	void Mesh3d_SizeMapControl::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int /*file_version*/)
	{
		ar & theReference_;
		ar & theBoundaries_;
		ar & theDomain_;
		ar & theCloud_;
	}
}