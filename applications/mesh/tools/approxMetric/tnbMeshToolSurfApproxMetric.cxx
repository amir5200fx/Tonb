#include <Cad_ApprxMetric.hxx>
#include <Cad_ApprxMetricCriterion.hxx>
#include <Cad_ApprxMetricCriterion_MinMax.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Cad_ApprxMetricIO.hxx>
#include <Cad_GeomSurface.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Cad_GModel.hxx>
#include <Cad_Shape.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo2d_SamplePoints.hxx>
//#include <Geo2d_SamplePoints_13Pts2ply.hxx>
#include <Geo2d_SamplePoints_4Pts.hxx>
#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Geo2d_SamplePoints_8Pts.hxx>
//#include <Geo2d_SamplePoints_8Pts2ply.hxx>
#include <Geo2d_SamplePoints_9Pts.hxx>
//#include <Geo2d_SamplePoints_9Pts2ply.hxx>
#include <Merge_PntInfo.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = Cad_Shape::extension;
	static const std::string saveExt = Cad_ApprxMetricIO::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;

	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static std::shared_ptr<Cad_Shape> myShape;
	static std::shared_ptr<Cad_ApprxMetricIO> myApprox;

	static auto myMinLev = Cad_ApprxMetricInfo::DEFAULT_MIN_LEVEL;
	static auto myMaxLev = Cad_ApprxMetricInfo::DEFAULT_MAX_LEVEL;
	static auto myUnBalance = Cad_ApprxMetricInfo::DEFAULT_UNBALANCING;

	static auto myRadius = Merge_PntInfo::DEFAULT_RADIUS;
	static auto myRes = Merge_PntInfo::DEFAULT_RESOLUTION;

	//static auto mySamples = Cad_ApprxMetricInfo::DEFAULT_SAMPLES;
	static auto mySampleType = Geo2d_SamplePoints::Type::five_points;

	static auto myTol = Cad_ApprxMetricCriterion::DEFAULT_TOLERANCE;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMinLev(const int n)
	{
		myMinLev = n;
		if (verbose)
		{
			Info << endl
				<< " - the Min. Lev is set to: " << myMinLev << endl;
		}
	}

	void setMaxLev(const int n)
	{
		myMaxLev = n;
		if (verbose)
		{
			Info << endl
				<< " - the Max. Lev is set to: " << myMaxLev << endl;
		}
	}

	void setUnBalance(const int n)
	{
		myUnBalance = n;
		if (verbose)
		{
			Info << endl
				<< " - the Unbalance is set to: " << myUnBalance << endl;
		}
	}

	void setRadius(const double x)
	{
		myRadius = x;
		if (verbose)
		{
			Info << endl
				<< " - the Radius is set to: " << x << endl;
		}
	}

	void setRes(const double x)
	{
		myRes = x;
		if (verbose)
		{
			Info << endl
				<< " - the Resolution is set to: " << x << endl;
		}
	}

	void setSample(const std::string& name)
	{
		auto selected = name;
		if (name IS_EQUAL "4pts")
		{
			mySampleType = Geo2d_SamplePoints::Type::four_points;
			selected = "4pts";
		}
		else if (name IS_EQUAL "5pts")
		{
			mySampleType = Geo2d_SamplePoints::Type::five_points;
			selected = "5pts";
		}
		else if (name IS_EQUAL "8pts")
		{
			mySampleType = Geo2d_SamplePoints::Type::eight_points;
			selected = "8pts";
		}
		else if (name IS_EQUAL "9pts")
		{
			mySampleType = Geo2d_SamplePoints::Type::nine_points;
			selected = "9pts";
		}
		/*else if (name IS_EQUAL "8pts2l")
		{
			mySampleType = Geo2d_SamplePoints::Type::eight_points_2layer;
			selected = "8pts2l";
		}*/
		/*else if (name IS_EQUAL "9pts2l")
		{
			mySampleType = Geo2d_SamplePoints::Type::nine_points_2layer;
			selected = "9pts2l";
		}*/
		/*else if (name IS_EQUAL "13pts2l")
		{
			mySampleType = Geo2d_SamplePoints::Type::thirteen_points_2layer;
			selected = "13pts2l";
		}*/
		if (verbose)
		{
			Info << endl
				<< " - the sample points is set to: " << selected << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + loadExt, verbose);
		if (NOT myShape)
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

		file::SaveTo(myApprox, name + saveExt, verbose);
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
			return ;
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

	auto createCriterion(const std::shared_ptr<Cad_MetricCalculator>& calc)
	{
		auto alg = std::make_shared<cadLib::ApprxMetricCriterion_MinMax>(myTol, calc);
		return std::move(alg);
	}

	auto createSamples()
	{
		std::shared_ptr<Geo2d_SamplePoints> samples;
		switch (mySampleType)
		{
		case tnbLib::Geo2d_SamplePoints::Type::four_points:
			samples = std::make_shared<Geo2d_SamplePoints_4Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::five_points:
			samples = std::make_shared<Geo2d_SamplePoints_5Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::eight_points:
			samples = std::make_shared<Geo2d_SamplePoints_8Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::nine_points:
			samples = std::make_shared<Geo2d_SamplePoints_9Pts>();
			break;
		/*case tnbLib::Geo2d_SamplePoints::Type::eight_points_2layer:
			samples = std::make_shared<Geo2d_SamplePoints_8Pts2ply>();
			break;*/
		/*case tnbLib::Geo2d_SamplePoints::Type::nine_points_2layer:
			samples = std::make_shared<Geo2d_SamplePoints_9Pts2ply>();
			break;*/
		/*case tnbLib::Geo2d_SamplePoints::Type::thirteen_points_2layer:
			samples = std::make_shared<Geo2d_SamplePoints_13Pts2ply>();
			break;*/
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of samples has been detected!" << endl
				<< abort(FatalError);
			break;
		}
		return std::move(samples);
	}

	auto retrieveGeometry(const std::shared_ptr<GModel_Surface>& surf)
	{
		auto geom = GModel_Tools::RetrieveGeometry(*surf);
		auto b = surf->ParaBoundingBox();
		auto t = std::make_pair(std::move(geom), std::move(b));
		return std::move(t);
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
		auto criterion = createCriterion(metricCalculator);
		auto samples = createSamples();

		auto apprxInfo = std::make_shared<Cad_ApprxMetricInfo>();
		apprxInfo->SetMinLevel(myMinLev);
		apprxInfo->SetMaxLevel(myMaxLev);
		apprxInfo->SetUnbalancing(myUnBalance);

		apprxInfo->MergeInfoRef().SetRadius(myRadius);
		apprxInfo->MergeInfoRef().SetResolution(myRes);

		apprxInfo->OverrideSamples(samples);
		apprxInfo->OverrideCriterion(criterion);

		auto surfaces = GModel_Tools::GetSurfaces(myShape->Shape());
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface is found!" << endl
				<< abort(FatalError);
		}

		auto ioObj = std::make_shared<Cad_ApprxMetricIO>();
		auto gModel = std::make_shared<Cad_GModel>(std::move(surfaces));
		ioObj->SetModel(myShape);
		auto& apprx = ioObj->ApproxRef();

		for (const auto& x : gModel->Surfaces())
		{
			if (verbose)
			{
				Info << " - Approximate the metrics of the surface nb. " << x->Index() << "..." << endl;
			}
			{
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				auto geom = GModel_Tools::RetrieveGeometry(*x);
				auto b = x->ParaBoundingBox();
				auto domain = std::make_shared<Entity2d_Box>(std::move(b));
				auto apprxMetricAlg = std::make_shared<Cad_ApprxMetric>(geom, domain);
				apprxMetricAlg->OverrideInfo(apprxInfo);
				apprxMetricAlg->Perform();

				auto tri = apprxMetricAlg->Triangulation();

				auto paired = std::make_pair(x->Index(), std::move(tri));
				auto insert = apprx.insert(std::move(paired));
				if (NOT insert.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data has been detected!" << endl
						<< abort(FatalError);
				}
			}
			if (verbose)
			{
				Info << " - the surface metric is approximated in " << global_time_duration << " ms." << endl;
			}
		}

		myApprox = std::move(ioObj);
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
		// io functions [4/8/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [4/8/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](int i)-> void {setMinLev(i); }), "setMinLev");
		mod->add(chaiscript::fun([](int i)-> void {setMaxLev(i); }), "setMaxLev");
		mod->add(chaiscript::fun([](int i)-> void {setUnBalance(i); }), "setUnbalancing");
		mod->add(chaiscript::fun([](double x)-> void {setRadius(x); }), "setRadius");
		mod->add(chaiscript::fun([](double x)-> void {setRes(x); }), "setResolution");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setSample(name); }), "setSampleType");

		// operators [4/8/2022 Amir]
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
			Info << " This application is aimed to approximate the surface metrics of a model." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setMinLev(n); " << endl
				<< " - setMaxLev(n);" << endl
				<< " - setUnbalancing(n);" << endl
				<< " - setRadius(double);" << endl
				<< " - setResolution(double);" << endl
				<< " - setSampleType(name);     - name: 4pts, 5pts, 8pts and 9pts" << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbMeshToolSurfApproxMetric"));

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