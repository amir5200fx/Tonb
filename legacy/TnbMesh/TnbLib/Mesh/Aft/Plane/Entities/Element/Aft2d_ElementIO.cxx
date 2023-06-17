#include <Aft2d_Element.hxx>

#include <Aft2d_Node.hxx>
#include <Aft2d_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft2d_Element)
{
	ar& boost::serialization::base_object<Aft2d_Entity>(*this);
	ar& boost::serialization::base_object<Aft2d_ElementAdaptor>(*this);

	ar& theNodes_;
	ar& theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft2d_Element)
{
	ar& boost::serialization::base_object<Aft2d_Entity>(*this);
	ar& boost::serialization::base_object<Aft2d_ElementAdaptor>(*this);

	ar& theNodes_;
	ar& theEdges_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::legLib::Aft2d_Element);