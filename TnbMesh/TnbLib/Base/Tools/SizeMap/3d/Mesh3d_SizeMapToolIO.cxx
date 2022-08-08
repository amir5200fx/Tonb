#include <Mesh3d_SizeMapTool.hxx>

#include <Mesh3d_Element.hxx>
#include <Cad_TModel.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_SizeMapTool)
{
	ar & boost::serialization::base_object<Mesh_SizeMapToolBase<GeoMesh3d_Background>>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_SizeMapTool)
{
	ar & boost::serialization::base_object<Mesh_SizeMapToolBase<GeoMesh3d_Background>>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theModel_;
}

#include <Mesh_ReferenceValues.hxx>
#include <GeoMesh3d_Background.hxx>
#include <Entity3d_Box.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh3d_Background>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theConditions_;
		ar & theValues_;

		ar & theReference_;
		ar & theDomain_;
		ar & theBackMesh_;
	}

	template<>
	template<>
	void Mesh_SizeMapToolBase<GeoMesh3d_Background>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theConditions_;
		ar & theValues_;

		ar & theReference_;
		ar & theDomain_;
		ar & theBackMesh_;
	}
}