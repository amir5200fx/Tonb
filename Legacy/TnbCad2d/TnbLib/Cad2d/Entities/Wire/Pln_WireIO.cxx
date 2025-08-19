#include <Pln_Wire.hxx>

#include <Pln_CmpEdge.hxx>

void tnbLib::Pln_Wire::ExportToPlt(OFstream & File) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToPlt(File);
	}
}

void tnbLib::Pln_Wire::ExportToPlt(std::stringstream& theStream) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToPlt(theStream);
	}
}

void tnbLib::Pln_Wire::ExportToVtk(OFstream& theFile) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToVtk(theFile);
	}
}

void tnbLib::Pln_Wire::ExportToVtk(std::stringstream& theStream) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToVtk(theStream);
	}
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & theEdges_;
}