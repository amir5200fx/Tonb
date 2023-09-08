#pragma once
#ifndef _VoyageWP_Dist_Header
#define _VoyageWP_Dist_Header

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

		Standard_Integer NbWPs() const;

		const auto& Coord() const { return theCoord_; }
		const auto& WPs() const { return theWaypoints_; }
		const auto& MetricInfo() const { return theMetricInfo_; }
		const auto& MeshInfo() const { return theMeshInfo_; }
		const auto& Earth() const { return theEarth_; }

		auto MaxSubLev() const { return theMaxSubLev_; }

		void Perform();

		Standard_Real MinDistance() const;
		Standard_Real Distance(const Standard_Integer theIndex) const;
		Standard_Real DistanceWP(const Standard_Integer theIndex) const;

		Standard_Integer MaxStarAngle(const Standard_Real) const;
		Standard_Integer MaxPortAngle(const Standard_Real) const;

		void SetPoint(const Pnt2d& theCoord) { theCoord_ = theCoord; }
		void SetWPs(const std::shared_ptr<Entity2d_Polygon>& thePoly) { theWaypoints_ = thePoly; }
		void SetMetricInfo(const std::shared_ptr<Geo_MetricPrcsrAnIso_Info>& theInfo) { theMetricInfo_ = theInfo; }
		void SetMeshInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theMeshInfo_ = theInfo; }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }
		void SetMaxSubLev(const Standard_Integer theMaxLev) { theMaxSubLev_ = theMaxLev; }
	};

}

#endif // !_VoyageWP_Dist_Header
