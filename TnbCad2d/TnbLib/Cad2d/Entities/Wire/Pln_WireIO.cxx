#include <Pln_Wire.hxx>

#include <Pln_CmpEdge.hxx>

void tnbLib::Pln_Wire::ExportToPlt(OFstream & File) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToPlt(File);
	}
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & CmpEdge();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & ChangeCmpEdge();
}