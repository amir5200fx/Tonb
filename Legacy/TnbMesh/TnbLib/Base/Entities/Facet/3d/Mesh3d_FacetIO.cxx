#include <Mesh3d_Facet.hxx>

#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Element.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh3d_Facet::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<adaptor>(*this);

		ar & theNodes_;
		ar & theEdges_;
	}

	template<>
	template<>
	void Mesh3d_Facet::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<adaptor>(*this);

		ar & theNodes_;
		ar & theEdges_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh3d_Facet);