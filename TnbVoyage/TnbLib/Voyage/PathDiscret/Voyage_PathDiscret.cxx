#include <Voyage_PathDiscret.hxx>

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
#include <Geo2d_MetricFunction.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom2d_Curve.hxx>

void tnbLib::Voyage_PathDiscret::Perform()
{
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no path has been loaded." << endl
			<< abort(FatalError);
	}
	if (Size() <= 0.0)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no size has been assigned." << endl
			<< abort(FatalError);
	}
	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info. has been found." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	const auto size = Size();

	auto metricInfo = std::make_shared<Geo_MetricPrcsrAnIso_Info>();
	metricInfo->OverrideIntegInfo(AlgInfo()->MetricInfo());

	const auto& earth = path->Earth();
	if (NOT earth)
	{
		FatalErrorIn(FunctionSIG)
			<< "no earth found on the path." << endl
			<< abort(FatalError);
	}
	auto metrics = earth->GetMetrics();
	auto sizeFun = 
		std::make_shared<GeoSizeFun2d_Uniform>
		(Size(), metrics->BoundingBox());

	auto metricPrcsr = 
		std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metrics, metricInfo);
	for (const auto& x : path->Curves())
	{
		const auto& curve = x->Curve();
		const auto& geom = curve->Geometry();
		const auto alg = 
			std::make_shared<Mesh2d_CurveAnIso>
			(
				geom, 
				geom->FirstParameter(), geom->LastParameter(), 
				metricPrcsr, AlgInfo()->CurveMeshInfo()
				);
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
		x->Mesh() = alg->Mesh();
	}
	Change_IsDone() = Standard_True;
}