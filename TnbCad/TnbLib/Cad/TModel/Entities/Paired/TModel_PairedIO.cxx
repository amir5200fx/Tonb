#include <TModel_PairedGeometry.hxx>
#include <TModel_Paired.hxx>

#include <TModel_Edge.hxx>
#include <Entity3d_Polygon.hxx>


TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Paired)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_PairedGeometry>(*this);

	ar & theEdge0_;
	ar & theEdge1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Paired)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & boost::serialization::base_object<TModel_PairedGeometry>(*this);

	ar & theEdge0_;
	ar & theEdge1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_Paired);

void tnbLib::TModel_PairedGeometry::ExportToPlt(OFstream & File) const
{
	if (NOT Mesh())
	{
		return;
	}

	Mesh()->ExportToPlt(File);
}