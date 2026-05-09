#include <Aft3d_Edge.hxx>

#include <Aft3d_Node.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::legLib::Aft3d_Edge)
{
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& boost::serialization::base_object<Aft3d_EdgeGeoemtry>(*this);
	ar& boost::serialization::base_object<Aft3d_EdgeAdaptor>(*this);
	ar& theNodes_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::legLib::Aft3d_Edge)
{
	ar& boost::serialization::base_object<Aft3d_Entity>(*this);
	ar& boost::serialization::base_object<Aft3d_EdgeGeoemtry>(*this);
	ar& boost::serialization::base_object<Aft3d_EdgeAdaptor>(*this);
	ar& theNodes_;
}