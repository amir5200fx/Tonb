#include <ShapePx_Tools.hxx>

#include <SectPx_Tools.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineSurface.hxx>

TColgp_Array2OfPnt 
tnbLib::ShapePx_Tools::ControlNet
(
	const ShapePx_CtrlNet & theNet
)
{
	TColgp_Array2OfPnt pnts(1, theNet.NbRows(), 1, theNet.NbColumns());
	Standard_Integer i = 0;
	for (const auto& x : theNet.Rows())
	{
		i++;
		Standard_Integer j = 0;
		auto xi = x.X();
		for (const auto& p : x.Pnts())
		{
			j++;
			auto pt3 = Pnt3d(xi, p.first.X(), p.first.Y());
			pnts.SetValue(i, j, pt3);
		}
	}
	return std::move(pnts);
}

TColStd_Array2OfReal 
tnbLib::ShapePx_Tools::Weights
(
	const ShapePx_CtrlNet & theNet
)
{
	TColStd_Array2OfReal ws(1, theNet.NbRows(), 1, theNet.NbColumns());
	Standard_Integer i = 0;
	for (const auto& x : theNet.Rows())
	{
		i++;
		Standard_Integer j = 0;
		for (const auto& p : x.Pnts())
		{
			j++;
			ws.SetValue(i, j, p.second);
		}
	}
	return std::move(ws);
}

std::vector<std::pair<tnbLib::Pnt2d, Standard_Real>>
tnbLib::ShapePx_Tools::CtrlRow
(
	const std::vector<Pnt2d>& theQ, 
	const std::vector<Standard_Real>& theWeights
)
{
	if (theQ.size() NOT_EQUAL theWeights.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "the pole list and weight list must be the same size" << endl
			<< abort(FatalError);
	}

	std::vector<std::pair<Pnt2d, Standard_Real>> paired;
	paired.reserve(theQ.size());
	for (size_t i = 0; i < theQ.size(); i++)
	{
		auto p = std::make_pair(theQ[i], theWeights[i]);
		paired.push_back(std::move(p));
	}
	return std::move(paired);
}

Handle(Geom_Surface) 
tnbLib::ShapePx_Tools::Surface
(
	const ShapePx_CtrlNet & theNet,
	const Standard_Integer uDegree
)
{
	auto poles = ControlNet(theNet);
	auto weights = Weights(theNet);
	auto[vknots, vMults] = SectPx_Tools::Knots(theNet.Knots());
	auto[uknots, uMults] = SectPx_Tools::Knots(SectPx_Tools::Knots(theNet.NbRows(), uDegree, 0, 1));

	Handle(Geom_Surface) surface = new Geom_BSplineSurface(poles, weights, uknots, vknots, uMults, vMults, uDegree, 3);
	return std::move(surface);
}