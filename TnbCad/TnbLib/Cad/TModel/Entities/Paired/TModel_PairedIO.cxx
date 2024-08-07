#include <TModel_PairedGeometry.hxx>
#include <TModel_Paired.hxx>

#include <TModel_Edge.hxx>
#include <Entity3d_Polygon.hxx>


void tnbLib::TModel_PairedGeometry::ExportToPlt(OFstream & File) const
{
	if (NOT Mesh())
	{
		return;
	}

	Mesh()->ExportToPlt(File);
}