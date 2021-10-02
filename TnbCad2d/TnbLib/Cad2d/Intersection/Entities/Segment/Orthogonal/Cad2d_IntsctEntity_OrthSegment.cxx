#include <Cad2d_IntsctEntity_OrthSegment.hxx>

#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::tuple<std::shared_ptr<tnbLib::Pln_Curve>, std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::Cad2d_IntsctEntity_OrthSegment::SubdivideCurve
(
	const Pln_Curve & theCurve, 
	const Cad2d_IntsctEntity_OrthSegment & theEntity
)
{
	if (NOT INSIDE(theEntity.CharParameter(), theCurve.FirstParameter(), theCurve.LastParameter()))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid parameter to subdivide the curve" << endl
			<< abort(FatalError);
	}

	auto[c0, c1] = theCurve.Split(theEntity.CharParameter());
	auto t = std::make_tuple(std::move(c0), std::move(c1));
	return std::move(t);
}