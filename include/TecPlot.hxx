#pragma once
#ifndef _TecPlot_Header
#define _TecPlot_Header

#include <Standard_TypeDef.hxx>
#include <Entity_Connectivity.hxx>
#include <Geo_Module.hxx>
#include <OFstream.hxx>

#include <vector>
#include <array>
#include <sstream>

namespace tnbLib
{

	class Pnt3d;
	class Pnt2d;
	class Entity2d_CmpConnect;
	class Entity3d_CmpConnect;

	namespace Io
	{
		TnbGeo_EXPORT void WriteVariables
		(
			const word& theVariables,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteVariables
		(
			const word& theVariables,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt2d>& thePoints,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt2d>& thePoints,
			OFstream& File
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt2d>& thePoints,
			std::fstream&
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt3d>& thePoints,
			OFstream&
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt3d>& thePoints,
			std::stringstream&
		);

		TnbGeo_EXPORT void WritePointsVariables
		(
			const std::vector<Pnt3d>& thePoints,
			std::fstream&
		);

		TnbGeo_EXPORT void WriteFeTriangleZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTriangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteFeTriangleZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTriangles,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteFeQuadrilateralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTriangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteFeQuadrilateralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTriangles,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteFeHexahedralZone
		(
			const Standard_Integer NbNodes, 
			const Standard_Integer NbElements, 
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteFeHexahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbElements, 
			std::fstream& theFile
		);

		TnbGeo_EXPORT void WriteFeHexahedralZone
		(
			const Standard_Integer NbNodes, 
			const Standard_Integer NbElements, 
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTriangularZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris,
			const Standard_Integer NbVar,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTriangularZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris,
			const Standard_Integer NbVar,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTriangularZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris, 
			const Standard_Integer NbVars,
			std::fstream& file
		);

		TnbGeo_EXPORT void WriteCellCenteredFeQuadrilateralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbElements,
			const Standard_Integer NbVar,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteCellCenteredFeQuadrilateralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbElements,
			const Standard_Integer NbVar,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteCellCenteredFeQuadrilateralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbElements,
			const Standard_Integer NbVars,
			std::fstream& file
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTriangular3DZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris,
			const Standard_Integer NbVar,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTriangular3DZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTris,
			const Standard_Integer NbVar,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			const Standard_Integer NbVar,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteCellCenteredFeTetrahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbTets,
			const Standard_Integer NbVar,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteCellCenteredFeHexahedralZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbElements,
			const Standard_Integer NbVars, 
			OFstream& file
		);

		TnbGeo_EXPORT void WriteCellCenteredFeHexahedralZone
		(
			const Standard_Integer NbNodes, 
			const Standard_Integer NbElements,
			const Standard_Integer NbVars,
			std::stringstream& file
		);

		TnbGeo_EXPORT void WriteCellCenteredFeHexahedralZone
		(
			const Standard_Integer NbNodes, 
			const Standard_Integer NbElements,
			const Standard_Integer NbVars,
			std::fstream& file
		);

		TnbGeo_EXPORT void WriteFeBrickZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbBricks,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteFeBrickZone
		(
			const Standard_Integer NbNodes,
			const Standard_Integer NbBricks,
			OFstream& theFile
		);

		TnbGeo_EXPORT void WriteIorderedZone
		(
			const Standard_Integer NbNodes,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void WriteIorderedZone
		(
			const Standard_Integer NbNodes,
			OFstream& theFile
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var, 
			const std::vector<Pnt2d>& thePoints,
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, 
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var,
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var,
			OFstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var,
			std::stringstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var, 
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::octuple>& ids, 
			const std::vector<std::array<Type, nbVAR>>& var,
			OFstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::octuple>& ids, 
			const std::vector<std::array<Type, nbVAR>>& var, 
			std::stringstream& file
		);

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::octuple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var, 
			std::fstream&
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>&,
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>&,
			OFstream&
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>&,
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>&,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>&,
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>&,
			OFstream&
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>&,
			const std::vector<std::shared_ptr<Entity2d_CmpConnect>>&,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>&,
			std::vector<std::shared_ptr<Entity3d_CmpConnect>>&,
			OFstream&
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>&,
			std::vector<std::shared_ptr<Entity3d_CmpConnect>>&,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints, 
			const std::vector<connectivity::quadruple>& theElements,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::quadruple>& theElements,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple_3d>& theElements,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple_3d>& theElements,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::dual>& Triangles,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::dual>& Triangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::dual>& Triangles,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::dual>& Triangles,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints, 
			const std::vector<connectivity::quadruple>& theTets,
			OFstream&
		);

		TnbGeo_EXPORT void ExportMesh
		(
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theTets,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportMesh(const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>&,
		                              OFstream&);
		TnbGeo_EXPORT void ExportMesh(const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>&,
		                              std::stringstream&);

		TnbGeo_EXPORT void ExportCurve
		(
			const std::vector<Pnt3d>& Points,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportCurve
		(
			const std::vector<Pnt3d>& Points,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportCurve
		(
			const std::vector<Pnt2d>& Points,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportCurve
		(
			const std::vector<Pnt2d>& Points,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportPoints
		(
			const std::vector<Pnt3d>& Points,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportPoints
		(
			const std::vector<Pnt3d>& Points,
			std::stringstream& theStream
		);

		TnbGeo_EXPORT void ExportPoints
		(
			const std::vector<Pnt2d>& Points,
			OFstream& File
		);

		TnbGeo_EXPORT void ExportPoints
		(
			const std::vector<Pnt2d>& Points,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theTets,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theTets,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, 
			const std::vector<connectivity::octuple>& theElements, 
			OFstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::octuple>& theElements,
			std::stringstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var, 
			const std::vector<Pnt3d>& thePoints, 
			const std::vector<connectivity::octuple>& theElements, 
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream& File
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var, 
			const std::vector<Pnt2d>& thePoints, 
			const std::vector<connectivity::triple>& Triangles, 
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::quadruple>& Triangles,
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theElements,
			OFstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theElements,
			std::stringstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, 
			const std::vector<connectivity::quadruple>& theElements,
			std::fstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, 
			const std::vector<connectivity::octuple>& theElements,
			OFstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::octuple>& theElements,
			std::stringstream& file
		);

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word& theVarNames, 
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::octuple>& theElements,
			std::fstream& file
		);
	}
}

#include <TecPlotI.hxx>

#endif // !_TecPlot_Header
