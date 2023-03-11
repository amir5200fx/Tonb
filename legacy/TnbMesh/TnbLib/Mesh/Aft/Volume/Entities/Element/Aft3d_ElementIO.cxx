#include <Aft3d_Element.hxx>

#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft3d_Element)
{
	ar& boost::serialization::base_object<Aft3d_ElementAdaptor>(*this);
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& theFacets_;
	ar& theEdges_;
	ar& theNodes_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft3d_Element)
{
	ar& boost::serialization::base_object<Aft3d_ElementAdaptor>(*this);
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& theFacets_;
	ar& theEdges_;
	ar& theNodes_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::legLib::Aft3d_Element);