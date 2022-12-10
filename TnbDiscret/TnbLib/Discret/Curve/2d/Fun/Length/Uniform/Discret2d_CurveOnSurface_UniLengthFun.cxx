#include <Discret2d_CurveOnSurface_UniLengthFun.hxx>

#include <Discret_Curve_Samples.hxx>
#include <Cad_ParaCurve.hxx>
#include <Cad_GeomSurface.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Discret2d_CurveOnSurface_UniLengthFun::Subdivide
(
	const std::shared_ptr<Cad_ParaCurve>& theCurve, 
	const Standard_Real theU0,
	const Standard_Real theU1
) const
{
	auto samples = Samples()->CalcXs(theU0, theU1);
	std::vector<Pnt3d> coords;
	coords.reserve(samples.size());

	const auto& geom = Surface();
	Debug_Null_Pointer(geom);

	for (auto x : samples)
	{
		auto pt = geom->Value(theCurve->Value(x));
		coords.push_back(std::move(pt));
	}
	Standard_Real len = 0;
	for (size_t i = 1; i < coords.size(); i++)
	{
		const auto& p0 = coords.at(i - 1);
		const auto& p1 = coords.at(i);
		len += p0.Distance(p1);
	}

	return len > Size();
}