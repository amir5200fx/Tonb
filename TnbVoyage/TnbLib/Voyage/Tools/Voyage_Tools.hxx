#pragma once
#ifndef _Voyage_Tools_Header
#define _Voyage_Tools_Header

#include <VoyageGeo_VelocityBackgroundFwd.hxx>
#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Vec2d.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]
	class VoyageGeo_Path2;
	class Voyage_Edge;
	class Voyage_Node;
	class Cad_GeomSurface;
	class Pnt2d;
	class Vec2d;

	class Voyage_Tools
	{

	public:

		// the nodes are sorted based on their indices 
		// So the first node is departure and the last one is destination [7/21/2023 Payvand]
		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Voyage_Node>> 
			RetrieveNodes(const std::vector<std::shared_ptr<Voyage_Edge>>&);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Node> 
			NeighborNode
			(
				const std::shared_ptr<Voyage_Node>& theCurrent, 
				const std::shared_ptr<Voyage_Edge>& theEdge
			);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Edge> 
			RetrieveEdge
			(
				const std::shared_ptr<Voyage_Node>&,
				const std::shared_ptr<Voyage_Node>&
			);

		static TnbVoyage_EXPORT std::shared_ptr<VoyageGeo_VelocityBackground> 
			MakeBackground
			(
				const std::vector<Pnt2d>& theCoords, 
				const std::vector<Vec2d>& theVecolity, 
				const Standard_Real theTol
			);

		static TnbVoyage_EXPORT std::vector<Pnt2d>
			ShortestStraightPath
			(
				const Pnt2d& theStart,
				const Pnt2d& theEnd, 
				const std::shared_ptr<Cad_GeomSurface>& theSurface
			);

		static TnbVoyage_EXPORT std::shared_ptr<Entity2d_Box>
			CalcBoundingBox
			(
				const std::vector<std::shared_ptr<Entity2d_Polygon>>&,
				const Standard_Real theTol
			);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Entity2d_Polygon>>
			RetrievePolygons
			(
				const VoyageGeo_Path2& thePath
			);

		static TnbVoyage_EXPORT Standard_Real
			CalcLength
			(
				const Entity2d_Polygon& thePolygon, 
				const Geo2d_MetricPrcsrAnIso&
			);

		static TnbVoyage_EXPORT std::vector<Standard_Real>
			CalcParameters
			(
				const Entity2d_Polygon&, 
				const Geo2d_MetricPrcsrAnIso&, 
				Standard_Real& theTotLength
			);

		// Convert the standard voyage coordinates to the parametric coordinates [8/27/2023 aamir]
		static TnbVoyage_EXPORT Pnt2d ConvertToUV(const Pnt2d&);
		static TnbVoyage_EXPORT Pnt2d ConvertToVoyageSystem(const Pnt2d&);

		static TnbVoyage_EXPORT Standard_Real KtsToKmh(const Standard_Real);

		// The route angle is greater than zero if the route turns to the left and is less than zero if turns to the right [8/5/2023 Payvand]
		static Standard_Real CalcRouteAngle(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theP2);

		static Vec2d CalcRightsideNormal(const Pnt2d& theP0, const Pnt2d& theP1);
		static Vec2d CalcLeftsideNormal(const Pnt2d& theP0, const Pnt2d& theP1);
	};
}

#endif // !_Voyage_Tools_Header
