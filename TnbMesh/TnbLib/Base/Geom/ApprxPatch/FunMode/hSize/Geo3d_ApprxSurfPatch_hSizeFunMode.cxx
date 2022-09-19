#include <Geo3d_ApprxSurfPatch_hSizeFunMode.hxx>

#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer tnbLib::Geo3d_ApprxSurfPatch_hSizeFunMode::DEFAULT_NB_SAMPLES = 3;

namespace tnbLib
{

	auto CalcDistance(const Pnt2d& theP0, const Pnt2d& theP1, const Geom_Surface& theSurface, const Standard_Integer n)
	{		
		const auto du = (theP1 - theP0) / (Standard_Real)n;
		Standard_Real dis = 0;
		auto p0 = theP0;
		for (size_t i = 0; i <= n; i++)
		{
			auto p = theP0 + (Standard_Real)i*du;
			dis += p0.Distance(p);
			p0 = p;
		}
		return dis;
	}
}

Standard_Boolean 
tnbLib::Geo3d_ApprxSurfPatch_hSizeFunMode::DoSubdivide
(
	const Entity2d_Box & theRegion,
	const Geom_Surface & theSurface, 
	const Standard_Real theSize
) const
{
	Debug_If_Condition(NbSamples() <= 1);
	const auto& p0 = theRegion.P0();
	const auto p1 = theRegion.Corner(Box2d_PickAlgorithm_SE);
	const auto& p2 = theRegion.P1();
	const auto p3 = theRegion.Corner(Box2d_PickAlgorithm_NW);

	const auto dis1 = CalcDistance(p0, p2, theSurface, NbSamples());
	if (dis1 > theSize)
	{
		return Standard_True;
	}
	const auto dis2 = CalcDistance(p1, p3, theSurface, NbSamples());
	if (dis2 > theSize)
	{
		return Standard_True;
	}
	return Standard_False;
}
