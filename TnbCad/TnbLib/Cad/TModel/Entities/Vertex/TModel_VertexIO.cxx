#include <TModel_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Vertex)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_VertexAdaptor>(*this);
	ar & boost::serialization::base_object<Cad_EntityPrecision>(*this);

	ar & theCoord_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Vertex)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_VertexAdaptor>(*this);
	ar & boost::serialization::base_object<Cad_EntityPrecision>(*this);

	ar & theCoord_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Vertex);