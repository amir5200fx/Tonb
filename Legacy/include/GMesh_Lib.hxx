#pragma once
#ifndef _GMesh_Lib_Header
#define _GMesh_Lib_Header

#include <GMesh_Module.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity_Triangle.hxx>
#include <Pnt3d.hxx>
#include <Vec3d.hxx>

#include <gp_Ax1.hxx>

class TopoDS_Shape;

namespace tnbLib
{

	class GMesh_Lib
	{

		/*Private Data*/

	public:

		static TnbGMesh_EXPORT void AddTriangle
		(
			const Entity_Triangle<const Pnt3d&>& theTriangle,
			Standard_Real(*theSizeFun)(const Pnt3d&),
			Standard_Integer& theNbNodes,
			Standard_Integer& theNbEdges,
			Standard_Integer& theNbElements,
			const Standard_Boolean theSense = Standard_True
		);

		static TnbGMesh_EXPORT void AddSurface
		(
			const Entity3d_Triangulation& theSurface,
			Standard_Real(*theSizeFun)(const Pnt3d&),
			Standard_Integer& theNbNodes,
			Standard_Integer& theNbEdges, 
			Standard_Integer& theNbElements, 
			const Standard_Boolean theSense = Standard_True
		);

		static TnbGMesh_EXPORT void Initialize();

		static TnbGMesh_EXPORT void AddModel(const word& theName);
		static TnbGMesh_EXPORT Standard_Integer 
			AddPoint
			(
				const Pnt3d& theCoord, 
				const Standard_Real theSize, 
				const Standard_Integer theTag
			);

		static TnbGMesh_EXPORT Standard_Integer 
			AddLine
			(
				const Standard_Integer theP0,
				const Standard_Integer theP1,
				const Standard_Integer theTag
			);

		static TnbGMesh_EXPORT Standard_Integer 
			AddWire
			(
				const std::vector<Standard_Integer>& theLines, 
				const Standard_Integer theTag,
				const Standard_Boolean theSense = Standard_True
			);

		static TnbGMesh_EXPORT Standard_Integer 
			AddPlane
			(
				const std::vector<Standard_Integer>& theWires, 
				const Standard_Integer theTag
			);

		static TnbGMesh_EXPORT Standard_Integer
			AddShell
			(
				const std::vector<Standard_Integer>& thePlanes, 
				const Standard_Integer theTag
			);

		static TnbGMesh_EXPORT Standard_Integer
			AddVolume
			(
				const std::vector<Standard_Integer>& theShellTags, 
				const Standard_Integer theTag
			);

		static TnbGMesh_EXPORT void SynchronizeModel();
		static TnbGMesh_EXPORT void SynchronizeShape();

		static TnbGMesh_EXPORT Standard_Integer
			AddPhysicalGroup
			(
				const Standard_Integer theDim,
				const std::vector<Standard_Integer>& theTags, 
				const Standard_Integer theTag, 
				const word& theName
			);

		static TnbGMesh_EXPORT std::shared_ptr<Entity3d_Box> GetBoundingBox(
			const Standard_Integer theDim, const Standard_Integer tag);

		static TnbGMesh_EXPORT void Translate
		(
			const std::vector<std::pair<Standard_Integer, Standard_Integer>>&,
			const Vec3d& theV
		);
		
		static TnbGMesh_EXPORT void Rotate
		(
			const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags,
			const gp_Ax1& theAx,
			const Standard_Real theAngle
		);
		
		static TnbGMesh_EXPORT void Copy
		(
			const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theDimTags,
			std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
		);

		static TnbGMesh_EXPORT void GetValue
		(
			const Standard_Integer theDim, 
			const Standard_Integer theTag, 
			const std::vector<Standard_Real>& theParametricCoord, 
			std::vector<Standard_Real>& theCoord
		);

		static TnbGMesh_EXPORT void Extrude
		(
			const std::vector<std::pair<Standard_Integer, Standard_Integer>>&,
			const Vec3d& theVec,
			std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags,
			const std::vector<Standard_Integer>& theNumElements = std::vector<Standard_Integer>(),
			const std::vector<Standard_Real>& theHeights = std::vector<Standard_Real>(),
			const Standard_Boolean recombine = Standard_False
		);

		static TnbGMesh_EXPORT void ImportShape
		(
			const TopoDS_Shape& theShape,
			std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
		);

		static TnbGMesh_EXPORT void ImportSTEP
		(
			const std::string& name,
			std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
		);

		static TnbGMesh_EXPORT void ImportIGES
		(
			const std::string& name,
			std::vector<std::pair<Standard_Integer, Standard_Integer>>& theOutDimTags
		);

		static TnbGMesh_EXPORT void ImportSTL(const std::string& name,
		                                      std::vector<std::pair<Standard_Integer, Standard_Integer>>&
		                                      theOutDimTags);

		static TnbGMesh_EXPORT void SetSizeMap(const Geo3d_SizeFunction&);

		static TnbGMesh_EXPORT void SetSize(const std::vector<std::pair<Standard_Integer, Standard_Integer>>&, const Standard_Real theSize);
		
		static TnbGMesh_EXPORT void Generate(const Standard_Integer theDim);

		static TnbGMesh_EXPORT void WriteMesh(const std::string& theName);
		static TnbGMesh_EXPORT void Finalize();

	};
}

#endif // !_GMesh_Lib_Header
