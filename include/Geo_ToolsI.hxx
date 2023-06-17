#pragma once
#include <Global_Tools.hxx>
inline Standard_Boolean 
tnbLib::Geo_Tools::IsZero
(
	const Standard_Real x,
	const Standard_Real epsilon
)
{
	return std::abs(x - epsilon) <= (Standard_Real)0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsForward
(
	const Standard_Integer theV0,
	const Standard_Integer theV1,
	const Standard_Integer theQ0,
	const Standard_Integer theQ1
)
{
	if (theV0 IS_EQUAL theQ0)
	{
		if (theV1 IS_EQUAL theQ1)
		{
			return Standard_True;
		}
	}
	else if (theV0 IS_EQUAL theQ1)
	{
		if (theV1 IS_EQUAL theQ0)
		{
			return Standard_False;
		}
	}
	FatalErrorIn(FunctionSIG)
		<< "the two segments aren't coincident" << endl
		<< abort(FatalError);
	return Standard_True;
}

inline Standard_Real 
tnbLib::Geo_Tools::CalcSquareDistancePointFromTriangle
(
	const Pnt3d& thePoint,
	const Entity_Triangle<const Pnt3d&>& theTriangle
)
{
	return CalcSquareDistancePointFromTriangle
	(
		thePoint,
		theTriangle.P0(), 
		theTriangle.P1(),
		theTriangle.P2()
	);
}

inline Standard_Real 
tnbLib::Geo_Tools::CalcSquareDistancePointFromSegment
(
	const Pnt2d& thePoint, 
	const Entity_Segment<const Pnt2d&>& theSeg
)
{
	return CalcSquareDistancePointFromSegment
	(
		thePoint, 
		theSeg.P0(),
		theSeg.P1()
	);
}

inline Standard_Real 
tnbLib::Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly
(
	const Entity_Segment<const Pnt3d&>& theSeg0, 
	const Entity_Segment<const Pnt3d&>& theSeg1
)
{
	return CalcSquareDistanceSegmentFromSegment_Eberly
	(
		theSeg0.P0(),
		theSeg0.P1(), 
		theSeg1.P0(),
		theSeg1.P1()
	);
}

inline Standard_Integer 
tnbLib::Geo_Tools::Round
(
	const Standard_Real x
)
{
	return (Standard_Integer)floor(x + 0.5);
}

inline Standard_Real 
tnbLib::Geo_Tools::DegToRadian
(
	const Standard_Real Degree
)
{
	return Degree * M_PI / 180.0;
}

inline Standard_Real 
tnbLib::Geo_Tools::RadianToDegree
(
	const Standard_Real Radian
)
{
	return Radian * 180.0 / M_PI;
}

namespace tnbLib
{

	template<class Point>
	inline Point Geo_Tools::CalcCentre(const Point & theP0, const Point & theP1)
	{
		auto Pm = MEAN(theP0, theP1);
		return std::move(Pm);
	}

	template<class Point>
	inline Point Geo_Tools::CalcCentre(const Point & theP0, const Point & theP1, const Point & theP2)
	{
		auto Pm = OnePerThree * (theP0 + theP1 + theP2);
		return std::move(Pm);
	}
}

inline Standard_Real 
tnbLib::Geo_Tools::Distance_cgal
(
	const Pnt2d & theQ, 
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	return std::sqrt(SquareDistance_cgal(theQ, theP0, theP1));
}

inline Standard_Real 
tnbLib::Geo_Tools::Distance_cgal
(
	const Pnt3d & theQ, 
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	return std::sqrt(SquareDistance_cgal(theQ, theP0, theP1));
}

inline Standard_Real 
tnbLib::Geo_Tools::Distance_cgal
(
	const Pnt3d & theQ, 
	const Pnt3d & theP0, 
	const Pnt3d & theP1, 
	const Pnt3d & theP2
)
{
	return std::sqrt(SquareDistance_cgal(theQ, theP0, theP1, theP2));
}

inline Standard_Real 
tnbLib::Geo_Tools::DistanceSegments_cgal
(
	const Pnt3d & theQ0,
	const Pnt3d & theQ1, 
	const Pnt3d & theP0, 
	const Pnt3d & theP1
)
{
	return std::sqrt(SquareDistanceSegments_cgal(theQ0, theQ1, theP0, theP1));
}

inline Standard_Real 
tnbLib::Geo_Tools::Distance_cgal
(
	const Pnt3d & thePoint, 
	const gp_Pln & thePlane
)
{
	return std::sqrt(SquareDistance_cgal(thePoint, thePlane));
}

inline Standard_Real 
tnbLib::Geo_Tools::Area_cgal
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const Pnt2d & theP2
)
{
	return Oriented_cgal(theP0, theP1, theP2)*(Standard_Real)0.5;
}

