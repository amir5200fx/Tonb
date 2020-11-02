#include <Pln_Entity.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_Entity)
{
	ar & boost::serialization::base_object<Cad_Entity>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Pln_Entity)
{
	ar & boost::serialization::base_object<Cad_Entity>(*this);
}