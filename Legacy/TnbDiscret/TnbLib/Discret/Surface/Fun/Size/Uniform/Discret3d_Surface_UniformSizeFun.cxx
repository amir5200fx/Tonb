#include <Discret3d_Surface_UniformSizeFun.hxx>

#include <Discret_Curve_Samples.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static auto CalcXs(const Discret_Curve_Samples& theFun)
	{
		auto xs = theFun.CalcXs(0.0, 1.0);
		return std::move(xs);
	}

	static auto CalcLength(const std::vector<Pnt3d>& thePts)
	{
		Standard_Real d = 0;
		for (size_t i = 1; i < thePts.size(); i++)
		{
			const auto& p0 = thePts.at(i - 1);
			const auto& p1 = thePts.at(i);
			d += p1.Distance(p0);
		}
		return d;
	}

	static Standard_Real 
		CalcPathLength
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1,
			const Cad_GeomSurface& theSurface, 
			const Discret_Curve_Samples& theFun
		)
	{
		const auto dp = theP1 - theP0;

		const auto us = CalcXs(theFun);

		std::vector<Pnt3d> pts;
		pts.reserve(us.size());
		pts.push_back(theSurface.Value(theP0));
		for (size_t i = 1; i < pts.size() - 1; i++)
		{
			pts.push_back(theSurface.Value(theP0 + us.at(i)*dp));
		}
		pts.push_back(theSurface.Value(theP1));

		return CalcLength(pts);
	}
}

Standard_Boolean 
tnbLib::Discret3d_Surface_UniformSizeFun::Subdivide
(
	const std::shared_ptr<Cad_GeomSurface>& theSurface, 
	const Standard_Real theU0, 
	const Standard_Real theU1,
	const Standard_Real theV0, 
	const Standard_Real theV1
) const
{
	Debug_Null_Pointer(theSurface);
	Debug_Null_Pointer(Samples());
	const auto len0 = ::tnbLib::CalcPathLength(Pnt2d(theU0, theV0), Pnt2d(theU1, theV1), *theSurface, *Samples());
	const auto len1 = ::tnbLib::CalcPathLength(Pnt2d(theU1, theV0), Pnt2d(theU0, theV1), *theSurface, *Samples());
	if (len0 <= Size() AND len1 <= Size())
	{
		return Standard_False;
	}
	return Standard_True;
}