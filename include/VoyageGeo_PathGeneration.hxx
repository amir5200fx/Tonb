#pragma once
#ifndef _VoyageGeo_PathGeneration_Header
#define _VoyageGeo_PathGeneration_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/27/2023 Payvand]
	class Cad_GeomCurve;
	class Cad_GeomSurface;
	class Mesh_Curve_Info;
	class Geo_MetricPrcsrAnIso_Info;

	class VoyageGeo_PathGeneration
		: public Global_Done
	{

		/*Private Data*/

		std::vector<Pnt2d> theCoords_;
		std::shared_ptr<Cad_GeomSurface> theSurface_;
		std::shared_ptr<Geo2d_MetricPrcsrAnIso> theMetricPrcsr_;

		std::shared_ptr<Mesh_Curve_Info> theCurveInfo_;

		// results [7/27/2023 Payvand]

		std::vector<std::shared_ptr<Cad_GeomCurve>> thePaths_;

	public:


		// default constructor [7/27/2023 Payvand]

		VoyageGeo_PathGeneration()
		{}

		// constructors [7/27/2023 Payvand]

		VoyageGeo_PathGeneration
		(
			const std::vector<Pnt2d>& theCoords, 
			const std::shared_ptr<Cad_GeomSurface>& theSurface, 
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
		)
			: theCoords_(theCoords)
			, theSurface_(theSurface)
			, theMetricPrcsr_(thePrcsr)
			, theCurveInfo_(theInfo)
		{}


		// Public functions and operators [7/27/2023 Payvand]

		const auto& Coords() const { return theCoords_; }
		const auto& Surface() const { return theSurface_; }

		const auto& CurveInfo() const { return theCurveInfo_; }
		const auto& MetricPrcsr() const { return theMetricPrcsr_; }

		const auto& Paths() const { return thePaths_; }

		TnbVoyage_EXPORT void Perform();

		void SetCoords(const std::vector<Pnt2d>& theCoords) { theCoords_ = theCoords; }
		void SetSurface(const std::shared_ptr<Cad_GeomSurface>& theSurface) { theSurface_ = theSurface; }
		void SetMetricPrsr(const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& thePrcsr) { theMetricPrcsr_ = thePrcsr; }

		void SetCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveInfo_ = theInfo; }

		static Standard_Real CalcMinAngularDistance(const Pnt2d& theP0, const Pnt2d& theP1);

	};
}

#endif // !_VoyageGeo_PathGeneration_Header
