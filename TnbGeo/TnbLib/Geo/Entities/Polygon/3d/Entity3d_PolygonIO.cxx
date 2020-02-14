#include <Entity3d_Polygon.hxx>

#include <TecPlot.hxx>

namespace tnbLib
{
	
	template<>
	void Entity3d_Polygon::ExportToPlt(OFstream& File) const
	{
		Io::ExportCurve(thePoints_, File);
	}
}