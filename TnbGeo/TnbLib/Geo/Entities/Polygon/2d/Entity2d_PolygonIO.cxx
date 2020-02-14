#include <Entity2d_Polygon.hxx>

#include <TecPlot.hxx>

namespace tnbLib
{

	template<>
	void Entity2d_Polygon::ExportToPlt(OFstream& File) const
	{
		Io::ExportCurve(thePoints_, File);
	}
}