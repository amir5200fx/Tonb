#include <TModel_Edge.hxx>

#include <TModel_Curve.hxx>
#include <TModel_Vertex.hxx>

#include <TopoDS.hxx>
#include <BRep_Tool.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Edge)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_EdgeAdaptor>(*this);
	ar & boost::serialization::base_object<TModel_EdgeGeometry>(*this);
	ar & boost::serialization::base_object<Cad_EntityPrecision>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Edge)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_EdgeAdaptor>(*this);
	ar & boost::serialization::base_object<TModel_EdgeGeometry>(*this);
	ar & boost::serialization::base_object<Cad_EntityPrecision>(*this);
}
