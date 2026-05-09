#include <Pln_Ring.hxx>

#include <Pln_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
	ar & theVtx_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
	ar & theVtx_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_Ring);