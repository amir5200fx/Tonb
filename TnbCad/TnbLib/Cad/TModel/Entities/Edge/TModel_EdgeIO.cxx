#include <TModel_Edge.hxx>

#include <TModel_Curve.hxx>
#include <TModel_Vertex.hxx>

#include <opencascade/TopoDS.hxx>
#include <opencascade/BRep_Tool.hxx>

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
