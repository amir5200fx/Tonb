#include <GeoSizeFun3d_Background.hxx>

#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <MeshBase_Tools.hxx>

namespace tnbLib
{

	template<>
	template<>
	void GeoSizeFun3d_Background::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<GeoSizeFun3d_nonUniform>(*this);
		ar & theBackMesh_;

		if (theBackMesh_)
		{
			theBackMesh_->ConnectTopology();
		}
		/*if (theBackMesh_)
		{
			if (const auto& mesh = theBackMesh_->Mesh())
			{
				if (mesh->Elements().size())
				{
					MeshBase_Tools::ConnectMesh(mesh->Elements());
				}
			}
		}*/
	}

	template<>
	template<>
	void GeoSizeFun3d_Background::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			)
	{
		ar & boost::serialization::base_object<GeoSizeFun3d_nonUniform>(*this);
		ar & theBackMesh_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoSizeFun3d_Background);