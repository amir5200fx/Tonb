#pragma once
#ifndef _Voyage_Waypoints_Header
#define _Voyage_Waypoints_Header

#include <Voyage_PathDir.hxx>
#include <Voyage_Module.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/2/2023 Payvand]
	class VoyageWP_Net;
	class VoyageMesh_Element;
	class VoyageMesh_Node;
	class Voyage_WptsGrid;
	class Voyage_MetricInfo;
	class Voyage_OffsetProfile;
	class VoyageMesh_Edge;
	class VoyageMesh_Node;
	class VoyageGeo_Path2;

	class Voyage_Waypoints
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path2> thePath_;

		std::shared_ptr<Geo2d_SizeFunction> theStarboardSize_;
		std::shared_ptr<Geo2d_SizeFunction> thePortSize_;

		std::shared_ptr<Voyage_OffsetProfile> theProfile_;

		std::shared_ptr<Voyage_MetricInfo> theInfo_;

		Standard_Real theSize_;


		// results [9/2/2023 Payvand]

		std::shared_ptr<VoyageWP_Net> theGrid_;

		std::shared_ptr<Entity2d_Triangulation> theStarMesh_;
		std::shared_ptr<Entity2d_Triangulation> thePortMesh_;

		// Private functions and operators [9/2/2023 Payvand]

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Entity2d_Polygon>> 
			RetrievePolygons(const VoyageGeo_Path2&);

		static TnbVoyage_EXPORT std::pair
			<
			std::vector<std::shared_ptr<VoyageMesh_Edge>>, 
			std::vector<std::shared_ptr<VoyageMesh_Edge>>
			>
			RetrieveEdges(const std::vector<std::shared_ptr<Entity2d_Polygon>>&);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Edge>>
			RetrieveEdges
			(
				const Entity2d_Polygon&
			);

		static TnbVoyage_EXPORT std::shared_ptr<VoyageMesh_Node>
			Merge(const VoyageMesh_Node&, const VoyageMesh_Node&);

		static TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageMesh_Node>>
			RetrieveTipNodes
			(
				const std::vector<std::shared_ptr<VoyageMesh_Element>>&
			);

		static TnbVoyage_EXPORT void Merge(VoyageMesh_Edge&, VoyageMesh_Edge&);
		static TnbVoyage_EXPORT void Merge(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		static TnbVoyage_EXPORT void SetDeparture(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		static TnbVoyage_EXPORT void SetArrival(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);

		static TnbVoyage_EXPORT void Renumber(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);

	public:

		static TnbVoyage_EXPORT unsigned short verbose;

		// Default constructors [9/2/2023 Payvand]

		Voyage_Waypoints()
			: theSize_(0)
		{}


		// Public functions and operators [9/2/2023 Payvand]

		[[nodiscard]] const auto& Path() const { return thePath_; }
		[[nodiscard]] const auto& StarboardSizeFunction() const { return theStarboardSize_; }
		[[nodiscard]] const auto& PortSizeFunction() const { return thePortSize_; }
		[[nodiscard]] const auto& Profile() const { return theProfile_; }
		[[nodiscard]] const auto& GetInfo() const { return theInfo_; }

		[[nodiscard]] auto Size() const { return theSize_; }

		[[nodiscard]] const auto& Grid() const { return theGrid_; }

		[[nodiscard]] const auto& StarMesh() const { return theStarMesh_; }
		[[nodiscard]] const auto& PortMesh() const { return thePortMesh_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetStarboardSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theSize) { theStarboardSize_ = theSize; }
		void SetPortSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theSize) { thePortSize_ = theSize; }
		void SetInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }

		void SetSize(const Standard_Real theH) { theSize_ = theH; }

	};

}

#endif // !_Voyage_Waypoints_Header
