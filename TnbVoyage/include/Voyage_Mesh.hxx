#pragma once
#ifndef _Voyage_Mesh_Header
#define _Voyage_Mesh_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/20/2023 Payvand]

	class Voyage_WptsGrid;
	class VoyageGeo_Path;
	class VoyageGeo_SizeFun;
	class VoyageGeo_MetricFun;
	class VoyageField_Earth;
	class Mesh_Curve_Info;

	struct Voyage_Mesh_Cache
	{

		static std::shared_ptr<Entity2d_Polygon> thePrevArea_;
	};

	class Voyage_Mesh
		: public Voyage_Mesh_Cache
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path> theRef_;

		std::shared_ptr<Geo2d_MetricPrcsrAnIso> thePrcsr_;
		std::shared_ptr<Mesh_Curve_Info> theCurveInfo_;

		std::shared_ptr<VoyageField_Earth> theEarth_;

		Standard_Real theResolution_;
		Standard_Integer theMaxDeviation_;


		// results [7/21/2023 Payvand]

		std::shared_ptr<Voyage_WptsGrid> theGrid_;

		// Private functions and operators [7/20/2023 Payvand]

		TnbVoyage_EXPORT Standard_Boolean IsValid(const Pnt2d& theCoord) const;

	public:

		// default constructor [7/20/2023 Payvand]

		Voyage_Mesh()
		{}

		// constructors [7/20/2023 Payvand]


		// Public functions and operators [7/20/2023 Payvand]

		const auto& RefRoute() const { return theRef_; }

		const auto& MetricPrcsr() const { return thePrcsr_; }

		const auto& CurveInfo() const { return theCurveInfo_; }

		const auto& Earth() const { return theEarth_; }

		auto Resolution() const { return theResolution_; }
		auto MaxDeviation() const { return theMaxDeviation_; }

		const auto& Grid() const { return theGrid_; }

		TnbVoyage_EXPORT void Perform();

	};

}

#endif // !_Voyage_Mesh_Header