inline Standard_Real 
tnbLib::Geo_Tools::Volume_cgal
(
	const Pnt3d & theP0, 
	const Pnt3d & theP1, 
	const Pnt3d & theP2,
	const Pnt3d & theP3
)
{
	return Oriented_cgal(theP0, theP1, theP2, theP3)*OnePerSix;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointRightEdge
(
	const Pnt2d& thePoint,
	const Pnt2d& theP0,
	const Pnt2d& theP1
)
{
	return Standard_Boolean();
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointRightEdge_cgal
(
	const Pnt2d & Point,
	const Pnt2d & P0, 
	const Pnt2d & P1
)
{
	return Oriented_cgal(Point, P0, P1) < 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointRightFacet_cgal
(
	const Pnt3d & thePoint,
	const Pnt3d & theP0, 
	const Pnt3d & theP1, 
	const Pnt3d & theP2
)
{
	return Oriented_cgal(thePoint, theP0, theP1, theP2) < 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointRightFacet_Shewchuk
(
	const Pnt3d & thePoint,
	const Pnt3d & theP0,
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	return Oriented_Shewchuk(thePoint, theP0, theP1, theP2) < 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointRightFacet_Fast
(
	const Pnt3d & thePoint, 
	const Pnt3d & theP0,
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	return Oriented_Fast(thePoint, theP0, theP1, theP2) < 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointLeftEdge_cgal
(
	const Pnt2d & Point, 
	const Pnt2d & P0, 
	const Pnt2d & P1
)
{
	return Oriented_cgal(Point, P0, P1) > 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointLeftFacet_cgal
(
	const Pnt3d & thePoint,
	const Pnt3d & theP0, 
	const Pnt3d & theP1, 
	const Pnt3d & theP2
)
{
	return Oriented_cgal(thePoint, theP0, theP1, theP2) > 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointLeftFacet_Shewchuk
(
	const Pnt3d & thePoint,
	const Pnt3d & theP0, 
	const Pnt3d & theP1, 
	const Pnt3d & theP2
)
{
	return Oriented_Shewchuk(thePoint, theP0, theP1, theP2) > 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointLeftFacet_Fast
(
	const Pnt3d & thePoint,
	const Pnt3d & theP0, 
	const Pnt3d & theP1,
	const Pnt3d & theP2
)
{
	return Oriented_Fast(thePoint, theP0, theP1, theP2) > 0.0;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointInsideTriangle_cgal
(
	const Pnt2d & Point, 
	const Pnt2d & P0,
	const Pnt2d & P1, 
	const Pnt2d & P2
)
{
	if (IsPointRightEdge_cgal(Point, P0, P1))
	{
		return Standard_False;
	}
	else if (IsPointRightEdge_cgal(Point, P1, P2))
	{
		return Standard_False;
	}
	else if (IsPointRightEdge_cgal(Point, P2, P0))
	{
		return Standard_False;
	}
	return Standard_True;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointInsideTriangleCW_cgal
(
	const Pnt2d & Point, 
	const Pnt2d & P0,
	const Pnt2d & P1, 
	const Pnt2d & P2
)
{
	if (IsPointLeftEdge_cgal(Point, P0, P1))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdge_cgal(Point, P1, P2))
	{
		return Standard_False;
	}
	else if (IsPointLeftEdge_cgal(Point, P2, P0))
	{
		return Standard_False;
	}
	return Standard_True;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPointInsideTetrahedron_cgal
(
	const Pnt3d& theCoord, 
	const Pnt3d& theP0,
	const Pnt3d& theP1,
	const Pnt3d& theP2,
	const Pnt3d& theP3
)
{
	if (IsPointRightFacet_cgal(theCoord, theP0, theP1, theP2))
	{
		return Standard_False;
	}
	else if (IsPointRightFacet_cgal(theCoord, theP1, theP3, theP2))
	{
		return Standard_False;
	}
	else if (IsPointRightFacet_cgal(theCoord, theP2, theP3, theP0))
	{
		return Standard_False;
	}
	else if (IsPointRightFacet_cgal(theCoord, theP0, theP3, theP1))
	{
		return Standard_False;
	}
	return Standard_True;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPairedTwoSegments
(
	const Standard_Integer v1, 
	const Standard_Integer v2, 
	const Standard_Integer q1, 
	const Standard_Integer q2
)
{
	if (v1 == q1)
	{
		if (v2 == q2)
			return Standard_True;
		else
			return Standard_False;
	}
	else if (v2 == q1)
	{
		if (v1 == q2)
			return Standard_True;
		else
			return Standard_False;
	}
	return Standard_False;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsPairedTwoTriangles
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer v3,
	const Standard_Integer q1,
	const Standard_Integer q2,
	const Standard_Integer q3
)
{
	if (v1 IS_EQUAL q1)
	{
		if (v2 IS_EQUAL q2)
		{
			if (v3 IS_EQUAL q3) return Standard_True;
		}
		else if (v2 IS_EQUAL q3)
		{
			if (v3 IS_EQUAL q2) return Standard_True;
		}
	}
	else if (v1 IS_EQUAL q2)
	{
		if (v2 IS_EQUAL q1)
		{
			if (v3 IS_EQUAL q3) return Standard_True;
		}
		else if (v2 IS_EQUAL q3)
		{
			if (v3 IS_EQUAL q1) return Standard_True;
		}
	}
	else if (v1 IS_EQUAL q3)
	{
		if (v2 IS_EQUAL q1)
		{
			if (v3 IS_EQUAL q2) return Standard_True;
		}
		else if (v2 IS_EQUAL q2)
		{
			if (v3 IS_EQUAL q1) return Standard_True;
		}
	}
	return Standard_False;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsIntersect
(
	const Standard_Real U0,
	const Standard_Real U1,
	const Standard_Real V0,
	const Standard_Real V1
)
{
	if (U1 < V0)
		return Standard_False;
	else if (V1 < U0)
		return Standard_False;
	else
		return Standard_True;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsOneCommonPointTwoSegments
(
	const Standard_Integer v1,
	const Standard_Integer v2, 
	const Standard_Integer q1, 
	const Standard_Integer q2
)
{
	if (v1 == q1)
	{
		return Standard_True;
	}
	else if (v1 == q2)
	{
		return Standard_True;
	}
	else if (v2 == q1)
	{
		return Standard_True;
	}
	else if (v2 == q2)
	{
		return Standard_True;
	}
	return Standard_False;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsOneCommonPointTwoTriangles
(
	const Standard_Integer v1, 
	const Standard_Integer v2,
	const Standard_Integer v3,
	const Standard_Integer q1, 
	const Standard_Integer q2, 
	const Standard_Integer q3
)
{
	if (v1 == q1)
		return Standard_True;
	else
		if (v1 == q2)
			return Standard_True;
		else
			if (v1 == q3)
				return Standard_True;
			else
				if (v2 == q1)
					return Standard_True;
				else
					if (v2 == q2)
						return Standard_True;
					else
						if (v2 == q3)
							return Standard_True;
						else
							if (v3 == q1)
								return Standard_True;
							else
								if (v3 == q2)
									return Standard_True;
								else
									if (v3 == q3)
										return Standard_True;
									else
										return Standard_False;
}

inline Standard_Boolean 
tnbLib::Geo_Tools::IsOneCommonPointSegmentTriangle
(
	const Standard_Integer v1,
	const Standard_Integer v2,
	const Standard_Integer q1,
	const Standard_Integer q2, 
	const Standard_Integer q3
)
{
	if (v1 == q1)
		return Standard_True;
	else
		if (v1 == q2)
			return Standard_True;
		else
			if (v1 == q3)
				return Standard_True;
			else
				if (v2 == q1)
					return Standard_True;
				else
					if (v2 == q2)
						return Standard_True;
					else
						if (v2 == q3)
							return Standard_True;
						else
							return Standard_False;
}

inline tnbLib::Vec3d 
tnbLib::Geo_Tools::CalcNormal
(
	const Pnt3d& theP0,
	const Pnt3d& theP1,
	const Pnt3d& theP2
)
{
	Vec3d V0(theP0, theP1);
	Vec3d V1(theP0, theP2);
	auto n = V0.Crossed(V1);
	return std::move(n);
}

inline Standard_Real 
tnbLib::Geo_Tools::Interpolate
(
	const Standard_Real x,
	const std::pair<Standard_Real, Standard_Real>& theLower, 
	const std::pair<Standard_Real, Standard_Real>& theUpper
)
{
	const auto[x0, y0] = theLower;
	const auto[x1, y1] = theUpper;

	if (NOT INSIDE(x, x0, x1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter, x, exceeds the boundary of the span [x0, x1]." << endl
			<< "  - x: " << x << endl
			<< "  - x0: " << x0 << endl
			<< "  - x1: " << x1 << endl
			<< abort(FatalError);
	}

	return y0 + ((x - x0) / (x1 - x0))*(y1 - y0);
}

template<class T>
inline T tnbLib::Geo_Tools::LinearInterpolate
(
	const T & x0,
	const T & x1, 
	const Standard_Real t
)
{
	return x0 + t * (x1 - x0);
}

inline tnbLib::Pnt2d 
tnbLib::Geo_Tools::ProjectPtAtSegment
(
	const Pnt2d & thePt, 
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	const auto bot = SquareDistance(theP0, theP1);

	Pnt2d Pn;
	if (bot == 0.0) Pn = theP1;
	else
	{
		const auto V1 = theP1 - theP0;
		const auto V2 = thePt - theP0;

		Standard_Real t = DotProduct(V1, V2) / bot;
		if (t > 1) t = 1;
		if (t < 0) t = 0;

		Pn = theP0 + t * V1;
	}
	return std::move(Pn);
}

namespace tnbLib
{

	template<class Type>
	size_t Geo_Tools::FindSpan
	(
		const Standard_Real x, 
		const std::vector<Type>& theSorted,
		Standard_Real(*xValue)(const Type&)
	)
	{
		return Global_Tools::FindSpan<Type>(x, theSorted, xValue);
	}
}

template<class Type>
inline Type 
tnbLib::Geo_Tools::CalcLinearPar
(
	const Type & x0, 
	const Type & x1, 
	const Type & p
)
{
	return (p - x0) / (x1 - x0);
}