#pragma once
#ifndef _Geo2d_PolygonDelTri_Header
#define _Geo2d_PolygonDelTri_Header

#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class Geo2d_PolygonDelTri
		: public Global_Done
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Entity2d_Polygon>> thePolygons_;

		// result [7/12/2023 Payvand]

		std::shared_ptr<Entity2d_Triangulation> theTriangulation_;

	public:

		// default constructor [7/12/2023 Payvand]

		Geo2d_PolygonDelTri()
		{}

		// constructors [7/12/2023 Payvand]

		Geo2d_PolygonDelTri(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolys)
			: thePolygons_(thePolys)
		{}


		// Public functions and operators [7/12/2023 Payvand]

		const auto& Polygons() const { return thePolygons_; }
		const auto& Triangulation() const { return theTriangulation_; }

		TnbGeo_EXPORT void Perform();

		void SetPolygons(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolys)
		{
			thePolygons_ = thePolys;
		}

		void SetPolygons(std::vector<std::shared_ptr<Entity2d_Polygon>>&& thePolys)
		{
			thePolygons_ = std::move(thePolys);
		}

	};

}

#endif // !_Geo2d_PolygonDelTri_Header
