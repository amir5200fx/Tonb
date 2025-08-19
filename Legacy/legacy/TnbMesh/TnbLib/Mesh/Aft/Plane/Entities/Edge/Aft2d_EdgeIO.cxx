#include <Aft2d_Edge.hxx>

#include <Aft2d_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft2d_Edge)
{
	ar& boost::serialization::base_object<Aft2d_Entity>(*this);
	ar& boost::serialization::base_object<Aft2d_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Aft2d_EdgeGeometry>(*this);

	ar& theNodes_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft2d_Edge)
{
	ar& boost::serialization::base_object<Aft2d_Entity>(*this);
	ar& boost::serialization::base_object<Aft2d_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Aft2d_EdgeGeometry>(*this);

	ar& theNodes_;
}