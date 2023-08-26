#include <VoyageGeo_PathGeneration.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Cad_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomCurve.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_Params.hxx>
#include <Geo_Tools.hxx>
#include <Geo3d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt2d.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>
#include <Poly_Triangulation.hxx>

using namespace tnbLib;

static auto myIntgInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
static auto myPrcsrInfo = std::make_shared<Geo_MetricPrcsrAnIso_Info>(myIntgInfo);

static auto myMeshInfo = std::make_shared<Mesh_Curve_Info>();

static double myAngle = 5.0;
static double myDeflection = 1.0E-3;
static double myMinSize = 1.0E-6;
static auto inParallel = false;
static auto inRalative = true;
static auto adaptiveMin = false;
static auto internalVerticesMode = true;
static auto controlSurfaceDeflection = true;

int main()
{
	auto earth = std::make_shared<VoyageGeo_Earth>();

	const auto d = earth->Surface()->BoundingBox().Diameter();
	auto params = FastDiscrete_Params();
	params.Angle = Geo_Tools::DegToRadian(myAngle);
	params.Deflection = myDeflection * d;
	params.MinSize = myMinSize * d;
	params.InParallel = inParallel;
	params.Relative = inRalative;
	params.AdaptiveMin = adaptiveMin;
	params.InternalVerticesMode = internalVerticesMode;
	params.ControlSurfaceDeflection = controlSurfaceDeflection;

	{// timer scope
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_s);
		Cad_FastDiscrete::Triangulation(earth->Geometry()->Shape(), params);
	}

	const auto surfaces = Cad_Tools::RetrieveTriangulation(earth->Geometry()->Shape());

	OFstream myFile("earth.plt");
	for (const auto& x : surfaces)
	{
		auto tri = Cad_Tools::Triangulation(*x);
		tri->ExportToPlt(myFile);
	}

	Pnt2d P02(Geo_Tools::DegToRadian(25.0), Geo_Tools::DegToRadian(-5.0));

	Pnt2d P01(Geo_Tools::DegToRadian(49.6), Geo_Tools::DegToRadian(-53.0));
	
	Pnt2d P00(Geo_Tools::DegToRadian(47.6), Geo_Tools::DegToRadian(-60.0));
	// coordinates 1: New York City [7/27/2023 Payvand]
	// Latitude: 40.7128, Longitude: -73.935242 [7/27/2023 Payvand]
	Pnt2d P0(Geo_Tools::DegToRadian(-33.0), Geo_Tools::DegToRadian(-71.6));
	// coordinates 2: Lisbon City [7/27/2023 Payvand]
	// Latitude: 38.736946, Longitude: -9.142685 [7/27/2023 Payvand]
	Pnt2d P1(Geo_Tools::DegToRadian(31.4), Geo_Tools::DegToRadian(121.8));
	// distance: 5,422.97 km [7/27/2023 Payvand]
	// avg. velocity: 14.8 kmph [7/27/2023 Payvand]
	// Resolution: 14.8 [7/27/2023 Payvand]

	auto surface = earth->Surface();
	std::cout << "u0: " << surface->FirstParameterU() << ", u1: " << surface->LastParameterU() << std::endl;
	std::cout << "v0: " << surface->FirstParameterV() << ", v1: " << surface->LastParameterV() << std::endl;
	std::cout << surface->Value({ 2.0,1.5708 });
	return 1;
	auto domain = surface->ParametricBoundingBox();
	auto sizeFun = std::make_shared<GeoSizeFun2d_Uniform>(14.8, domain);
	auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(surface->Geometry(), domain);

	auto prcsr = std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metricFun, myPrcsrInfo);

	auto path = std::make_shared<VoyageGeo_PathGeneration>();
	path->SetCoords({ P02, P01, P00, P0,P1 });
	path->SetCurveInfo(myMeshInfo);
	path->SetMetricPrsr(prcsr);
	path->SetSurface(surface);

	path->Perform();
	
	auto apprxCurveInfo = std::make_shared<Geo_ApprxCurve_Info>();
	for (const auto& x : path->Paths())
	{
		auto mesh = Cad_PreviewTools::PreviewCurve(x->Geometry(), 100);
		/*Geo3d_ApprxCurve alg(x->Geometry(), x->FirstParameter(), x->LastParameter(), apprxCurveInfo);
		alg.Perform();
		const auto& mesh = alg.Chain();*/
		mesh->ExportToPlt(myFile);
	}
	return 1;
}