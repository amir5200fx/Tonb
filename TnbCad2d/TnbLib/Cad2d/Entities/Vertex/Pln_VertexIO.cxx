#include <Pln_Vertex.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_Vertex)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_EntityPrecision>(*this);
	ar & boost::serialization::base_object<Pln_VertexAdaptor>(*this);

	ar & Coord();
}

DECLARE_LOAD_IMP(tnbLib::Pln_Vertex)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_EntityPrecision>(*this);
	ar & boost::serialization::base_object<Pln_VertexAdaptor>(*this);

	ar & Coord();
}