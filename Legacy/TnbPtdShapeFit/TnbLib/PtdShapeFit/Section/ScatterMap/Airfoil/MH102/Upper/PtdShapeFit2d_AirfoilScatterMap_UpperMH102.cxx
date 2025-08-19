#include <PtdShapeFit2d_AirfoilScatterMap_UpperMH102.hxx>

#include <PtdShapeFit2d_UpperAirfoilCurve.hxx>
#include <Geo_AirfoilOffsets_MH102.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const unsigned int tnbLib::airfoilScatterMapLib::UpperMH102::nb_regions(1);

Standard_Integer 
tnbLib::airfoilScatterMapLib::UpperMH102::NbRegions() const
{
	return Standard_Integer(nb_regions);
}

std::shared_ptr<typename tnbLib::PtdShapeFit2d_ScatterMap::ptList>
tnbLib::airfoilScatterMapLib::UpperMH102::Region(const Standard_Integer theIndex) const
{
	auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilOffsetsLib::upper::coords);
	return std::move(pts);
}

std::vector<std::pair<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<typename tnbLib::PtdShapeFit2d_ScatterMap::ptList>>>
tnbLib::airfoilScatterMapLib::UpperMH102::RetrieveCurves
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
) const
{
	const auto& outer = thePlane->OuterWire();
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	for (const auto& x : outer->RetrieveCurves())
	{
		if (auto upper = std::dynamic_pointer_cast<PtdShapeFit2d_UpperAirfoilCurve>(x))
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
	std::vector<std::pair<std::shared_ptr<Pln_Curve>, std::shared_ptr<ptList>>> pairedList;
	{
		auto pts = std::make_shared<std::vector<Pnt2d>>(geoLib::airfoilOffsetsLib::upper::coords);
		auto paired = std::make_pair(curves.at(0), std::move(pts));
		pairedList.push_back(std::move(paired));
	}
	return std::move(pairedList);
}