#include <Mesh2d_Element.hxx>

#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh2d_Element::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<adaptor>(*this);
		ar & theNodes_;
		ar & theEdges_;
	}

	template<>
	template<>
	void Mesh2d_Element::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			)
	{
		ar & boost::serialization::base_object<Mesh_Entity>(*this);
		ar & boost::serialization::base_object<adaptor>(*this);
		ar & theNodes_;
		ar & theEdges_;
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Mesh2d_Element);