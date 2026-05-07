#include <Aft3d_Facet.hxx>

#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft3d_Facet)
{
	ar& boost::serialization::base_object<Aft3d_FacetAdaptor>(*this);
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& theNodes_;
	ar& theEdges_;
	ar& isCavity_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft3d_Facet)
{
	ar& boost::serialization::base_object<Aft3d_FacetAdaptor>(*this);
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& theNodes_;
	ar& theEdges_;
	ar& isCavity_;
}