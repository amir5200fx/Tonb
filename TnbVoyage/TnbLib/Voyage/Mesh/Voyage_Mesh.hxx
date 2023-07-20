#pragma once
#ifndef _Voyage_Mesh_Header
#define _Voyage_Mesh_Header

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

		std::shared_ptr<VoyageGeo_SizeFun> theSizeFun_;
		std::shared_ptr<VoyageGeo_MetricFun> theMetricFun_;

		std::shared_ptr<VoyageField_Earth> theEarth_;

		// Private functions and operators [7/20/2023 Payvand]

		static Standard_Boolean CheckIntersection(const Pnt2d& theCoord, const )

	public:

		// default constructor [7/20/2023 Payvand]

		Voyage_Mesh()
		{}

		// constructors [7/20/2023 Payvand]


		// Public functions and operators [7/20/2023 Payvand]

		const auto& Path() const { return theRef_; }

		const auto& SizeFun() const { return theSizeFun_; }
		const auto& MetricFun() const { return theMetricFun_; }

		const auto& Earth() const { return theEarth_; }

		void Perform();

	};

}

#endif // !_Voyage_Mesh_Header
