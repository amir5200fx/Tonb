#include <Geo_CmptLib.hxx>

#include <gp.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Triangle.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

static const auto onePerTwelve = 1.0 / 12.0;

Standard_Real 
tnbLib::Geo_CmptLib::Area
(
	const Entity2d_Box & rect
)
{
	auto[h, b] = rect.Length();
	return h * b;
}

Standard_Real 
tnbLib::Geo_CmptLib::IxBar
(
	const Entity2d_Box & rect
)
{
	auto[h, b] = rect.Length();
	return h * h*h*b *onePerTwelve;
}

Standard_Real 
tnbLib::Geo_CmptLib::IyBar
(
	const Entity2d_Box & rect
)
{
	auto[h, b] = rect.Length();
	return h * b*b*b *onePerTwelve;
}

Standard_Real 
tnbLib::Geo_CmptLib::Ix
(
	const Entity2d_Box & b, 
	const Standard_Real y0
)
{
	auto c = b.CalcCentre();
	auto dy = c.Y() - y0;
	auto a = Area(b);

	return IxBar(b) + a * dy*dy;
}

Standard_Real 
tnbLib::Geo_CmptLib::Iy
(
	const Entity2d_Box & b, 
	const Standard_Real x0
)
{
	auto c = b.CalcCentre();
	auto dx = c.X() - x0;
	auto a = Area(b);

	return IyBar(b) + a * dx*dx;
}

Standard_Real 
tnbLib::Geo_CmptLib::Mx
(
	const Entity2d_Box & b,
	const Standard_Real y0
)
{
	auto c = b.CalcCentre();
	auto dy = c.Y() - y0;

	return dy * Area(b);
}

Standard_Real 
tnbLib::Geo_CmptLib::My
(
	const Entity2d_Box & b,
	const Standard_Real x0
)
{
	auto c = b.CalcCentre();
	auto dx = c.X() - x0;

	return dx * Area(b);
}

namespace tnbLib
{

	namespace geoCmptLib
	{

		static void CheckPolygon(const Entity2d_Polygon & thePoly, const char* Name)
		{
			if (NOT thePoly.IsClosed())
			{
				FatalErrorIn(Name)
					<< "the polygon is not closed" << endl
					<< abort(FatalError);
			}
		}
	}

	inline Standard_Real 
		Determinant
		(
			const Pnt2d& p0, 
			const Pnt2d& p1
		)
	{
		const auto x0 = p0.X();
		const auto y0 = p0.Y();

		const auto x1 = p1.X();
		const auto y1 = p1.Y();

		return x0 * y1 - x1 * y0;
	}

	inline Standard_Real 
		CxPoly
		(
			const Pnt2d& p0,
			const Pnt2d& p1
		)
	{
		const auto x0 = p0.X();
		const auto y0 = p0.Y();

		const auto x1 = p1.X();
		const auto y1 = p1.Y();

		return (x0 + x1)*(x0 * y1 - x1 * y0);
	}

	inline Standard_Real
		CyPoly
		(
			const Pnt2d& p0,
			const Pnt2d& p1
		)
	{
		const auto x0 = p0.X();
		const auto y0 = p0.Y();

		const auto x1 = p1.X();
		const auto y1 = p1.Y();

		return (y0 + y1)*(x0 * y1 - x1 * y0);
	}

	inline Standard_Real
		IxPoly
		(
			const Pnt2d& p0,
			const Pnt2d& p1,
			const Standard_Real yc
		)
	{
		const auto x0 = p0.X();
		const auto y0 = p0.Y() - yc;

		const auto x1 = p1.X();
		const auto y1 = p1.Y() - yc;

		return (y0*y0 + y0 * y1 + y1 * y1)*(x0 * y1 - x1 * y0);
	}

	inline Standard_Real
		IyPoly
		(
			const Pnt2d& p0,
			const Pnt2d& p1,
			const Standard_Real xc
		)
	{
		const auto x0 = p0.X() - xc;
		const auto y0 = p0.Y();

		const auto x1 = p1.X() - xc;
		const auto y1 = p1.Y();

		return (x0*x0 + x0 * x1 + x1 * x1)*(x0 * y1 - x1 * y0);
	}

	inline Standard_Real
		IxyPoly
		(
			const Pnt2d& p0,
			const Pnt2d& p1,
			const Pnt2d& C
		)
	{
		const auto x0 = p0.X() - C.X();
		const auto y0 = p0.Y() - C.Y();

		const auto x1 = p1.X() - C.X();
		const auto y1 = p1.Y() - C.Y();

		return (x0*y1 + 2.0*x0*y0 + 2.0*x1*y1 + x1 * y0)*(x0 * y1 - x1 * y0);
	}
}

