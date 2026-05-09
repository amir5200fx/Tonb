#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Cad_gModifySingularPlane.hxx>
#include <Cad_gSingularity.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_SingularityHorizons.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_ApprxMetricIO.hxx>
#include <Cad_gApprxParaPlane.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Plane.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_ParaWire.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <GeoSizeFun2d_Surface.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_PolygonGraphEdge.hxx>
#include <Geo_Tools.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>

namespace tnbLib
{
	static const auto loadExt = Cad_ApprxMetricIO::extension;
	static const auto saveExt = Entity2d_Triangulation::extension + "list";

	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;
	static std::shared_ptr<Geo_ApprxCurve_Info> myApproxInfo = std::make_shared<Geo_ApprxCurve_Info>();

	static std::shared_ptr<Cad_ApprxMetricIO> myApproxMetrics;
	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myPlanes;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static auto myTol = 1.0E-6;
	static auto mySingZoneWeight = Cad_gSingularity::DEFAULT_WEIGHT;

	static std::string myFileName;

	static double myDegenCrit = Cad_SingularityHorizons::DEFAULT_DEGEN_CRITERION;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTol(double x)
	{
		myDegenCrit = x;
		if (verbose)
		{
			Info << endl
				<< " - the degeneracy criterion is set to: " << x << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myApproxMetrics = file::LoadFile<std::shared_ptr<Cad_ApprxMetricIO>>(name + loadExt, verbose);
		if (NOT myApproxMetrics)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape file is null!" << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myPlanes, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			return true;
		}
		return false;
	}

