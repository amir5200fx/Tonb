#include <Pln_Ring.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
}