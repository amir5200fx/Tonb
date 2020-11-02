#include <Pln_Ring.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Pln_Ring)
{
	ar & boost::serialization::base_object<Pln_Edge>(*this);
}