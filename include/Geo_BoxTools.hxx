#pragma once
#ifndef _Geo_BoxTools_Header
#define _Geo_BoxTools_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Geo_Module.hxx>
#include <Geo_Traits.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_BoxTools
	{

	public:

		static Standard_Real Triangulation_Merge_Radius;
		static Standard_Real Triangulation_Merge_Resolution;

		template<class Point>
		using Box = Entity_Box<Point>;

		template<class Point>
		using Triangulation = Entity_StaticData<Point, typename entity_connectivity_type<Point>::type, false>;

		template<class Point>
		static Standard_Boolean IsPointInside(const Point& thePt, const Box<Point>& theBox);

		template<class Point>
		static Standard_Boolean IsBoxInside(const Box<Point>& theBox, const Box<Point>& theTarget);

		template<class Point>
		static Standard_Boolean IsIntersect(const Box<Point>& theBox0, const Box<Point>& theBox1);

		template<class Point>
		static Box<Point> Union(const Box<Point>& theBox0, const Box<Point>& theBox1);

		template<class Point>
		static Box<Point> Intersect(const Box<Point>& theBox0, const Box<Point>& theBox1);

		template<class Point>
		static Box<Point> GetBox(const Point& theCoord, const Standard_Real theRadius);
		
		template<class Point>
		static Box<Point> GetBox(const std::vector<Point>& theCoords, const Standard_Real theOffset);

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Triangulation> Triangulate(const Entity2d_Box&);
		std::shared_ptr<Entity3d_Triangulation> Triangulate(const Entity3d_Box&);

		static TnbGeo_EXPORT void GetTriangulation(const std::vector<Entity2d_Box>& theBoxes, Entity2d_Triangulation& theTri);
		static TnbGeo_EXPORT void GetTriangulation(const std::vector<Entity3d_Box>& theBoxes, Entity3d_Tetrahedralization& theTri);
		static TnbGeo_EXPORT void GetTriangulation(const std::vector<std::shared_ptr<Entity3d_Box>>& theBoxes, Entity3d_Tetrahedralization& theTri);

		template<class Point>
		static Triangulation<Point> GetTriangulation(const std::vector<Box<Point>>& theBoxes);

	};
}

#include <Geo_BoxToolsI.hxx>

#endif // !_Geo_BoxTools_Header