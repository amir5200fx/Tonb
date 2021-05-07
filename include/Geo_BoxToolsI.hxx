#pragma once
#include <Entity_Box.hxx>
namespace tnbLib
{
	template<class Point>
	inline Standard_Boolean 
		Geo_BoxTools::IsPointInside
		(
			const Point & thePt,
			const Box<Point>& theBox
		)
	{
		return theBox.IsInside(thePt);
	}

	template<class Point>
	inline Standard_Boolean 
		Geo_BoxTools::IsBoxInside
		(
			const Box<Point>& theBox,
			const Box<Point>& theTarget
		)
	{
		return Box<Point>::IsInside(theBox, theTarget);
	}

	template<class Point>
	inline Standard_Boolean 
		Geo_BoxTools::IsIntersect
		(
			const Box<Point>& theBox0,
			const Box<Point>& theBox1
		)
	{
		return theBox0.IsIntersect(theBox1);
	}

	template<class Point>
	inline typename Geo_BoxTools::Box<Point> 
		Geo_BoxTools::Union
		(
			const Box<Point>& theBox0,
			const Box<Point>& theBox1
		)
	{
		return Box<Point>::Union(theBox0, theBox1);
	}

	template<class Point>
	inline typename Geo_BoxTools::Box<Point> 
		Geo_BoxTools::GetBox
		(
			const std::vector<Point>& theCoords,
			const Standard_Real theOffset
		)
	{
		auto b = Entity_Box<Point>::BoundingBoxOf(theCoords);
		if (theOffset)
		{
			b.Expand(theOffset);
		}
		return std::move(b);
	}

	template<class Point>
	inline typename Geo_BoxTools::Triangulation<Point> 
		Geo_BoxTools::GetTriangulation
		(
			const std::vector<Box<Point>>& theBoxes
		)
	{
		Triangulation<Point> tri;
		GetTriangulation(theBoxes, tri);
		return std::move(tri);
	}
}