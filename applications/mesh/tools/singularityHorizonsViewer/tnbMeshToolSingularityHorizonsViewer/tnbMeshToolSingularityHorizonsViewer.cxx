#include <Cad_gSingularity.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_SingularityHorizons.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_ApprxMetricIO.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_PolygonGraphEdge.hxx>
#include <Geo_Tools.hxx>
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
	static const auto saveExt = Entity3d_Triangulation::extension + "list";

	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static std::shared_ptr<Cad_ApprxMetricIO> myApproxMetrics;
	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myHorizons;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

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

		file::SaveTo(myHorizons, name + saveExt, verbose);
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
			return;
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
			auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geom, *metricApprox);
			auto criterion = Cad_ColorApprxMetric::CalcCriterion(maxDet);

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

			if (horizonAlg->HasHorizon())
			{
				const auto& horizons = horizonAlg->Horizons();
				Debug_Null_Pointer(horizons);

				for (const auto& pedge : horizons->Edges())
				{
					Debug_Null_Pointer(pedge.second);
					const auto& poly = pedge.second->Polygon();
					Debug_Null_Pointer(poly);

					auto tri2d = Geo_Tools::Triangulation(*Geo_Tools::RetrieveChain(*poly));
					auto tri = Cad_Tools::Triangulation(*geom, *tri2d);

					myHorizons.push_back(std::move(tri));
				}
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - Nb. of singularity horizons: " << myHorizons.size() << endl;
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
				fileName theFileName(file::GetSystemFile("tnbMeshToolSingularityHorizonsViewer"));

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