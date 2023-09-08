#include <VoyageWP_Dist.hxx>

#include <VoyageGeo_Earth.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_Dist::Perform()
{
	if (NOT Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "the earth is not loaded." << endl
			<< abort(FatalError);
	}
	const auto& earth = Earth();
	if (NOT WPs())
	{
		FatalErrorIn(FunctionSIG)
			<< "the waypoints are not loaded." << endl
			<< abort(FatalError);
	}
	const auto& wps = WPs();
	auto metrics = earth->GetMetrics();
	Debug_Null_Pointer(metrics);
	auto sizeFun =
		std::make_shared<GeoSizeFun2d_Uniform>
		(1.0, metrics->BoundingBox());
	if (NOT MetricInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric info. has been loaded." << endl
			<< abort(FatalError);
	}
	const auto& metricInfo = MetricInfo();
	auto metricProcsr =
		std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metrics, metricInfo);
	theWPdists_.reserve(NbWPs() - 1);
	theDists_.reserve(NbWPs());
	const auto& wps_points = wps->Points();
	if (NOT MeshInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh info. has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT MaxSubLev())
	{
		FatalErrorIn(FunctionSIG)
			<< "no max. sub. lev. has been set." << endl
			<< abort(FatalError);
	}
	for (size_t i = 1; i < NbWPs(); i++)
	{
		const auto& p0 = wps_points.at(i - 1);
		const auto& p1 = wps_points.at(i);
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		Debug_Null_Pointer(geom);
		auto alg = std::make_shared<Mesh2d_CurveAnIso>
			(
				geom,
				geom->FirstParameter(), geom->LastParameter(),
				metricProcsr, MeshInfo());
		auto dist = alg->CalcLengthWithChecking(MaxSubLev());
		theWPdists_.push_back(dist);
	}
	for (const auto& x : wps_points)
	{
		auto geom = Pln_CurveTools::MakeSegment(Coord(), x);
		Debug_Null_Pointer(geom);
		auto alg = std::make_shared<Mesh2d_CurveAnIso>
			(
				geom,
				geom->FirstParameter(), geom->LastParameter(),
				metricProcsr, MeshInfo());
		auto dist = alg->CalcLengthWithChecking(MaxSubLev());
		theDists_.push_back(dist);
	}
	Change_IsDone() = Standard_True;
}