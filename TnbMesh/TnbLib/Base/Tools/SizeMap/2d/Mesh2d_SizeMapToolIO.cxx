#include <Mesh2d_SizeMapTool.hxx>

#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapTool)
{
	ar & boost::serialization::base_object<Mesh_SizeMapToolBase<GeoMesh2d_Background>>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & thePlane_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_SizeMapTool)
{
	ar & boost::serialization::base_object<Mesh_SizeMapToolBase<GeoMesh2d_Background>>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & thePlane_;
}

#include <Mesh_ReferenceValues.hxx>
#include <GeoMesh2d_Background.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh2d_Background>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theConditions_;
		ar & theValues_;

		ar & theReference_;
		ar & theBackMesh_;
	}

	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh2d_Background>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theConditions_;
		ar & theValues_;

		ar & theReference_;
		ar & theBackMesh_;
	}
}