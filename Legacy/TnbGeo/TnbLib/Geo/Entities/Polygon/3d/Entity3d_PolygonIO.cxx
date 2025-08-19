#include <Entity3d_Polygon.hxx>

#include <TecPlot.hxx>
#include <GeoIO_VTK.hxx>

namespace tnbLib
{
	
	template<>
	void Entity3d_Polygon::ExportToPlt(OFstream& File) const
	{
		Io::ExportCurve(thePoints_, File);
	}

	template <>
	void Entity3d_Polygon::ExportToVtk(std::fstream& file) const
	{
		vtkLib::WriteMesh(*this, "the polygon", file);
	}

	template <>
	void Entity3d_Polygon::ExportToVtk(std::stringstream& st) const
	{
		vtkLib::WriteMesh(*this, "the polygon", st);
	}

}