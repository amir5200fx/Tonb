#pragma once
#ifndef _Aft3d_Tools_Header
#define _Aft3d_Tools_Header

#include <Mesh_Module.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward declarations [6/1/2023 Payvand]
	class Pnt3d;
	class Vec3d;

	namespace legLib
	{

		// Forward declarations [6/1/2023 Payvand]
		class Aft3d_Facet;
		class Aft3d_Edge;
		class Aft3d_Node;

		class Aft3d_Tools
		{

		public:

			static inline const Pnt3d& GetCoord0(const Aft3d_Edge&);
			static inline const Pnt3d& GetCoord1(const Aft3d_Edge&);

			static inline const Pnt3d& GetCoord0(const Aft3d_Facet&);
			static inline const Pnt3d& GetCoord1(const Aft3d_Facet&);
			static inline const Pnt3d& GetCoord2(const Aft3d_Facet&);

			static TnbLegMesh_EXPORT Vec3d 
				CalcNormal(const Aft3d_Facet& theFacet);

			static Standard_Boolean IsForwardEdge(const std::shared_ptr<Aft3d_Edge>& theEdge, const std::shared_ptr<Aft3d_Facet>& theFace);

			static std::shared_ptr<Aft3d_Edge> CommonEdge(const Aft3d_Facet& theFace0, const Aft3d_Facet& theFace1);

			// Calculating the angle between two triangles which have a common edge
			// Will throw an exception if there is no common edge [6/3/2023 Payvand]
			static Standard_Real CalcCommonEdgeAngle(const Aft3d_Facet& theFace0, const Aft3d_Facet& theFace1);

			static TnbLegMesh_EXPORT Pnt3d 
				CalcTetrahedronVertex
				(
					const Standard_Real theSize,
					const Aft3d_Facet&
				);

			static TnbLegMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Node>>
				RetrieveNodes(const std::vector<std::shared_ptr<Aft3d_Facet>>&);
			static TnbLegMesh_EXPORT std::vector<std::shared_ptr<Aft3d_Edge>>
				RetrieveEdges(const std::vector<std::shared_ptr<Aft3d_Facet>>&);
			static TnbLegMesh_EXPORT std::vector<Pnt3d> RetriveGeometries(const std::vector<std::shared_ptr<Aft3d_Node>>&);
		};
	}
}

#include <Aft3d_ToolsI.hxx>

#endif // !_Aft3d_Tools_Header
