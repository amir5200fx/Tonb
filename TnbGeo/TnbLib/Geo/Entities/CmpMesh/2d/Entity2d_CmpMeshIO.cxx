#include <Entity2d_CmpMesh.hxx>

#include <Entity2d_CmpConnect.hxx>
#include <TecPlot.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Entity2d_CmpMesh)
{
	ar& theCoords_;
	ar& theIndices_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Entity2d_CmpMesh)
{
	ar& theCoords_;
	ar& theIndices_;
}

void tnbLib::Entity2d_CmpMesh::ExportToPlt(OFstream& theFile) const
{
	Io::ExportMesh(Coords(), Indices(), theFile);
}
