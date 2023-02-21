#pragma once
#ifndef _Geo_Tools_Header
#define _Geo_Tools_Header

#include <Dir2d.hxx>
#include <Dir3d.hxx>
#include <Vec3d.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>

#include <Geo2d_GraphFwd.hxx>
#include <Entity_Segment.hxx>
#include <Entity_Line.hxx>
#include <Entity_Triangle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Entity2d_ChainFwd.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Entity2d_TriangleFwd.hxx>
#include <Entity3d_TriangleFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity3d_TriangulationFwd.hxx>

#include <vector>
#include <memory>

#include <armadillo.h>

class gp_Pln;
class gp_Lin2d;
class gp_Lin;
class Poly_Triangulation;
class Poly_Triangle;

namespace tnbLib
{

	class Geo_Tools
	{

	public:

		static TnbGeo_EXPORT const Standard_Real OnePerTwo;
		static TnbGeo_EXPORT const Standard_Real OnePerThree;
		static TnbGeo_EXPORT const Standard_Real OnePerFour;
		static TnbGeo_EXPORT const Standard_Real OnePerSix;


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

		static inline Standard_Boolean 
			IsZero
			(
				const Standard_Real x, 
				const Standard_Real epsilon = gp::Resolution()
			);

		static TnbGeo_EXPORT Standard_Real MachineEpsilon();

		static TnbGeo_EXPORT arma::mat 
			CalcRotationMatrix(const Dir3d&, const Dir3d&);

		static TnbGeo_EXPORT std::tuple<Pnt2d, Pnt2d, Pnt2d, arma::mat> 
			ProjectToPlane
			(
				const Pnt3d& theP0, 
				const Pnt3d& theP1, 
				const Pnt3d& theP2
			);

		static std::tuple<Standard_Real, Standard_Real, Standard_Real, Standard_Real>
			GetPlaneCoeff(const gp_Pln&);

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

		template<class Point>
		static Point CalcCentre(const Point& theP0, const Point& theP1);

		template<class Point>
		static Point CalcCentre(const Point& theP0, const Point& theP1, const Point& theP2);

		static TnbGeo_EXPORT Pnt3d
			CalcCentre
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1, 
				const Pnt3d& theP2, 
				const Pnt3d& theP3
			);

		static TnbGeo_EXPORT Standard_Real 
			CalcLength
			(
				const Entity2d_Polygon&
			);

		static inline Standard_Real 
			CalcSquareDistancePointFromSegment
			(
				const Pnt2d& thePoint, 
				const Entity_Segment<const Pnt2d&>&
			);

