#include <Entity2d_Polygon.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{

	template<>
	void Entity2d_Polygon::ExportToPlt(OFstream& File) const
	{
		Io::ExportCurve(thePoints_, File);
	}
}

template<>
void tnbLib::Entity2d_Polygon::ExportToVtk(OFstream& file) const
{
	vtkLib::WriteMesh(*this, "the polygon", file);
}

template <>
void tnbLib::Entity2d_Polygon::ExportToVtk(std::fstream& file) const
{
	vtkLib::WriteMesh(*this, "the polygon", file);
}

template <>
void tnbLib::Entity2d_Polygon::ExportToPlt(std::stringstream& theStream) const
{
	Io::ExportCurve(thePoints_, theStream);
}

template<>
void tnbLib::Entity2d_Polygon::ExportToVtk(std::stringstream& file) const
{
	vtkLib::WriteMesh(*this, "the polygon", file);
}