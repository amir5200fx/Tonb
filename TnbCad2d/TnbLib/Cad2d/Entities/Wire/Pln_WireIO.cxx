#include <Pln_Wire.hxx>

#include <Pln_CmpEdge.hxx>

void tnbLib::Pln_Wire::ExportToPlt(OFstream & File) const
{
	if (CmpEdge())
	{
		CmpEdge()->ExportToPlt(File);
	}
}

DECLARE_SAVE_IMP(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & CmpEdge();
}

DECLARE_LOAD_IMP(tnbLib::Pln_Wire)
{
	ar & boost::serialization::base_object<Pln_Entity>(*this);
	ar & boost::serialization::base_object<Pln_WireAdaptor>(*this);
	ar & boost::serialization::base_object<Pln_WireAux>(*this);

	ar & ChangeCmpEdge();
}