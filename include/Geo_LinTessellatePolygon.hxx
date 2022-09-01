#pragma once
#ifndef _Geo_LinTessellatePolygon_Header
#define _Geo_LinTessellatePolygon_Header

#include <Geo_TessellatePolygon.hxx>

//#include "Entity2d_Polygon.hxx"

namespace tnbLib
{

	template<class Point>
	class Geo_LinTessellatePolygon
		: public Geo_TessellatePolygon<Point>
	{

		/*Private Data*/

	public:

		// default constructor [5/20/2022 Amir]

		Geo_LinTessellatePolygon()
		{}


		// constructors [5/20/2022 Amir]

		explicit Geo_LinTessellatePolygon
		(
			const std::shared_ptr<Entity_Polygon<Point>>& thePoly
		)
			: Geo_TessellatePolygon<Point>(thePoly)
		{}


		// override functions and operators [5/20/2022 Amir]

		void Tessellate(const Standard_Integer nbLevels) override;


		// public functions and operators [5/20/2022 Amir]

		static std::vector<Point> 
			CalcInners
			(
				const Point&, const Point&, 
				const Standard_Real du, 
				const Standard_Integer n
			);
	};
}

#include <Geo_LinTessellatePolygonI.hxx>

#endif // !_Geo_LinTessellatePolygon_Header