		static TnbGeo_EXPORT Standard_Real 
			CalcSquareDistancePointFromSegment
			(
				const Pnt2d& thePoint,
				const Pnt2d& theP0, 
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT Standard_Real
			CalcSquareDistancePointFromTriangle
			(
				const Pnt3d& thePoint,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static TnbGeo_EXPORT Standard_Real
			CalcSquareDistancePointFromTriangle_cgal
			(
				const Pnt3d& thePoint,
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Real 
			CalcSquareDistancePointFromTriangle
			(
				const Pnt3d& thePoint,
				const Entity_Triangle<const Pnt3d&>& theTriangle
			);

		static TnbGeo_EXPORT Standard_Real
			CalcSquareDistanceSegmentFromSegment_Eberly
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theQ0,
				const Pnt3d& theQ1
			);

		static inline Standard_Real
			CalcSquareDistanceSegmentFromSegment_Eberly
			(
				const Entity_Segment<const Pnt3d&>& theSeg0,
				const Entity_Segment<const Pnt3d&>& theSeg1
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
			SquareDistance_cgal
			(
				const Pnt3d& thePoint,
				const gp_Pln& thePlane
			);

		static inline Standard_Real 
			Distance_cgal
			(
				const Pnt3d& thePoint,
				const gp_Pln& thePlane
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

		static TnbGeo_EXPORT Standard_Real 
			Oriented_Shewchuk
			(
				const Pnt3d& theCoord, 
				const Pnt3d& P1,
				const Pnt3d& P2,
				const Pnt3d& P3
			);

		static TnbGeo_EXPORT Standard_Real 
			Oriented_Fast
			(
				const Pnt3d& theCoord,
				const Pnt3d& P1,
				const Pnt3d& P2,
				const Pnt3d& P3
			);

		static inline Standard_Real
			Area_cgal
			(
				const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Pnt2d& theP2
			);

		static inline Standard_Real 
			Volume_cgal
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1, 
				const Pnt3d& theP2,
				const Pnt3d& theP3
			);

		static inline Standard_Boolean 
			IsPointRightEdge
			(
				const Pnt2d& thePoint,
				const Pnt2d& theP0,
				const Pnt2d& theP1
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
			IsPointRightFacet_Shewchuk
			(
				const Pnt3d& thePoint, 
				const Pnt3d& theP0,
				const Pnt3d& theP1, 
				const Pnt3d& theP2
			);

		static inline Standard_Boolean 
			IsPointRightFacet_Fast
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
			IsPointLeftFacet_Shewchuk
			(
				const Pnt3d& thePoint, 
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static inline Standard_Boolean 
			IsPointLeftFacet_Fast
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

		static inline Standard_Boolean 
			IsPointInsideTetrahedron_cgal
			(
				const Pnt3d& theCoord,
				const Pnt3d& theP0,
				const Pnt3d& theP1, 
				const Pnt3d& theP2,
				const Pnt3d& theP3
			);

		static TnbGeo_EXPORT Standard_Boolean
			HasIntersection_cgal
			(
				const Pnt2d& theQ0,
				const Pnt2d& theQ1,
				const Pnt2d& theP0,
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT Standard_Boolean
			IsIntersectionSegmentTriangle_cgal
			(
				const Pnt3d& theP0, 
				const Pnt3d& theP1, 
				const Pnt3d& theQ0,
				const Pnt3d& theQ1,
				const Pnt3d& theQ2
			);

		static TnbGeo_EXPORT Standard_Boolean
			IsIntersectionTwoTriangles_cgal
			(
				const Pnt3d& theP0, 
				const Pnt3d& theP1,
				const Pnt3d& theP2, 
				const Pnt3d& theQ0,
				const Pnt3d& theQ1,
				const Pnt3d& theQ2
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
			IsPairedTwoTriangles
			(
				const Standard_Integer v1, 
				const Standard_Integer v2, 
				const Standard_Integer v3,
				const Standard_Integer q1, 
				const Standard_Integer q2, 
				const Standard_Integer q3
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

		static inline Standard_Boolean 
			IsOneCommonPointSegmentTriangle
			(
				const Standard_Integer v1,
				const Standard_Integer v2,
				const Standard_Integer q1,
				const Standard_Integer q2,
				const Standard_Integer q3
			);

		static TnbGeo_EXPORT Standard_Boolean
			IsCcwOrder
			(
				const std::vector<Pnt2d>& thePts
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

		static inline Vec3d 
			CalcNormal
			(
				const Pnt3d& theP0,
				const Pnt3d& theP1,
				const Pnt3d& theP2
			);

		static TnbGeo_EXPORT Pnt3d
			ProjectToPlane_cgal
			(
				const Pnt3d& thePoint, 
				const gp_Pln& thePlane
			);

		static TnbGeo_EXPORT Pnt2d 
			ProjectToLine_cgal
			(
				const Pnt2d& pt, 
				const Entity2d_Line& line
			);

		static TnbGeo_EXPORT Pnt2d
			ProjectToLine_cgal
			(
				const Pnt2d& pt,
				const Entity2d_LineRef& line
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

		static TnbGeo_EXPORT std::pair<Pnt2d, Standard_Boolean> 
			IntersectTwoLines
			(
				const Pnt2d& p0, 
				const Dir2d& t0, 
				const Pnt2d& p1, 
				const Dir2d& t1,
				Standard_Real& gamma0, 
				Standard_Real& gamma1,
				const Standard_Real tol = 1.0E-6
			);

		static TnbGeo_EXPORT std::pair<Pnt2d, Standard_Boolean>
			IntersectTwoLines
			(
				const Pnt2d& p0,
				const Vec2d& t0,
				const Pnt2d& p1,
				const Vec2d& t1,
				Standard_Real& gamma0,
				Standard_Real& gamma1,
				const Standard_Real tol = 1.0E-6
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

		static TnbGeo_EXPORT std::shared_ptr<IntersectEntity2d> 
			Intersection_cgal
			(
				const Entity2d_LineRef&,
				const Entity2d_LineRef&
			);

		static TnbGeo_EXPORT std::vector<Pnt2d> 
			Intersecction_cgal
			(
				const Entity2d_Triangle& tri0,
				const Entity2d_Triangle& tri1
			);

		static TnbGeo_EXPORT Standard_Boolean 
			IsIntersect_cgal
			(
				const Entity3d_SegmentRef& theSeg,
				const Entity3d_Triangle& theTri
			);

		static std::shared_ptr<Entity2d_Polygon> Intersection_cgal(const gp_Pln&, const Entity3d_Box&);

		static inline Standard_Real 
			Interpolate
			(
				const Standard_Real x, 
				const std::pair<Standard_Real, Standard_Real>& theLower, 
				const std::pair<Standard_Real, Standard_Real>& theUpper
			);

		static TnbGeo_EXPORT std::pair<Standard_Real, Standard_Real>
			Interpolate
			(
				const Entity2d_Box& theBox, 
				const std::pair<Standard_Real, Standard_Real>& pt
			);

		template<class T>
		static T LinearInterpolate(const T& x0, const T& x1, const T& t);

		static inline Pnt2d 
			ProjectPtAtSegment
			(
				const Pnt2d& thePt,
				const Pnt2d& theP0, 
				const Pnt2d& theP1
			);

		static TnbGeo_EXPORT Entity_Triangle<Pnt2d> 
			CalcParametricTriangle
			(
				const Entity_Triangle<const Pnt3d&>&
			);

		static TnbGeo_EXPORT std::vector<Pnt2d> 
			DistributeInDomain
			(
				const std::vector<Pnt2d>&, 
				const Entity2d_Box&
			);

		static TnbGeo_EXPORT connectivity::triple RetrieveIds(const Poly_Triangle&);

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			RetrieveParaTriangulation
			(
				const Poly_Triangulation&
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Triangulation> 
			RetrieveTriangulation
			(
				const Poly_Triangulation&
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

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Triangulation>
			Triangulation
			(
				const Entity2d_Chain& theChain
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

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Polygon>
			GetPolygon
			(
				const Entity_Triangle<const Pnt2d&>&
			);

		static TnbGeo_EXPORT std::vector<Entity2d_Triangle> 
			GetTriangles
			(
				const Entity2d_Triangulation&
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Triangle>
			ProjectToPlane
			(
				const Entity3d_Triangle& theTri, 
				const gp_Pln& thePlane
			);

		static TnbGeo_EXPORT Entity_Triangle<const Pnt2d&> 
			GetTriangle
			(
				const Standard_Integer theIndex,
				const Entity2d_Triangulation&
			);

		static TnbGeo_EXPORT std::shared_ptr<Entity3d_Triangulation> 
			PoissonSurfaceRecon_cgal
			(
				const Entity3d_Triangulation&
			);

		template<class Type>
		static size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<Type>& theSorted,
				Standard_Real(*xValue)(const Type&)
			);

		static TnbGeo_EXPORT size_t 
			FindSpan
			(
				const Standard_Real x, 
				const std::vector<Standard_Real>& theSorted
			);

		template<class Type>
		static Type CalcLinearPar(const Type& x0, const Type& x1, const Type& p);

		static TnbGeo_EXPORT Entity2d_Line GetLine(const gp_Lin2d&);

		static TnbGeo_EXPORT std::tuple<Standard_Real, Standard_Real, Standard_Real, Standard_Real>
			GetCoefficients(const gp_Pln& thePlane);

		static TnbGeo_EXPORT void 
			CheckSorted
			(
				const std::vector<Standard_Real>& theSorted,
				const char* theName
			);

		static TnbGeo_EXPORT void 
			MakeTrianglesCCW
			(
				const std::shared_ptr<Entity2d_Triangulation>& t
			);

		static TnbGeo_EXPORT void Reverse(Entity2d_Triangulation&);
		static TnbGeo_EXPORT void Reverse(Entity3d_Triangulation&);
	};
}

#include <Geo_ToolsI.hxx>

#endif // !_Geo_Tools_Header
