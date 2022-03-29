#include <Cad_gSingularity.hxx>

#include <Cad_Tools.hxx>
#include <Pln_Curve.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

template<>
std::shared_ptr<tnbLib::Cad_gSingularZone> 
tnbLib::Cad_gSingularity::TypeDetection
(
	const Entity2d_Polygon& thePoly, 
	const GeoMesh2d_Data& theBMesh, 
	const std::vector<std::shared_ptr<Pln_Curve>>& theSides, 
	const Geom_Surface& theSurface
) const
{
	if (NOT this->SizeFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size function has been found!" << endl
			<< abort(FatalError);
	}

	// checking the polygon [3/29/2022 Amir]
	Entity2d_Polygon::Check(thePoly);

	const auto& pts = thePoly.Points();
	const auto& p0 = FirstItem(pts);
	const auto& p1 = LastItem(pts);
	const auto& pm = pts.at(pts.size() / 2);

	if (thePoly.IsClosed())
	{
		const auto length = Cad_Tools::CalcLength(thePoly, theSurface);
		const auto elmSize = this->SizeFun()->Value(pm);
	}
	else
	{

	}
}