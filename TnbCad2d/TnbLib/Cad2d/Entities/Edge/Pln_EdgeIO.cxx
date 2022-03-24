#include <Pln_Edge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>

void tnbLib::Pln_Edge::ExportToPlt
(
	OFstream & File
) const
{
	if (Mesh())
	{
		Mesh()->ExportToPlt(File);
	}
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Edge)
{
	ar& boost::serialization::base_object<Pln_Entity>(*this);
	ar& boost::serialization::base_object<Pln_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Pln_EdgeGeom>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Edge)
{
	ar& boost::serialization::base_object<Pln_Entity>(*this);
	ar& boost::serialization::base_object<Pln_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Pln_EdgeGeom>(*this);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_Edge);