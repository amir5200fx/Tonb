#include <Pln_Segment.hxx>

#include <Pln_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Segment)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
	ar & theVtx0_;
	ar & theVtx1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Segment)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
	ar & theVtx0_;
	ar & theVtx1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_Segment);