	void loadSizeFun()
	{
		if (checkFolder("sizeMap"))
		{
			FatalErrorIn(FunctionSIG)
				<< "no size map has been found!" << endl;
		}
		else
		{
			const auto currentPath = boost::filesystem::current_path();

			// change the current path [12/4/2021 Amir]
			boost::filesystem::current_path(currentPath.string() + R"(\sizeMap)");

			auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo3d_SizeFunction::extension).string();

			auto sizeFun = file::LoadFile<std::shared_ptr<Geo3d_SizeFunction>>(name + Geo3d_SizeFunction::extension, verbose);
			if (NOT sizeFun)
			{
				FatalErrorIn(FunctionSIG)
					<< " the size function file is null" << endl
					<< abort(FatalError);
			}

			//- change back the current path
			boost::filesystem::current_path(currentPath);

			mySizeFun = std::move(sizeFun);
		}
	}

	auto calcSize(const Pnt3d& pt)
	{
		return mySizeFun->Value(pt);
	}

	auto createMetricCalculator()
	{
		if (mySizeFun)
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_SizeFun>(&calcSize);
			return std::move(alg);
		}
		else
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_Std>();
			return std::move(alg);
		}
	}

	auto approxPlane(const std::shared_ptr<GModel_Plane>& thePlane)
	{
		auto alg = std::make_shared<Cad_gApprxParaPlane>(thePlane, myApproxInfo);
		alg->Perform();
		if (NOT alg->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		return alg->Polygons();
	}

	auto approxPlane(const std::vector<std::shared_ptr<GModel_Plane>>& thePlanes)
	{
		std::vector<std::shared_ptr<Entity2d_Polygon>> polys;
		auto iter = thePlanes.begin();
		auto p = approxPlane(*iter);
		for (auto& x : p)
		{
			polys.push_back(std::move(x));
		}
		iter++;
		while (iter NOT_EQUAL thePlanes.end())
		{
			auto p = approxPlane(*iter);
			for (auto& x : p)
			{
				polys.push_back(std::move(x));
			}
			iter++;
		}
		return std::move(polys);
	}

	auto makeOrignPlanes(const std::vector<std::shared_ptr<Aft2d_gRegionPlaneSurface>>& thePlanes)
	{
		std::vector<std::shared_ptr<GModel_Plane>> origns;
		origns.reserve(thePlanes.size());
		for (const auto& x : thePlanes)
		{
			auto pln = Aft2d_gRegionPlaneSurface::MakeOrignPlane<GModel_Plane>(x);
			origns.push_back(std::move(pln));
		}
		return std::move(origns);
	}

	auto makeTriangulation(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePolys)
	{
		auto chain = Geo_Tools::RetrieveChain(thePolys);
		auto tri = Geo_Tools::Triangulation(*chain);
		return std::move(tri);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		loadSizeFun();

		auto metricCalculator = createMetricCalculator();

		const auto& myShape = myApproxMetrics->Model();
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}
		const auto surfaces = GModel_Tools::GetSurfaces(myShape->Shape());
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface is found!" << endl
				<< abort(FatalError);
		}

		const auto& myApproxMap = myApproxMetrics->Approx();
		for (const auto& x : surfaces)
		{
			Debug_Null_Pointer(x);
			auto iter = myApproxMap.find(x->Index());
			if (iter IS_EQUAL myApproxMap.end())
			{
				FatalErrorIn(FunctionSIG)
					<< "the item is not in the tree!" << endl
					<< abort(FatalError);
			}
			const auto& metricApprox = iter->second;
			if (NOT metricApprox)
			{
				FatalErrorIn(FunctionSIG)
					<< "no approximation has been found for the surface!" << endl
					<< abort(FatalError);
			}
			auto geom = GModel_Tools::RetrieveGeometry(*x);
			if (NOT geom)
			{
				FatalErrorIn(FunctionSIG)
					<< "no geometry has been found!" << endl
					<< abort(FatalError);
			}
			Standard_Real myMaxDet = 0;
			if (mySizeFun)
			{
				auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geom, *metricApprox, &calcSize);
				myMaxDet = maxDet;
			}
			else
			{
				auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geom, *metricApprox);
				myMaxDet = maxDet;
			}
			auto criterion = Cad_ColorApprxMetric::CalcCriterion(myMaxDet);

			auto colors = std::make_shared<Cad_ColorApprxMetric>();

			colors->SetCriterion(myDegenCrit);

			colors->LoadGeoemtry(geom);
			colors->LoadApproximation(metricApprox);
			colors->LoadMetricCalculator(metricCalculator);

			colors->Perform();
			if (NOT colors->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			auto horizonAlg = std::make_shared<Cad_SingularityHorizons>();

			horizonAlg->SetDegeneracyCriterion(myDegenCrit);
			horizonAlg->SetMaxDet(myMaxDet);

			horizonAlg->LoadGeometry(geom);
			horizonAlg->LoadApproximation(metricApprox);
			horizonAlg->LoadMetricCalculato(metricCalculator);

			horizonAlg->Perform();
			if (NOT horizonAlg->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			std::cout << "nb horizons: " << horizonAlg->NbHorizons() << std::endl;

			if (horizonAlg->HasHorizon())
			{
				auto paraPlane = GModel_Tools::GetParaPlane(x, myTol);
				auto regionPln = Aft2d_gRegionPlaneSurface::MakePlane(paraPlane);

				auto surfSizeFun = std::make_shared<GeoSizeFun2d_Surface>(geom, mySizeFun, x->ParaBoundingBox());

				auto zonesAlg = std::make_shared<Cad_gSingularity>();

				zonesAlg->LoadColors(colors);
				zonesAlg->LoadHorizons(horizonAlg);
				zonesAlg->LoadSizeFun(surfSizeFun);

				zonesAlg->LoadParaPlane(regionPln);

				zonesAlg->SetWeight(mySingZoneWeight);

				zonesAlg->Perform();
				if (NOT zonesAlg->IsDone())
				{
					FatalErrorIn(FunctionSIG)
						<< "the application is not performed!" << endl
						<< abort(FatalError);
				}

				auto modifyAlg = std::make_shared<Cad_gModifySingularPlane>();

				modifyAlg->LoadColors(std::move(colors));
				modifyAlg->LoadZones(zonesAlg->Zones());
				modifyAlg->LoadPlane(regionPln);
				modifyAlg->LoadSurface(x);
				modifyAlg->LoadApproxInfo(myApproxInfo);

				modifyAlg->SetTolerance(myTol);

				modifyAlg->Perform();
				if (NOT modifyAlg->IsDone())
				{
					FatalErrorIn(FunctionSIG)
						<< "the application is not performed!" << endl
						<< abort(FatalError);
				}

				auto polys0 = approxPlane(paraPlane);
				auto polys1 = approxPlane(makeOrignPlanes(modifyAlg->ModifiedPlanes()));

				auto tri0 = makeTriangulation(polys0);
				auto tri1 = makeTriangulation(polys1);

				myPlanes.push_back(std::move(tri0));
				myPlanes.push_back(std::move(tri1));
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - Nb. of singularity horizons: " << myPlanes.size() / 2 << endl;
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		// io functions [4/11/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [4/11/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setDegenCrit");

		// operators [4/11/2022 Amir]
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char *argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to detect the boundaries of singularity regions." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setDegenCrit(x); " << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshToolSingularityModifyPlaneViewer"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}