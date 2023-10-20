#include <Aft_MetricPrcsr.hxx>
#include <VoyageFun_CostFunction_Resistane.hxx>
#include <VoyageFun_ProfiledCalmResist.hxx>
#include <Voyage_Profile.hxx>
#include <Voyage_RepairNet.hxx>
#include <VoyageSim_MinFuel.hxx>
#include <VoyageWP_Connect.hxx>
#include <VoyageWP_Connect2.hxx>
#include <VoyageWP_Net.hxx>
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
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <GeoSizeFun2d_Background.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Geo_SteffenInterplFunction.hxx>
#include <Cad_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomCurve.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_FastDiscrete.hxx>
#include <Pln_Edge.hxx>
#include <FastDiscrete_Params.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
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

auto loadData(const std::string& fileName)
{
	std::vector<std::pair<double, double>> qs;
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Error: Could not open file: " << fileName << endl
			<< abort(FatalError);
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		double x, y;
		char delimiter;
		if (!(iss >> x >> delimiter >> y))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid line in CSV file: " << fileName << endl
				<< abort(FatalError);
		}
		qs.emplace_back(x, y);
	}
	file.close();
	return std::move(qs);
}

int main()
{
	{// settings
		//VoyageMesh_BaseSize::verbose = 2;
	}

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

	//OFstream myFile("earth.plt");
	for (const auto& x : surfaces)
	{
		auto tri = Cad_Tools::Triangulation(*x);
		//tri->ExportToPlt(myFile);
	}

	auto offsets = std::make_shared<Entity2d_Polygon>();
	{
		auto& pts = offsets->Points();

		//pts.push_back(Voyage_Tools::ConvertToUV({ 1.0, 1.0 })); // yaghubi example
		//pts.push_back(Voyage_Tools::ConvertToUV({ 2.0, 2.0 }));

		//pts.push_back(Voyage_Tools::ConvertToUV({ 25.25, 55.27 }));
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
	auto h = vel * hour;
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

		//OFstream planeFile("polygons.plt");
		for (const auto& x : alg->Path()->Curves())
		{
			const auto& mesh = x->Mesh();
			//mesh->ExportToPlt(planeFile);
		}

		for (const auto& x : alg->Path3D())
		{
			//x->ExportToPlt(myFile);
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
	wayPoints->SetSize(h);
	// assign the state function (dry & wet function)
	wayPoints->SetStateFun([](const Pnt2d&) {return true; });
	wayPoints->Perform();
	{ // Calculate bounding bxo
		auto domain = 
			Geo_BoxTools::Union
		(
			Geo_BoxTools::GetBox(wayPoints->StarMesh()->Points(), 1.0e-6), 
			Geo_BoxTools::GetBox(wayPoints->PortMesh()->Points(), 1.0e-6)
		);
	}

	//OFstream triFile1("triangle.plt");
	//OFstream triFile2("triangle1.plt");
	//OFstream triFile1("triangle0.vtk");
	//OFstream triFile2("triangle1.vtk");
	{// plot the starboard mesh [9/6/2023 aamir]
		const auto mesh = /*Voyage_Tools::ConvertToVoyageSystem(**/wayPoints->StarMesh()/*)*/;
		//mesh->ExportToPlt(triFile1);
		//mesh->ExportToVtk(triFile1);
		//wayPoints->PortMesh()->ExportToPlt(triFile1);
	}
	//PAUSE;
	const auto grid = wayPoints->Grid();
	{
		const auto alg = std::make_shared<VoyageWP_Connect2>();
		alg->SetSize(2);
		alg->SetStateFun([](const Pnt2d&, const Pnt2d&) {return true; });
		alg->SetNet(grid);
		alg->Perform();
	}

	{// repair the grid
		auto alg = std::make_shared<Voyage_RepairNet>(grid);
		alg->Perform();
	}

	OFstream gridFile("grid.plt");
	
	grid->ExportToPlt(gridFile);

	std::cout << std::endl;
	std::cout << " # Simulating the Fuel consumption..." << std::endl;
	
	std::shared_ptr<VoyageFun_ProfiledCalmResist> profile;
	{// putting the profile values into a list.
		//auto qs = loadData("HoltropResistance.csv");
		std::vector<std::pair<double, double>> qs;
		qs.emplace_back(0, 0);
		qs.emplace_back(0.625, 2.3);
		qs.emplace_back(1.25, 8.3);
		qs.emplace_back(1.875, 17.7);
		qs.emplace_back(2.5, 30.5);
		qs.emplace_back(3.125, 46.4);
		qs.emplace_back(3.75, 65.4);
		qs.emplace_back(4.375, 87.4);
		qs.emplace_back(5, 112.5);
		qs.emplace_back(5.625, 140.5);
		qs.emplace_back(6.25, 171.4);
		qs.emplace_back(6.875, 205.3);
		qs.emplace_back(7.5, 242);
		qs.emplace_back(8.125, 281.6);
		qs.emplace_back(8.75, 324);
		qs.emplace_back(9.375, 369.2);
		qs.emplace_back(10, 417.2);
		qs.emplace_back(10.625, 468);
		qs.emplace_back(11.25, 521.7);
		qs.emplace_back(11.875, 578.3);
		qs.emplace_back(12.5, 637.9);
		qs.emplace_back(13.125, 700.6);
		qs.emplace_back(13.75, 766.8);
		qs.emplace_back(14.375, 836.7);
		qs.emplace_back(15, 910.7);
		qs.emplace_back(15.625, 989.3);
		qs.emplace_back(16.25, 1073.2);
		qs.emplace_back(16.875, 1163.2);
		qs.emplace_back(17.5, 1259.9);
		qs.emplace_back(18.125, 1364.6);
		qs.emplace_back(18.75, 1478.2);
		qs.emplace_back(19.375, 1601.9);
		qs.emplace_back(20, 1737.1);
		qs.emplace_back(20.625, 1885.3);
		qs.emplace_back(21.25, 2048.3);
		qs.emplace_back(22.5, 2421.6);
		qs.emplace_back(23.125, 2632.7);
		qs.emplace_back(23.75, 2862.4);
		for (auto&[u,res]:qs)
		{
			u *= 1.852;
		}
		auto geo_profile = std::make_shared<Geo_SteffenInterplFunction>(std::move(qs));
		geo_profile->Perform();
		profile = 
			std::make_shared<VoyageFun_ProfiledCalmResist>
		(std::make_shared<Voyage_Profile>(std::move(geo_profile)));
	}

	double avg_vel = 18.52; // kmph
	double min_vel = 0.5 * avg_vel;
	double max_vel = 1.2 * avg_vel;

	double maxDay = 3;
	
	auto cost_fun = 
		std::make_shared<VoyageFun_CostFunction_Resistane>
	([](const Pnt2d&, double)->std::pair<double, double> {return { 2.0,0.0 }; }, profile, std::make_pair(min_vel, max_vel), std::make_pair(0,(maxDay+0.5)*24));

	
	VoyageSim_MinFuel::verbose = 1;
	auto sim = std::make_shared<VoyageSim_MinFuel>();

	sim->SetMinVel(min_vel);
	sim->SetMaxVel(max_vel);
	sim->SetVel(avg_vel);
	sim->SetTimeStep(hour);
	sim->SetNbSamples(1);
	sim->SetTimeRes(hour);
	sim->SetNbLevels(2);
	sim->SetNet(grid);
	sim->SetBaseTime(0);
	sim->SetMaxDay(maxDay);
	{
		auto prcsr = 
			Voyage_Tools::MakeMetricPrcsr
		(Voyage_Tools::MakeUniformSizeMap(*earth), *earth, *metricInfo);
		auto my_dist_fun = [prcsr](const Pnt2d& theP0, const Pnt2d& theP1)
		{
			return prcsr->CalcDistance(theP0, theP1);
		};
		sim->SetDistFunc(my_dist_fun);

		auto weather_fun = 
			[cost_fun]
		(
			const std::pair<Pnt2d, double>& st0,
			const std::pair<Pnt2d, double>& st1, 
			const double dis, const double nbsamples
			)
		{
			cost_fun->SetDistance(dis);
			cost_fun->SetNbSamples(nbsamples);
			cost_fun->SetShipVel(dis / (st1.second - st0.second));
			return
				cost_fun->Value
				(
					{ st0.first,{st0.second} },
					{ st1.first, {st1.second} }
			);
		};
		sim->SetResistFunc(weather_fun);

		sim->Init();
		sim->Perform(grid->Departure()->Index());
	}

	//auto best_path = sim->RetrievePath(sim->SelectArrivalNode(MEAN(sim->MinTimeArrival(), sim->MaxTimeArrival())));
	auto best_path = sim->RetrievePath(sim->LowestCostNode());

	std::cout << " path size = " << best_path.size() << std::endl;

	for (const auto& [loc, time, vel] : best_path)
	{
		std::cout << " - coord: (" << loc.value << ")"
			<< ", time: " << time.value
			<< ", velocity: " << vel.value
			<< std::endl;
	}

	std::cout << std::endl;
	std::cout << " - the application is successfully performed." << std::endl;

	return 1;
}