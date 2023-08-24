#pragma once
#ifndef _Voyage_Mesh2_Header
#define _Voyage_Mesh2_Header

#include <Voyage_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class Voyage_Mesh2
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> theRefRoute_;

		Standard_Real theResolution_;
		Standard_Integer theMaxDeviation_;

		std::function<Standard_Boolean(const Pnt2d&)> is_valid_fun;

	public:

		// default constructor [8/5/2023 Payvand]

		Voyage_Mesh2()
		{}

		// constructors [8/5/2023 Payvand]


		// Public functions and operators [8/5/2023 Payvand]

		const auto& RefRoute() const { return theRefRoute_; }

		auto Resolution() const { return theResolution_; }
		auto MaxDeviation() const { return theMaxDeviation_; }

		void Perform();

		void SetRefRoute(const std::shared_ptr<Entity2d_Polygon>& theRoute) { theRefRoute_ = theRoute; }
		void SetRefRoute(std::shared_ptr<Entity2d_Polygon>&& theRoute) { theRefRoute_ = std::move(theRoute); }
		void SetFunction(std::function<Standard_Boolean(const Pnt2d&)>& theFunction) { is_valid_fun = theFunction; }
	};
}

#endif // !_Voyage_Mesh2_Header
