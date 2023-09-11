#pragma once
#ifndef _GeoIO_VTK_Header
#define _GeoIO_VTK_Header

#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Geo_Module.hxx>
#include <OFstream.hxx>

#include <vector>
#include <string>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	namespace vtkLib
	{

		TnbGeo_EXPORT void WriteVersion(OFstream&);
		TnbGeo_EXPORT void WriteTitle(const std::string&, OFstream&);
		TnbGeo_EXPORT void WriteFileType_ASCII(OFstream&);
		TnbGeo_EXPORT void WriteUnstructuredGrid(OFstream&);

		TnbGeo_EXPORT void WriteNbPoints(const Standard_Integer, OFstream&);
		TnbGeo_EXPORT void WriteNbCells(const Standard_Integer, const Standard_Integer, OFstream&);
		TnbGeo_EXPORT void WriteCellTypes(const Standard_Integer, OFstream&);

		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt2d>&, OFstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::triple>&, OFstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::dual>&, OFstream&);

		TnbGeo_EXPORT void WriteMesh(const Entity2d_Triangulation&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Chain&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Polygon&, const std::string& theTitle, OFstream&);
	}
}

#endif // !_GeoIO_VTK_Header
