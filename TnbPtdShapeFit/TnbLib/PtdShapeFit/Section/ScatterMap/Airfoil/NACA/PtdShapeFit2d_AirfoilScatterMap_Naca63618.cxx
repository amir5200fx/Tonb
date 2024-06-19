#include <PtdShapeFit2d_AirfoilScatterMap_Naca63618.hxx>

#include <PtdShapeFit2d_UpperAirfoilCurve.hxx>
#include <PtdShapeFit2d_LowerAirfoilCurve.hxx>
#include <Geo_AirfoilCloud_Naca63618.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const unsigned int tnbLib::airfoilScatterMapLib::Naca63618::nb_regions{2};
Standard_Integer tnbLib::airfoilScatterMapLib::Naca63618::NbRegions() const
{
	return static_cast<Standard_Integer>(nb_regions);
}

std::shared_ptr<tnbLib::PtdShapeFit2d_ScatterMap::ptList> tnbLib::airfoilScatterMapLib::Naca63618::Region(
	const Standard_Integer theIndex) const
{
	if (theIndex IS_EQUAL 0)
	{
		auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilcloud::naca63618::upper::coords);
		return std::move(pts);
	}
	if (theIndex IS_EQUAL 1)
	{
		auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilcloud::naca63618::lower::coords);
		return std::move(pts);
	}
	FatalErrorIn(FunctionSIG) << endl
		<< " Wrong index has been detected." << endl
		<< abort(FatalError);
	return nullptr;
}

std::vector<std::pair<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<tnbLib::PtdShapeFit2d_ScatterMap::ptList>>>
tnbLib::airfoilScatterMapLib::Naca63618::RetrieveCurves(const std::shared_ptr<Cad2d_Plane>& thePlane) const
{
	const auto outer = thePlane->OuterWire();
	std::vector<std::pair<std::shared_ptr<Pln_Curve>, std::shared_ptr<ptList>>> pairedList;
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	for (const auto& x: outer->RetrieveCurves())
	{
		if (auto upper = std::dynamic_pointer_cast<PtdShapeFit2d_UpperAirfoilCurve>(x))
		{
			curves.emplace_back(x);
		}
	}
	if (curves.size() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of airfoil has been detected." << endl
			<< abort(FatalError);
	}
	{
		auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilcloud::naca63618::upper::coords);
		auto paired = std::make_pair(curves.at(0), std::move(pts));
		pairedList.push_back(std::move(paired));
	}
	curves.clear();
	for (const auto& x : outer->RetrieveCurves())
	{
		if (auto lower = std::dynamic_pointer_cast<PtdShapeFit2d_LowerAirfoilCurve>(x))
		{
			curves.push_back(x);
		}
	}
	if (curves.size() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of airfoil has been detected." << endl
			<< abort(FatalError);
	}
	{
		auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilcloud::naca63618::lower::coords);
		auto paired = std::make_pair(curves.at(0), std::move(pts));
		pairedList.push_back(std::move(paired));
	}
	return std::move(pairedList);
}