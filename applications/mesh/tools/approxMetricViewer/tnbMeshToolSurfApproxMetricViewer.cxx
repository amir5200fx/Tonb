#include <MeshBase_Tools.hxx>
#include <Cad_ApprxMetricIO.hxx>
#include <Cad_GModel.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <Geo_Tools.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Entity3d_MeshValue.hxx>
#include <Entity2d_MetricMeshValue.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>
#include <Geom_Surface.hxx>

namespace tnbLib
{
	static const std::string loadExt = Cad_ApprxMetricIO::extension;
	static const std::string saveExt = Entity3d_MeshValue::extension + "list";

	static std::shared_ptr<Cad_ApprxMetricIO> myIO;
	static std::vector<std::shared_ptr<Entity3d_MeshValue>> myApproxs;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myIO = file::LoadFile<std::shared_ptr<Cad_ApprxMetricIO>>(name + loadExt, verbose);
		if (NOT myIO)
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

		file::SaveTo(myApproxs, name + saveExt, verbose);
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

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		loadSizeFun();

		const auto& model = myIO->Model();
		const auto& approxMap = myIO->Approx();
		auto surfaces = GModel_Tools::GetSurfaces(model->Shape());
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface is found!" << endl
				<< abort(FatalError);
		}

		myApproxs.reserve(surfaces.size());
		for (const auto& x : surfaces)
		{
			auto iter = approxMap.find(x->Index());
			if (iter IS_EQUAL approxMap.end())
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
			std::shared_ptr<Entity2d_MetricMeshValue> metrics;
			if (mySizeFun)
			{
				metrics = Cad_Tools::CalcMetrics(geom, *metricApprox, &calcSize);
			}
			else
			{
				metrics = Cad_Tools::CalcMetrics(geom, *metricApprox);
			}
			//auto metrics = Cad_Tools::CalcMetrics(geom, *metricApprox);
			auto poly = Cad_Tools::RetrieveTriangulation(x->Face());
			if (NOT poly)
			{
				FatalErrorIn(FunctionSIG)
					<< "the surface is not discretized!" << endl
					<< abort(FatalError);
			}
			auto tri = Cad_Tools::ParaTriangulation(*poly);
			auto tri3d = Cad_Tools::Triangulation(*geom, *tri);

			auto b = Entity2d_Box::BoundingBoxOf(tri->Points());
			b.Expand(-b.Diameter()*1.0E-6);
			auto shrinkedPts = Geo_Tools::DistributeInDomain(tri->Points(), b);
			auto hs = MeshBase_Tools::CalcDeterminants(shrinkedPts, *metrics);

			//auto meshV = MeshBase_Tools::CalcDeterminants(tri, *metrics);
			//auto& values = meshV->ValuesRef();

			auto meshV3d = std::make_shared<Entity3d_MeshValue>();
			
			meshV3d->SetMesh(std::move(tri3d));
			//meshV3d->SetValues(std::move(values));
			meshV3d->SetValues(std::move(hs));

			myApproxs.push_back(std::move(meshV3d));
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
		// io functions [4/8/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [4/8/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

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

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbMeshToolSurfApproxMetricViewer"));

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