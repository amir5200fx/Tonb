#pragma once
#ifndef _Voyage_Waypoints_Header
#define _Voyage_Waypoints_Header

#include <Voyage_PathDir.hxx>
#include <Voyage_Module.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/2/2023 Payvand]
	class Voyage_WptsGrid;
	class Voyage_MetricInfo;
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

		std::shared_ptr<Voyage_MetricInfo> theInfo_;


		// results [9/2/2023 Payvand]

		std::shared_ptr<Voyage_WptsGrid> theGrid_;

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

		static TnbVoyage_EXPORT void Merge(VoyageMesh_Edge&, VoyageMesh_Edge&);
		static TnbVoyage_EXPORT void Merge(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		static TnbVoyage_EXPORT void SetDeparture(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);
		static TnbVoyage_EXPORT void SetArrival(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);

		static TnbVoyage_EXPORT void Renumber(const std::vector<std::shared_ptr<VoyageMesh_Edge>>&);

	public:

		static TnbVoyage_EXPORT unsigned short verbose;

		// Default constructors [9/2/2023 Payvand]

		Voyage_Waypoints()
		{}


		// Public functions and operators [9/2/2023 Payvand]

		const auto& Path() const { return thePath_; }
		const auto& StarboardSizeFunction() const { return theStarboardSize_; }
		const auto& PortSizeFunction() const { return thePortSize_; }
		const auto& GetInfo() const { return theInfo_; }

		const auto& Grid() const { return theGrid_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetStarboardSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theSize) { theStarboardSize_ = theSize; }
		void SetPortSizeFunction(const std::shared_ptr<Geo2d_SizeFunction>& theSize) { thePortSize_ = theSize; }
		void SetInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }

	};

}

#endif // !_Voyage_Waypoints_Header
