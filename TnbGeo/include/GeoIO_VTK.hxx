#pragma once
#ifndef _GeoIO_VTK_Header
#define _GeoIO_VTK_Header

#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity3d_SurfTriangulationFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Geo_Module.hxx>
#include <OFstream.hxx>

#include <vector>
#include <string>
#include <sstream>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Entity3d_CmpMeshSurface;
	class Entity2d_CmpMesh;
	class Pnt2d;

	namespace vtkLib
	{

		TnbGeo_EXPORT void WriteVersion(OFstream&);
		TnbGeo_EXPORT void WriteVersion(std::fstream&);
		TnbGeo_EXPORT void WriteTitle(const std::string&, OFstream&);
		TnbGeo_EXPORT void WriteTitle(const std::string&, std::fstream&);
		TnbGeo_EXPORT void WriteFileType_ASCII(OFstream&);
		TnbGeo_EXPORT void WriteFileType_ASCII(std::fstream&);
		TnbGeo_EXPORT void WriteUnstructuredGrid(OFstream&);
		TnbGeo_EXPORT void WriteUnstructuredGrid(std::fstream&);

		TnbGeo_EXPORT void WriteVersion(std::stringstream&);
		TnbGeo_EXPORT void WriteTitle(const std::string&, std::stringstream&);
		TnbGeo_EXPORT void WriteFileType_ASCII(std::stringstream&);
		TnbGeo_EXPORT void WriteUnstructuredGrid(std::stringstream&);

		TnbGeo_EXPORT void WriteNbPoints(const Standard_Integer, OFstream&);
		TnbGeo_EXPORT void WriteNbPoints(const Standard_Integer, std::fstream&);
		TnbGeo_EXPORT void WriteNbCells(const Standard_Integer, const Standard_Integer, OFstream&);
		TnbGeo_EXPORT void WriteNbCells(const Standard_Integer, const Standard_Integer, std::fstream&);
		TnbGeo_EXPORT void WriteCellTypes(const Standard_Integer, OFstream&);
		TnbGeo_EXPORT void WriteCellTypes(const Standard_Integer, std::fstream&);

		TnbGeo_EXPORT void WriteNbPoints(const Standard_Integer, std::stringstream&);
		TnbGeo_EXPORT void WriteNbCells(const Standard_Integer, const Standard_Integer, std::stringstream&);
		TnbGeo_EXPORT void WriteCellTypes(const Standard_Integer, std::stringstream&);

		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt2d>&, OFstream&);
		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt2d>&, std::fstream&);
		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt3d>&, OFstream&);
		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt3d>&, std::fstream&);
		TnbGeo_EXPORT void WritePoints(const std::vector<Entity3d_SPnt>&, std::fstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::triple>&, OFstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::triple>&, std::fstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::dual>&, OFstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::dual>&, std::fstream&);

		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt2d>&, std::stringstream&);
		TnbGeo_EXPORT void WritePoints(const std::vector<Pnt3d>&, std::stringstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::triple>&, std::stringstream&);
		TnbGeo_EXPORT void WriteConnectivity(const std::vector<connectivity::dual>&, std::stringstream&);

		TnbGeo_EXPORT void WriteMesh(const Entity2d_Triangulation&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Triangulation&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Triangulation&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Triangulation&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_SurfTriangulation&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Chain&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Chain&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Chain&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Polygon&, const std::string& theTitle, OFstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Polygon&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Polygon&, const std::string& theTitle, std::fstream&);

		TnbGeo_EXPORT void WriteMesh(const Entity2d_Triangulation&, const std::string& theTitle, std::stringstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Triangulation&, const std::string& theTitle, std::stringstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Chain&, const std::string& theTitle, std::stringstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Chain&, const std::string& theTitle, std::stringstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity2d_Polygon&, const std::string& theTitle, std::stringstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_Polygon&, const std::string& theTitle, std::stringstream&);

		TnbGeo_EXPORT void WriteMesh(const Entity2d_CmpMesh&, const std::string& theTitle, std::fstream&);
		TnbGeo_EXPORT void WriteMesh(const Entity3d_CmpMeshSurface&, const std::string& theTitle, std::fstream&);

		TnbGeo_EXPORT void ExportField(const Entity2d_Triangulation&, const std::vector<Standard_Real>& theField, std::stringstream&);
		TnbGeo_EXPORT void ExportField(const Entity3d_Tetrahedralization&, const std::vector<Standard_Real>& theField, std::stringstream&);
	}
}

#endif // !_GeoIO_VTK_Header
