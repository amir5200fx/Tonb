#include <Voyage_Distance.hxx>

#include <VoyageGeo_Path2.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Voyage_MetricInfo.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Voyage_Distance::Value() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	return theValue_;
}

void tnbLib::Voyage_Distance::Perform()
{
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG)
			<< "no path has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info. has been found." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	const auto& earth = path->Earth();
	if (NOT earth)
	{
		FatalErrorIn(FunctionSIG)
			<< "no earth has been found." << endl
			<< abort(FatalError);
	}
	auto metrics = earth->GetMetrics();
	Debug_Null_Pointer(metrics);
	auto sizeFun = 
		std::make_shared<GeoSizeFun2d_Uniform>
		(1.0, metrics->BoundingBox());
	auto metricInfo = 
		std::make_shared<Geo_MetricPrcsrAnIso_Info>
		(GetInfo()->MetricInfo(), GetInfo()->NbSamples());
	auto metricProcsr = 
		std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metrics, metricInfo);
	Standard_Real tot_dist = 0;
	for (const auto& x : path->Curves())
	{
		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);
		const auto& geom = curve->Geometry();
		Debug_Null_Pointer(geom);
		auto alg = std::make_shared<Mesh2d_CurveAnIso>
			(
				geom,
				geom->FirstParameter(), geom->LastParameter(), 
				metricProcsr, GetInfo()->CurveMeshInfo());
		auto dist = alg->CalcLengthWithChecking(GetInfo()->MaxSubdivideLev());
		tot_dist += dist;
	}
	theValue_ = tot_dist;
	Change_IsDone() = Standard_True;
}