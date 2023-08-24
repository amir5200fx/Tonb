#pragma once
#ifndef _VoyageMesh_BaseSize_Header
#define _VoyageMesh_BaseSize_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [8/15/2023 aamir]
	class VoyageMesh_BaseSizeInfo;
	class Geo_ProfileFun;

	class VoyageMesh_BaseSize
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageMesh_BaseSizeInfo> theInfo_;

		std::shared_ptr<Geo2d_MetricPrcsrAnIso> theMetrics_;
		std::vector<std::shared_ptr<Entity2d_Polygon>> thePath_;

		// Results [8/16/2023 aamir]

		std::shared_ptr<std::vector<std::vector<Standard_Real>>> theHs_;

		// Private functions and operators [8/15/2023 aamir]

		TnbVoyage_EXPORT Standard_Real RetrieveHmax(const Standard_Integer id, const std::vector<Standard_Real>&) const;
		TnbVoyage_EXPORT Standard_Real RetrieveH0(const Standard_Integer id, const std::vector<Standard_Real>&) const;
		TnbVoyage_EXPORT Standard_Real RetrieveH1(const Standard_Integer id, const std::vector<Standard_Real>&) const;

		TnbVoyage_EXPORT std::vector<Standard_Real> 
			CalcHs
			(
				const Standard_Integer id, 
				const Entity2d_Polygon&, 
				const std::vector<Standard_Real>&
			) const;

		TnbVoyage_EXPORT std::shared_ptr<Geo_ProfileFun>
			CalcProfile
			(
				const Standard_Real theH0, 
				const Standard_Real theH1,
				const Standard_Real theHm
			) const;

	public:

		static TnbVoyage_EXPORT Standard_Real TRANS_POINT_CONST;

		// default constructor [8/15/2023 aamir]

		VoyageMesh_BaseSize()
		{}

		// constructors [8/15/2023 aamir]

		VoyageMesh_BaseSize
		(
			const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePath,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMetrics,
			const std::shared_ptr<VoyageMesh_BaseSizeInfo>& theInfo
		)
			: thePath_(thePath)
			, theMetrics_(theMetrics)
			, theInfo_(theInfo)
		{}

		// Public functions and operators [8/15/2023 aamir]

		const auto& GetInfo() const { return theInfo_; }

		const auto& Metrics() const { return theMetrics_; }
		const auto& Path() const { return thePath_; }

		const auto& Hs() const { return theHs_; }

		TnbVoyage_EXPORT void Perform();

		void SetInfo(const std::shared_ptr<VoyageMesh_BaseSizeInfo>& theInfo) { theInfo_ = theInfo; }

		void SetMetrics(const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMetrics) { theMetrics_ = theMetrics; }
		void SetPath(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePath) { thePath_ = thePath; }
		void SetPath(std::vector<std::shared_ptr<Entity2d_Polygon>>&& thePath) { thePath_ = std::move(thePath); }
	};
}

#endif // !_VoyageMesh_BaseSize_Header
