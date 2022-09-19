#include <Geo3d_ApprxSurfPatch_DistOnlyFunMode.hxx>

#include <Geo3d_ApprxSurfPatch_Samples.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Triangle.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>

#include <gp_Pln.hxx>
#include <gp_Vec.hxx>
#include <gp_Dir.hxx>

namespace tnbLib
{

	Standard_Real CalcMaxDistance
	(
		const Geom_Plane& thePlane,
		const std::vector<Pnt2d>& theSamples, 
		const Geom_Surface& thePatch
	)
	{
		Debug_If_Condition(theSamples.empty());
		Standard_Real maxDis = RealFirst();
		for (const auto& x : theSamples)
		{
			const auto[xs, ys] = x.Components();
			auto Ps = thePlane.Value(xs, ys);
			auto P = thePatch.Value(xs, ys);
			auto dis = Ps.Distance(P);
			if (dis > maxDis)
			{
				maxDis = dis;
			}
		}
		return maxDis;
	}

	auto CalcDistance
	(
		const Entity_Triangle<const Pnt2d&>& theTriangle,
		const Geo3d_ApprxSurfPatch_Samples& theSamples,
		const Geom_Surface& thePatch
	)
	{
		const auto[x0, y0] = theTriangle.P0().Components();
		const auto[x1, y1] = theTriangle.P1().Components();
		const auto[x2, y2] = theTriangle.P2().Components();

		const auto P0 = thePatch.Value(x0, y0);
		const auto P1 = thePatch.Value(x1, y1);
		const auto P2 = thePatch.Value(x2, y2);

		const auto b = Geo_BoxTools::GetBox(P0, P1, P2);
		const auto dim = b->Diameter();

		gp_Vec v0(P0, P1);
		gp_Vec v1(P0, P2);

		gp_Dir n = v0.Crossed(v1);
		Geom_Plane pln(P0, n);
		
		auto t = std::make_pair(CalcMaxDistance(pln, theSamples.RetrieveSamples(theTriangle), thePatch), dim);
		return std::move(t);
	}
}

Standard_Boolean 
tnbLib::Geo3d_ApprxSurfPatch_DistOnlyFunMode::DoSubdivide
(
	const Entity2d_Box& theRegion,
	const Geom_Surface& theGeometry, 
	const Standard_Real theTol
) const
{
	Debug_Null_Pointer(Samples());
	const auto& p0 = theRegion.P0();
	const auto p1 = theRegion.Corner(Box2d_PickAlgorithm_SE);
	const auto& p2 = theRegion.P1();
	const auto p3 = theRegion.Corner(Box2d_PickAlgorithm_NW);

	{
		Entity_Triangle<const Pnt2d&> tri(p0, p1, p2);
		const auto[dis, dim] = CalcDistance(tri, *Samples(), theGeometry);
		if (dis < theTol*dim)
		{
			return Standard_True;
		}
	}

	{
		Entity_Triangle<const Pnt2d&> tri(p0, p2, p3);
		const auto[dis, dim] = CalcDistance(tri, *Samples(), theGeometry);
		if (dis < theTol*dim)
		{
			return Standard_True;
		}
	}

	{
		Entity_Triangle<const Pnt2d&> tri(p0, p1, p3);
		const auto[dis, dim] = CalcDistance(tri, *Samples(), theGeometry);
		if (dis < theTol*dim)
		{
			return Standard_True;
		}
	}

	{
		Entity_Triangle<const Pnt2d&> tri(p1, p2, p3);
		const auto[dis, dim] = CalcDistance(tri, *Samples(), theGeometry);
		if (dis < theTol*dim)
		{
			return Standard_True;
		}
	}
	return Standard_False;
}