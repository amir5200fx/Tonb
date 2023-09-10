#pragma once
#ifndef _VoyageWP_Dist_Header
#define _VoyageWP_Dist_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageGeo_Earth;
	class Mesh_Curve_Info;
	class Geo_MetricPrcsrAnIso_Info;

	class VoyageWP_Dist
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Earth> theEarth_;
		std::shared_ptr<Entity2d_Polygon> theWaypoints_;

		Pnt2d theCoord_;

		Standard_Integer theMaxSubLev_;
		std::shared_ptr<Geo_MetricPrcsrAnIso_Info> theMetricInfo_;
		std::shared_ptr<Mesh_Curve_Info> theMeshInfo_;

		//- results

		std::vector<Standard_Real> theWPdists_;
		std::vector<Standard_Real> theDists_;

	public:

		//- default constructor

		VoyageWP_Dist()
			: theMaxSubLev_(0)
		{}

		//- constructors

		//- Public functions and operators

		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer NbWPs() const;

		[[nodiscard]] const auto& Coord() const { return theCoord_; }
		[[nodiscard]] const auto& WPs() const { return theWaypoints_; }
		[[nodiscard]] const auto& MetricInfo() const { return theMetricInfo_; }
		[[nodiscard]] const auto& MeshInfo() const { return theMeshInfo_; }
		[[nodiscard]] const auto& Earth() const { return theEarth_; }

		[[nodiscard]] auto MaxSubLev() const { return theMaxSubLev_; }

		TnbVoyage_EXPORT void Perform();

		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer MinDistanceId() const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real MinDistance() const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real Distance(const Standard_Integer theIndex) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real DistanceWP(const Standard_Integer theIndex) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real DistanceWP(const Standard_Integer from, const Standard_Integer to) const;

		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer MaxStarAngle(const Standard_Real) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Integer MaxPortAngle(const Standard_Real) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real StarAngle(const Standard_Integer theMinDist, const Standard_Integer theIndex) const;
		[[nodiscard]] TnbVoyage_EXPORT Standard_Real PortAngle(const Standard_Integer theMinDist, const Standard_Integer theIndex) const;

		void SetPoint(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetWPs(const std::shared_ptr<Entity2d_Polygon>& thePoly) { theWaypoints_ = thePoly; }
		void SetMetricInfo(const std::shared_ptr<Geo_MetricPrcsrAnIso_Info>& theInfo) { theMetricInfo_ = theInfo; }
		void SetMeshInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theMeshInfo_ = theInfo; }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }
		void SetMaxSubLev(const Standard_Integer theMaxLev) { theMaxSubLev_ = theMaxLev; }
	};

}

#endif // !_VoyageWP_Dist_Header
