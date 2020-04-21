#pragma once
#ifndef _HydStatic_Modeler_Header
#define _HydStatic_Modeler_Header

#include <Global_AccessMethod.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_AdTree.hxx>
#include <Entity3d_Box.hxx>
#include <HydStatic_Entity.hxx>
#include <HydStatic_Modeler_Corner.hxx>
#include <Cad3d_NModelManager.hxx>

#include <map>
#include <memory>

class TopoDS_Face;

namespace tnbLib
{

	// Forward Declarations
	class NModel_Vertex;
	class NModel_Edge;
	class NModel_Surface;
	class NModel_Edge;

	namespace hydStcLib { class Modeler_CurveTools; }
	namespace hydStcLib { class Modeler_SurfaceTools; }

	class HydStatic_Modeler_Counter
	{

		typedef Geo_PriorityList<Standard_Integer> counterList;

		/*Private Data*/

		Standard_Integer theNbVertices_;
		Standard_Integer theNbEdges_;
		Standard_Integer theNbSurfaces_;

		Standard_Integer theNbCorners_;

		counterList theVertexIndex_;
		counterList theEdgeIndex_;
		counterList theSurfaceIndex_;

		counterList theCornerIndex_;

	protected:

		HydStatic_Modeler_Counter();


		void InsertToVertexCounter(const Standard_Integer theIndex);

		void InsertToEdgeCounter(const Standard_Integer theIndex);

		void InsertToSurfaceCounter(const Standard_Integer theIndex);

		void InsertToCornerCounter(const Standard_Integer theIndex);

		Standard_Integer RetrieveIndexForVertex();

		Standard_Integer RetrieveIndexForEdge();

		Standard_Integer RetrieveIndexForSurface();

		Standard_Integer RetrieveIndexForCorner();

		//- macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbVertices)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbEdges)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbSurfaces)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbCorners)

	public:


	};


	class HydStatic_Modeler_SrchEng
	{

		typedef hydStcLib::Modeler_Corner corner;

		/*Private Data*/

		Geo_AdTree<std::shared_ptr<corner>>
			theVtxSrchEngine_;

	protected:

		HydStatic_Modeler_SrchEng();


		static const Standard_Real DEFAULT_DELTA;
		static const std::shared_ptr<corner> null;

		const std::shared_ptr<corner>& SelectCorner(const Pnt3d& theCoord) const;

		void ReArrangeEngine();

		void AddCorner
		(
			const std::shared_ptr<corner>& theCorner
		);

		void RemoveCorner
		(
			const std::shared_ptr<corner>& theCorner
		);

		static Standard_Boolean IsNull(const std::shared_ptr<corner>& theCorner);

	};

	class HydStatic_Modeler
		: public HydStatic_Modeler_Counter
		, public HydStatic_Modeler_SrchEng
	{

		typedef std::vector<std::shared_ptr<NModel_Surface>>
			faceList;

		typedef std::vector<std::shared_ptr<NModel_Edge>>
			edgeList;

		typedef hydStcLib::Modeler_Corner corner;

		friend class hydStcLib::Modeler_CurveTools;
		friend class hydStcLib::Modeler_SurfaceTools;

		/*Private Data*/

		/*std::map<Standard_Integer, std::shared_ptr<corner>>
			theCorners_;*/

		std::map<Standard_Integer, std::shared_ptr<NModel_Vertex>>
			theVertices_;
		std::map<Standard_Integer, std::shared_ptr<NModel_Edge>>
			theEdges_;
		std::map<Standard_Integer, std::shared_ptr<NModel_Surface>>
			theSurfaces_;


		std::pair
			<
			std::vector<std::pair<std::shared_ptr<NModel_Vertex>, std::shared_ptr<corner>>>, 
			Standard_Boolean
			>
			RetrievePairs
			(
				const std::shared_ptr<NModel_Surface>& theSurface
			) const;

		auto& ChangeVerices()
		{
			return theVertices_;
		}

		auto& ChangeEdges()
		{
			return theEdges_;
		}

		auto& ChangeSurfaces()
		{
			return theSurfaces_;
		}

		void InsertToVertices(const std::shared_ptr<NModel_Vertex>& theVertex);
		void InsertToEdges(const std::shared_ptr<NModel_Edge>& theEdge);
		void InsertToSurfaces(const std::shared_ptr<NModel_Surface>& theSurface);

		void AddVertex(const std::shared_ptr<NModel_Vertex>& theVertex, const Standard_Integer theSurfaceIndex);
		void AddEdge(const std::shared_ptr<NModel_Edge>& theEdge, const Standard_Integer theSurfaceIndex);
		
		void AddSurface(const std::shared_ptr<NModel_Surface>& theSurface);

	public:

		HydStatic_Modeler();

		
		void Import(const TopoDS_Face& theFace);


		
	};
}

#endif // !_HydStatic_Modeler_Header
