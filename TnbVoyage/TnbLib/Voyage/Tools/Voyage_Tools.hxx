#pragma once
#ifndef _Voyage_Tools_Header
#define _Voyage_Tools_Header

#include <VoyageGeo_VelocityBackgroundFwd.hxx>
#include <Voyage_Module.hxx>

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]

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

	};
}

#endif // !_Voyage_Tools_Header
