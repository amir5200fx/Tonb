#include <VoyageGeo_PathGeneration.hxx>
#include <VoyageGeo_Earth.hxx>
#include <VoyageGeo_Path2.hxx>
#include <Voyage_Tools.hxx>
#include <Voyage_MetricInfo.hxx>
#include <Voyage_Distance.hxx>
#include <Voyage_PathDiscret.hxx>
#include <Voyage_PathOnEarth.hxx>
#include <Voyage_SizeMap.hxx>
#include <Voyage_Waypoints.hxx>
#include <VoyageMesh_SizeMap.hxx>
#include <VoyageMesh_BaseSize.hxx>
#include <VoyageMesh_BaseSizeInfo.hxx>
#include <VoyageMesh_CorrectSizeMap.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <GeoSizeFun2d_Background.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Cad_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomCurve.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_FastDiscrete.hxx>
#include <Pln_Edge.hxx>
#include <FastDiscrete_Params.hxx>
#include <Geo_Tools.hxx>
#include <Geo3d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Chain.hxx>
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

	auto offsets = std::make_shared<Entity2d_Polygon>();
	{
		auto& pts = offsets->Points();
		//pts.push_back(Voyage_Tools::ConvertToUV({ 25.25, 55.27 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 25.25, 55.27 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 25.6, 55.2 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 26.4, 56.4 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 8.0, 77.0 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 5.8, 80.1 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 6.7, 94.0 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 7.0, 97.0 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 1.1, 103.6 }));
		pts.push_back(Voyage_Tools::ConvertToUV({ 1.28009, 103.85095 }));

		//Voyage_Tools::CalcTurningAngle(pts.at(0), pts.at(1), pts.at(2));
		//std::exit(1);
	}

	

	auto metricInfo = std::make_shared<Voyage_MetricInfo>();
	std::shared_ptr<VoyageGeo_Path2> path;
	{// Generate the path [8/27/2023 Payvand]
		auto alg = std::make_shared<VoyageGeo_PathGeneration>(offsets, earth);
		alg->Perform();

		path = alg->Path();

		std::cout << std::endl;
		std::cout << " The path is successfully generated." << std::endl;
	}

	Standard_Real dist = 0;
	{// Calculate the distance [8/27/2023 Payvand]
		auto alg = std::make_shared<Voyage_Distance>(path, metricInfo);
		alg->Perform();

		dist = alg->Value();

		std::cout << std::endl;
		std::cout << " The distance is successfully calculated." << std::endl;
		std::cout << " - dist: " << dist << std::endl;
	}

	Standard_Real vel = Voyage_Tools::KtsToKmh(10.0); // velocity of the vessel [8/27/2023 Payvand]
	Standard_Real hour = 5.0;
	auto h = dist / (vel * hour);
	std::cout << std::endl;
	std::cout << " - Size: " << h << std::endl;
	std::cout << std::endl;
	auto voyagePath = std::make_shared<Entity2d_Chain>();
	{// approximate the path [8/27/2023 Payvand]
		auto alg = std::make_shared<Voyage_PathDiscret>(path, metricInfo, h);
		alg->Perform();

		for (const auto& x : alg->Path()->Curves())
		{
			auto chain = Geo_Tools::RetrieveChain(*x->Mesh());
			voyagePath->Add(*chain);
		}

		std::cout << std::endl;
		std::cout << " The path is successfully discretized." << std::endl;
	}

	
	{
		auto alg = std::make_shared<Voyage_PathOnEarth>(earth, path);
		alg->Perform();

		OFstream planeFile("polygons.plt");
		for (const auto& x : alg->Path()->Curves())
		{
			const auto& mesh = x->Mesh();
			mesh->ExportToPlt(planeFile);
		}

		for (const auto& x : alg->Path3D())
		{
			x->ExportToPlt(myFile);
		}

		std::cout << std::endl;
		std::cout << " The three-dimensional path is successfully discretized." << std::endl;
	}

	OFstream myVoyagePath("voyage.txt");
	const auto& pts = voyagePath->Points();
	for (const auto& x : voyagePath->Connectivity())
	{
		auto i0 = x.Value(0);
		auto i1 = x.Value(1);
		myVoyagePath
			<< Voyage_Tools::ConvertToVoyageSystem(pts.at(Index_Of(i0))) 
			<< "  " 
			<< Voyage_Tools::ConvertToVoyageSystem(pts.at(Index_Of(i1))) << endl;
	}

	// creating the size maps [9/3/2023 Payvand]
	Voyage_SizeMap::verbose = 1;
	auto sizeMap = std::make_shared<Voyage_SizeMap>();
	sizeMap->SetPath(path);
	sizeMap->SetInfo(metricInfo);
	sizeMap->Perform();
	//return 1;
	Voyage_Waypoints::verbose = 1;
	auto wayPoints = std::make_shared<Voyage_Waypoints>();
	wayPoints->SetPath(path);
	wayPoints->SetInfo(metricInfo);
	wayPoints->SetPortSizeFunction(sizeMap->Port());
	wayPoints->SetStarboardSizeFunction(sizeMap->Startboard());
	wayPoints->Perform();

	OFstream triFile("triangle.plt");
	OFstream triFile1("triangle0.vtk");
	OFstream triFile2("triangle1.vtk");
	{// plot the starboard mesh [9/6/2023 aamir]
		const auto mesh = /*Voyage_Tools::ConvertToVoyageSystem(**/wayPoints->StarMesh()/*)*/;
		mesh->ExportToPlt(triFile);
		mesh->ExportToVtk(triFile1);
		wayPoints->PortMesh()->ExportToVtk(triFile2);
	}

	return 1;

	auto metricsFun = earth->GetMetrics();
	auto uniSizeMap = std::make_shared<GeoSizeFun2d_Uniform>(1.0, metricsFun->BoundingBox());
	auto metricPrcsrInfo = std::make_shared<Geo_MetricPrcsrAnIso_Info>(metricInfo->MetricInfo(), metricInfo->NbSamples());
	auto metrics = std::make_shared<Geo2d_MetricPrcsrAnIso>(uniSizeMap, metricsFun, metricPrcsrInfo);
	std::shared_ptr<std::vector<std::vector<Standard_Real>>> bHs;
	{// Create the base size map [8/28/2023 aamir]
		auto algInfo = std::make_shared<VoyageMesh_BaseSizeInfo>();
		auto alg = std::make_shared<VoyageMesh_BaseSize>(path->RetrieveOffsets(), metrics, algInfo);
		alg->Perform();
		bHs = alg->Hs();

		std::cout << std::endl;
		std::cout << " The base sizes is successfully computed." << std::endl;

		size_t k = 0;
		for (const auto& x : *bHs)
		{
			std::cout << std::endl;
			std::cout << " - Profile's id: " << k << std::endl;
			for (size_t i = 0; i < x.size(); i++)
			{
				std::cout << x.at(i) << " ";
				if (i % 10 == 0) std::cout << std::endl;
			}
		}
	}

	std::shared_ptr<GeoMesh2d_Background> unCorrSizeMap;
	{// Calculate the uncorrected size map [8/28/2023 aamir]
		auto alg = std::make_shared<VoyageMesh_SizeMap>();
		const auto baseSize = 1.0E-3;
		alg->SetBaseSize(baseSize);
		alg->SetHs(bHs);
		alg->SetPath(path);

		alg->Perform();
		unCorrSizeMap = alg->BackMesh();

		std::cout << std::endl;
		std::cout << " The uncorrected size map is successfully computed." << std::endl;
	}

	auto unCorrSizeFun = 
		std::make_shared<GeoSizeFun2d_Background>
		(uniSizeMap->BoundingBox(), unCorrSizeMap);

	std::shared_ptr<GeoMesh2d_Background> corrSizeMap;
	{// Calculate the size map correction [8/29/2023 aamir]
		VoyageMesh_CorrectSizeMap::verbose = 1;
		auto alg = std::make_shared<VoyageMesh_CorrectSizeMap>();
		alg->SetPath(path);
		alg->SetDirection(voyageLib::PathDirect::Starboard);
		alg->SetSizeFunction(unCorrSizeFun);
		alg->SetInfo(metricInfo);

		alg->Perform();
		corrSizeMap = alg->BackMesh();

		std::cout << std::endl;
		std::cout << " The Size map correction is successfully computed." << std::endl;
	}

	OFstream mySizeMapFile("sizeMap.plt");
	unCorrSizeMap->ExportToPlt(mySizeMapFile);
	corrSizeMap->ExportToPlt(mySizeMapFile);

	//Pnt2d P02(Geo_Tools::DegToRadian(25.0), Geo_Tools::DegToRadian(-5.0));

	//Pnt2d P01(Geo_Tools::DegToRadian(49.6), Geo_Tools::DegToRadian(-53.0));
	
	//Pnt2d P00(Geo_Tools::DegToRadian(47.6), Geo_Tools::DegToRadian(-60.0));
	// coordinates 1: New York City [7/27/2023 Payvand]
	// Latitude: 40.7128, Longitude: -73.935242 [7/27/2023 Payvand]
	//Pnt2d P0(Geo_Tools::DegToRadian(-33.0), Geo_Tools::DegToRadian(-71.6));
	// coordinates 2: Lisbon City [7/27/2023 Payvand]
	// Latitude: 38.736946, Longitude: -9.142685 [7/27/2023 Payvand]
	//Pnt2d P1(Geo_Tools::DegToRadian(31.4), Geo_Tools::DegToRadian(121.8));
	// distance: 5,422.97 km [7/27/2023 Payvand]
	// avg. velocity: 14.8 kmph [7/27/2023 Payvand]
	// Resolution: 14.8 [7/27/2023 Payvand]

	//auto surface = earth->Surface();
	/*std::cout << "u0: " << surface->FirstParameterU() << ", u1: " << surface->LastParameterU() << std::endl;
	std::cout << "v0: " << surface->FirstParameterV() << ", v1: " << surface->LastParameterV() << std::endl;
	std::cout << surface->Value({ 2.0,1.5708 });
	return 1;*/
	/*auto domain = surface->ParametricBoundingBox();
	auto sizeFun = std::make_shared<GeoSizeFun2d_Uniform>(14.8, domain);
	auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(surface->Geometry(), domain);

	auto prcsr = std::make_shared<Geo2d_MetricPrcsrAnIso>(sizeFun, metricFun, myPrcsrInfo);*/

	//auto path = std::make_shared<VoyageGeo_PathGeneration>();
	//path->SetCoords({ P02, P01, P00, P0,P1 });
	//path->SetCurveInfo(myMeshInfo);
	//path->SetMetricPrsr(prcsr);
	//path->SetSurface(surface);

	//path->Perform();
	//
	//auto apprxCurveInfo = std::make_shared<Geo_ApprxCurve_Info>();
	//for (const auto& x : path->Paths())
	//{
	//	auto mesh = Cad_PreviewTools::PreviewCurve(x->Geometry(), 100);
	//	/*Geo3d_ApprxCurve alg(x->Geometry(), x->FirstParameter(), x->LastParameter(), apprxCurveInfo);
	//	alg.Perform();
	//	const auto& mesh = alg.Chain();*/
	//	mesh->ExportToPlt(myFile);
	//}
	return 1;
}