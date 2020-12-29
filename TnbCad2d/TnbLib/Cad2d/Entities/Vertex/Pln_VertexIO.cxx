#include <Pln_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Vertex)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_EntityPrecision>(*this);
	ar & boost::serialization::base_object<Pln_VertexAdaptor>(*this);

	ar & theCoord_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Vertex)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_EntityPrecision>(*this);
	ar & boost::serialization::base_object<Pln_VertexAdaptor>(*this);

	ar & theCoord_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_Vertex);