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

void tnbLib::Pln_Edge::ExportToPlt(std::stringstream& theStream) const
{
	if (Mesh())
	{
		Mesh()->ExportToPlt(theStream);
	}
}

void tnbLib::Pln_Edge::ExportToVtk(OFstream& theFile) const
{
	if (Mesh())
	{
		Mesh()->ExportToVtk(theFile);
	}
}

void tnbLib::Pln_Edge::ExportToVtk(std::stringstream& theStream) const
{
	if (Mesh())
	{
		Mesh()->ExportToVtk(theStream);
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