#include <PtdShapeFit2d_AirfoilLeading_t1.hxx>

#include <PtdShapeFit2d_ScatterMap.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{
	auto RetrieveLeadingT1Geometry(const Cad2d_Plane& thePlane)
	{
		const auto& outer = thePlane.OuterWire();
		const auto& edges = outer->Edges();
		return edges.at(0)->Curve();
	}
}

Standard_Real
tnbLib::curveLib::airfoilLib::Leading_t1::CalcError
(
	const std::vector<Standard_Real>& xs,
	const std::shared_ptr<PtdShapeFit2d_ScatterMap>& theMap
) const
{
	auto shape = RetrieveShape(xs);
	auto geom = RetrieveLeadingT1Geometry(*shape);
	auto pnts = theMap->Region(geom->Index());
	Standard_Real sum = 0;
	for (const auto& x : *pnts)
	{
		try
		{
			auto dis = PtdShapeFit_Section::CalcDistance(x, *geom);
			auto d2 = dis * dis;
			sum += d2;
		}
		catch (const Standard_Failure& ms)
		{
			if (verbose)
			{
				Info << ms.GetMessageString() << endl;
			}
		}
	}
	return sum;
}