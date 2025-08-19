#include <Pln_Entity.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Entity)
{
	ar & boost::serialization::base_object<Cad_Entity>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Entity)
{
	ar & boost::serialization::base_object<Cad_Entity>(*this);
}
