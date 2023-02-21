#pragma once
#ifndef _GeoSlicer2d_PolyLine_Header
#define _GeoSlicer2d_PolyLine_Header

#include <Geo_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class GeoSlicer2d_PolyLine
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Triangulation> theMesh_;
		std::shared_ptr<Entity2d_Polygon> thePolyline_;


		// Results [2/19/2023 Payvand]

		std::shared_ptr<Entity2d_Triangulation> theClipped_;

	public:

		// default constructor [2/19/2023 Payvand]

		GeoSlicer2d_PolyLine()
		{}

		// constructors [2/19/2023 Payvand]


		// Public functions and operators [2/19/2023 Payvand]

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const auto& Polyline() const
		{
			return thePolyline_;
		}

		const auto& Clipped() const
		{
			return theClipped_;
		}

		TnbGeo_EXPORT void Perform();

		void SetMesh(const std::shared_ptr<Entity2d_Triangulation>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetPolyline(const std::shared_ptr<Entity2d_Polygon>& thePolyline)
		{
			thePolyline_ = thePolyline;
		}

	};
}

#endif // !_GeoSlicer2d_PolyLine_Header
