#include <Mesh2d_Edge.hxx>

#include <Mesh2d_Node.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh2d_Edge::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<edgeAdaptor>(*this);
		ar & theNodes_;
	}

	template<>
	template<>
	void Mesh2d_Edge::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<edgeAdaptor>(*this);
		ar & theNodes_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_Edge);