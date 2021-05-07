#pragma once
#ifndef _Geo_Tools_Header
#define _Geo_Tools_Header

#include <Dir2d.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

#include <Entity_Segment.hxx>
#include <Entity_Line.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Entity2d_TriangleFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	class Geo_Tools
	{

	public:

		class IntersectEntity2d
		{

		public:

			bool Result = false;

			IntersectEntity2d()
			{}

			virtual bool IsPoint() const
			{
				return false;
			}

			virtual bool IsSegment() const
			{
				return false;
			}

			virtual bool IsLine() const
			{
				return false;
			}
		};

		class PointIntersectEntity2d
			: public IntersectEntity2d
		{

		public:

			Pnt2d IntPnt;

			PointIntersectEntity2d()
			{
				Result = true;
			}

			PointIntersectEntity2d(Pnt2d&& pt)
				: IntPnt(std::move(pt))
			{
				Result = true;
			}

			bool IsPoint() const override
			{
				return true;
			}
		};

		class SegmentIntersectEntity2d
			: public IntersectEntity2d
		{

		public:

			Entity2d_Segment Segment;

			SegmentIntersectEntity2d()
			{
				Result = true;
			}

			SegmentIntersectEntity2d(Entity2d_Segment&& seg)
				: Segment(std::move(seg))
			{
				Result = true;
			}

			bool IsSegment() const override
			{
				return true;
			}
		};

		class LineIntersectEntity2d
			: public IntersectEntity2d
		{

		public:

			Entity2d_Line Line;

			LineIntersectEntity2d()
			{
				Result = true;
			}

			LineIntersectEntity2d(Entity2d_Line&& line)
				: Line(std::move(line))
			{
				Result = true;
			}

			bool IsLine() const override
			{
				return true;
			}
		};

		static TnbGeo_EXPORT Pnt2d
			GetIntersectionPoint
			(
				const std::shared_ptr<IntersectEntity2d>&
			);

		static TnbGeo_EXPORT Entity2d_Segment
			GetIntersectionSegment
			(
				const std::shared_ptr<IntersectEntity2d>&
			);

		static inline Standard_Integer
			Round
			(
				const Standard_Real x
			);

		static inline Standard_Real
			DegToRadian
			(
				const Standard_Real Degree
			);

		static inline Standard_Real
			RadianToDegree
			(
				const Standard_Real Radian
			);

		static TnbGeo_EXPORT Standard_Real
			SquareDistance_cgal
			(
				const Pnt2d& theQ,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT Standard_Real
			SquareDistance_cgal
			(
				const Pnt3d& theQ,
				const Pnt3d& theP0,
				const Pnt3d& theP1
			);

		static inline Standard_Real
			Distance_cgal
			(
				const Pnt2d& theQ,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static inline Standard_Real
			Distance_cgal
			(
				const Pnt3d& theQ,
				const Pnt3d& theP0,
				const Pnt3d& theP1
			);

		static TnbGeo_EXPORT Standard_Real
			SquareDistance_cgal
			(
				const Pnt3d& theQ,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Real
			Distance_cgal
			(
				const Pnt3d& theQ,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static TnbGeo_EXPORT Standard_Real
			SquareDistanceSegments_cgal
			(
				const Pnt3d& theQ0,
				const Pnt3d& theQ1,
				const Pnt3d& theP0,
				const Pnt3d& theP1
			);

		static inline Standard_Real
			DistanceSegments_cgal
			(
				const Pnt3d& theQ0,
				const Pnt3d& theQ1,
				const Pnt3d& theP0,
				const Pnt3d& theP1
			);

		static TnbGeo_EXPORT Standard_Real
			Oriented_cgal
			(
				const Pnt2d& theQ,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT Standard_Real
			Oriented_cgal
			(
				const Pnt3d& theQ,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Real
			Area_cgal
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2
			);

		static inline Standard_Boolean
			IsPointRightEdge_cgal
			(
				const Pnt2d& Point,
				const Pnt2d& P0,
				const Pnt2d& P1
			);

		static inline Standard_Boolean
			IsPointRightFacet_cgal
			(
				const Pnt3d& thePoint,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Boolean
			IsPointLeftEdge_cgal
			(
				const Pnt2d& Point,
				const Pnt2d& P0,
				const Pnt2d& P1
			);

		static inline Standard_Boolean
			IsPointLeftFacet_cgal
			(
				const Pnt3d& thePoint,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Boolean
			IsPointInsideTriangle_cgal
			(
				const Pnt2d& Point,
				const Pnt2d& P0,
				const Pnt2d& P1,
				const Pnt2d& P2
			);

		static inline Standard_Boolean
			IsPointInsideTriangleCW_cgal
			(
				const Pnt2d& Point,
				const Pnt2d& P0,
				const Pnt2d& P1,
				const Pnt2d& P2
			);

		static TnbGeo_EXPORT Standard_Boolean
			HasIntersection_cgal
			(
				const Pnt2d& theQ0,
				const Pnt2d& theQ1,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static inline Standard_Boolean
			IsPairedTwoSegments
			(
				const Standard_Integer v1,
				const Standard_Integer v2,
				const Standard_Integer q1,
				const Standard_Integer q2
			);

		static inline Standard_Boolean
			IsIntersect
			(
				const Standard_Real U0,
				const Standard_Real U1,
				const Standard_Real V0,
				const Standard_Real V1
			);

		static inline Standard_Boolean
			IsOneCommonPointTwoSegments
			(
				const Standard_Integer v1,
				const Standard_Integer v2,
				const Standard_Integer q1,
				const Standard_Integer q2
			);

		static inline Standard_Boolean
			IsOneCommonPointTwoTriangles
			(
				const Standard_Integer v1,
				const Standard_Integer v2,
				const Standard_Integer v3,
				const Standard_Integer q1,
				const Standard_Integer q2,
				const Standard_Integer q3
			);

		static TnbGeo_EXPORT Standard_Boolean
			IsCcwOrder_cgal
			(
				const std::vector<Pnt2d>& thePts
			);

		static TnbGeo_EXPORT Standard_Boolean
			IsSimple_cgal
			(
				const std::vector<Pnt2d>& thePts
			);

		static TnbGeo_EXPORT Pnt2d 
			IntersectionTwoLines
			(
				const Pnt2d& P0,
				const Dir2d& t0,
				const Pnt2d& P1,
				const Dir2d& t1,
				const Standard_Real theAngTol
			);

		static TnbGeo_EXPORT std::shared_ptr<IntersectEntity2d> 
			Intersection_cgal
			(
				const Entity2d_Segment&, 
				const Entity2d_Segment&
			);

		static TnbGeo_EXPORT std::shared_ptr<IntersectEntity2d>
			Intersection_cgal
			(
				const Entity2d_Line&,
				const Entity2d_Line&
			);

		static TnbGeo_EXPORT std::vector<Pnt2d> 
			Intersecction_cgal
			(
				const Entity2d_Triangle& tri0,
				const Entity2d_Triangle& tri1
			);

		static inline Pnt2d 
			ProjectPtAtSegment
			(
				const Pnt2d& thePt,
				const Pnt2d& theP0, 
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Chain>
			RetrieveChain
			(
				const Entity2d_Polygon& thePoly
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Chain>
			RetrieveChain
			(
				const Entity3d_Polygon& thePoly
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Chain>
			RetrieveChain
			(
				const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePoly
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Chain>
			RetrieveChain
			(
				const std::vector<std::shared_ptr<Entity3d_Polygon>>& thePoly
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Chain>
			RetrieveChain
			(
				const std::vector<std::shared_ptr<Entity3d_Chain>>& theChains
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Triangulation>
			Triangulation
			(
				const Entity3d_Chain& theChain
			);

		static TnbGeo_EXPORT std::vector<Entity2d_Triangle> 
			Intersections
			(
				const std::vector<Entity2d_Triangle>& theTriangles
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Polygon> 
			GetPolygon
			(
				const Entity2d_Triangle&
			);

		static TnbGeo_EXPORT std::vector<Entity2d_Triangle> 
			GetTriangles
			(
				const Entity2d_Triangulation&
			);

		template<class Type>
		static size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<std::shared_ptr<Type>>& theSorted,
				Standard_Real(*xValue)(const std::shared_ptr<Type>&)
			);

		static TnbGeo_EXPORT size_t 
			FindSpan
			(
				const Standard_Real x, 
				const std::vector<Standard_Real>& theSorted
			);

		static TnbGeo_EXPORT void 
			CheckSorted
			(
				const std::vector<Standard_Real>& theSorted,
				const char* theName
			);
	};
}

#include <Geo_ToolsI.hxx>

#endif // !_Geo_Tools_Header