Standard_Real 
tnbLib::Geo_CmptLib::Area
(
	const Entity2d_Polygon & thePoly
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::Area(const Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += Determinant(pts[i], pts[i + 1]);
	}
	return 0.5*sum;
}

Standard_Real 
tnbLib::Geo_CmptLib::Area
(
	const Entity2d_Triangle & t
)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	return Area(*poly);
}

Standard_Real 
tnbLib::Geo_CmptLib::CxProductArea
(
	const Entity2d_Polygon & thePoly
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::CxProductAreaconst Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += CxPoly(pts[i], pts[i + 1]);
	}
	return sum / 6.0;
}

Standard_Real 
tnbLib::Geo_CmptLib::CxProductArea
(
	const Entity2d_Triangle & t
)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	return CxProductArea(*poly);
}

Standard_Real
tnbLib::Geo_CmptLib::CyProductArea
(
	const Entity2d_Polygon & thePoly
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::CyProductArea(const Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += CyPoly(pts[i], pts[i + 1]);
	}
	return sum / 6.0;
}

Standard_Real 
tnbLib::Geo_CmptLib::CyProductArea
(
	const Entity2d_Triangle & t
)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	return CyProductArea(*poly);
}

tnbLib::Pnt2d 
tnbLib::Geo_CmptLib::Centre
(
	const Entity2d_Polygon & thePoly
)
{
	const auto area = Area(thePoly);
	
	const auto cx = CxProductArea(thePoly) / area;
	const auto cy = CyProductArea(thePoly) / area;

	return Pnt2d(cx, cy);
}

tnbLib::Pnt2d 
tnbLib::Geo_CmptLib::Centre(const Entity2d_Triangle & t)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	auto pt = Centre(*poly);
	return std::move(pt);
}

Standard_Real 
tnbLib::Geo_CmptLib::Ix
(
	const Entity2d_Polygon & thePoly,
	const Standard_Real y0
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::Ix(const Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += IxPoly(pts[i], pts[i + 1], y0);
	}
	return sum / 12.0;
}

Standard_Real 
tnbLib::Geo_CmptLib::Ix
(
	const Entity2d_Triangle & t,
	const Standard_Real y0
)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	return Ix(*poly, y0);
}

Standard_Real
tnbLib::Geo_CmptLib::Iy
(
	const Entity2d_Polygon & thePoly,
	const Standard_Real x0
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::Iy(const Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += IyPoly(pts[i], pts[i + 1], x0);
	}
	return sum / 12.0;
}

Standard_Real 
tnbLib::Geo_CmptLib::Iy
(
	const Entity2d_Triangle & t,
	const Standard_Real x0
)
{
	auto poly = Geo_Tools::GetPolygon(t);
	Debug_Null_Pointer(poly);

	return Iy(*poly, x0);
}

Standard_Real
tnbLib::Geo_CmptLib::Ixy
(
	const Entity2d_Polygon & thePoly,
	const Pnt2d& theC
)
{
	geoCmptLib::CheckPolygon(thePoly, "Standard_Real Geo_CmptLib::Ixy(const Entity2d_Polygon & thePoly)");

	Standard_Real sum = 0;

	const auto& pts = thePoly.Points();
	for (auto i = 0; i < pts.size() - 1; i++)
	{
		sum += IxyPoly(pts[i], pts[i + 1], theC);
	}
	return sum / 24.0;
}

Standard_Real 
tnbLib::Geo_CmptLib::Ixi
(
	const Standard_Real IxiBar, 
	const Standard_Real theArea, 
	const Standard_Real dxi
)
{
	return IxiBar + theArea * dxi*dxi;
}

Standard_Real 
tnbLib::Geo_CmptLib::Gyradius
(
	const Standard_Real Ix, 
	const Standard_Real theArea
)
{
	if (theArea <= gp::Resolution())
	{
		FatalErrorIn("Standard_Real Geo_CmptLib::Gyradius(const Standard_Real Ix, const Standard_Real theArea)")
			<< "divided by zero!" << endl
			<< abort(FatalError);
	}

	return std::sqrt(Ix / theArea);
}

Standard_Real 
tnbLib::Geo_CmptLib::Ixi
(
	const std::vector<Standard_Real>& ix,
	const std::vector<Standard_Real>& Ax, 
	const std::vector<Standard_Real>& dx
)
{
	Standard_Real sum = 0;
	for (auto i = 0; i < ix.size(); i++)
	{
		sum += ix[i] + Ax[i] * dx[i] * dx[i];
	}
	return sum;
}

Standard_Real 
tnbLib::Geo_CmptLib::Ixy
(
	const Standard_Real IxyBar,
	const Standard_Real dx,
	const Standard_Real dy, 
	const Standard_Real Area
)
{
	return IxyBar + dx * dy*Area;
}