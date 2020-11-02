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

DECLARE_SAVE_IMP(tnbLib::Pln_Edge)
{
	ar& boost::serialization::base_object<Pln_Entity>(*this);
	ar& boost::serialization::base_object<Pln_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Pln_EdgeGeom>(*this);

	ar << Vtx0();
	ar << Vtx1();
}

DECLARE_LOAD_IMP(tnbLib::Pln_Edge)
{
	ar& boost::serialization::base_object<Pln_Entity>(*this);
	ar& boost::serialization::base_object<Pln_EdgeAdaptor>(*this);
	ar& boost::serialization::base_object<Pln_EdgeGeom>(*this);

	ar >> ChangeVtx0();
	ar >> ChangeVtx1();
}