#pragma once
#ifndef _GeoExtrude_Polyline_Header
#define _GeoExtrude_Polyline_Header

#include <Geo_Module.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class GeoExtrude_Polyline
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolyline_;

		Standard_Real theZ0_;
		Standard_Real theZ1_;


		// Result [2/19/2023 Payvand]

		std::shared_ptr<Entity3d_Triangulation> theMesh_;

	public:

		// default constructor [2/19/2023 Payvand]

		GeoExtrude_Polyline()
			: theZ0_(0)
			, theZ1_(0)
		{}

		// constructors [2/19/2023 Payvand]


		// Public functions and operators [2/19/2023 Payvand]

		const auto& Polyline() const
		{
			return thePolyline_;
		}

		auto Z0() const
		{
			return theZ0_;
		}

		auto Z1() const
		{
			return theZ1_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbGeo_EXPORT void Perform();

		void SetPolyline(const std::shared_ptr<Entity2d_Polygon>& thePolyline)
		{
			thePolyline_ = thePolyline;
		}

		void SetZ0(const Standard_Real theZ)
		{
			theZ0_ = theZ;
		}

		void SetZ1(const Standard_Real theZ)
		{
			theZ1_ = theZ;
		}

	};
}

#endif // !_GeoExtrude_Polyline_Header
