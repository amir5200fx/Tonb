#include <Aft2d_ElementSurface.hxx>

#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_EdgeSurface.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::serialize<TNB_iARCH_TYPE>
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
	void Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::serialize<TNB_oARCH_TYPE>
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

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_ElementSurface);