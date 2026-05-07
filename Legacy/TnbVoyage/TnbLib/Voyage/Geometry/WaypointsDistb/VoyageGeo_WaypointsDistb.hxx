//#pragma once
//#ifndef _VoyageGeo_WaypointsDistb_Header
//#define _VoyageGeo_WaypointsDistb_Header
//
//#include <Global_Done.hxx>
//
//#include <memory>
//
//namespace tnbLib
//{
//
//	// Forward Declarations [7/10/2023 Payvand]
//
//	class Voyage_WptsGrid;
//	class VoyageGeo_Path;
//	class VoyageGeo_SizeFun;
//	class VoyageGeo_MetricFun;
//
//	class VoyageGeo_WaypointsDistb
//		: public Global_Done
//	{
//
//		/*private Data*/
//
//		std::shared_ptr<VoyageGeo_Path> theRef_;
//
//		std::shared_ptr<VoyageGeo_SizeFun> theSizeFun_;
//		std::shared_ptr<VoyageGeo_MetricFun> theMetricFun_;
//
//		Standard_Real theDeviation_;
//		Standard_Integer theMaxDeviation_;
//
//		// results [7/10/2023 Payvand]
//
//		std::shared_ptr<Voyage_WptsGrid> theGrid_;
//
//	public:
//
//		// default constructor [7/10/2023 Payvand]
//
//		VoyageGeo_WaypointsDistb()
//		{}
//
//
//		// constructors [7/10/2023 Payvand]
//
//
//		// Public functions and operators [7/10/2023 Payvand]
//
//		const auto& RefRoute() const { return theRef_; }
//
//		const auto& SizeFun() const { return theSizeFun_; }
//		const auto& MetricFun() const { return theMetricFun_; }
//
//		auto Deviation() const { return theDeviation_; }
//		auto MaxDeviation() const { return theMaxDeviation_; }
//
//		const auto& Grid() const { return theGrid_; }
//
//		void Perform();
//
//		void SetRefRoute(const std::shared_ptr<VoyageGeo_Path>& theRef) { theRef_ = theRef; }
//		void SetRefRoute(std::shared_ptr<VoyageGeo_Path>&& theRef) { theRef_ = std::move(theRef); }
//
//		void SetSizeFun(const std::shared_ptr<VoyageGeo_SizeFun>& theFun) { theSizeFun_ = theFun; }
//		void SetSizeFun(std::shared_ptr<VoyageGeo_SizeFun>&& theFun) { theSizeFun_ = std::move(theFun); }
//		void SetMetricFun(const std::shared_ptr<VoyageGeo_MetricFun>& theFun) { theMetricFun_ = theFun; }
//		void SetMetricFun(std::shared_ptr<VoyageGeo_MetricFun>&& theFun) { theMetricFun_ = std::move(theFun); }
//
//	};
//}
//
//#endif // !_VoyageGeo_WaypointsDistb_Header
