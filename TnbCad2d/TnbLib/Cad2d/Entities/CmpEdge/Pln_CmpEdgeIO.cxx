#include <Pln_CmpEdge.hxx>

#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Pln_CmpEdge::ExportToPlt(OFstream & File) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(File);
	}
}

void tnbLib::Pln_CmpEdge::ExportToPlt(std::stringstream& theStream) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		x->ExportToPlt(theStream);
	}
}

void tnbLib::Pln_CmpEdge::ExportToVtk(OFstream& theFile) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		x->ExportToVtk(theFile);
	}
}

void tnbLib::Pln_CmpEdge::ExportToVtk(std::stringstream& theStream) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		x->ExportToVtk(theStream);
	}
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_CmpEdge)
{
	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_CmpEdge)
{
	ar & theEdges_;
}