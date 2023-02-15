#include <GeoIntsct3d_PlnTris.hxx>
#include <Geo3d_KnitChain.hxx>
#include <Geo3d_PolygonGraph.hxx>
#include <Geo3d_SegmentGraphEdge.hxx>
#include <Geo3d_PolygonSegmentGraphEdge.hxx>
#include <Merge_StaticData.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static const std::string extension = GeoIntsct3d_PlnTris::intsctEntity::extension;

	static std::vector<std::shared_ptr<GeoIntsct3d_PlnTris::intsctEntity>> myEntities;

	static double myTol = 1.0E-6;
	//static std::vector<std::shared_ptr<Entity3d_Chain>> unMergedList;
	static std::vector<std::shared_ptr<Entity3d_Polygon>> myPolygs;

	static std::string myFileName;

	void setTol(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tol. is set to: " << myTol << endl;
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myEntities = file::LoadFile<std::vector<std::shared_ptr<GeoIntsct3d_PlnTris::intsctEntity>>>(name + extension, verbose);
		if (NOT myEntities.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the entity list is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		auto current = fs::current_path().string();
		std::string address = current + "\\results";
		fs::path dir(address);
		if (NOT fs::is_directory(dir))
		{
			fs::create_directory(dir);
		}
		else
		{
			file::RemoveDirectory(dir);
			fs::create_directory(dir);
		}

		fs::current_path(dir);

		size_t i = 0;
		for (const auto& x : myPolygs)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + Entity3d_Polygon::extension, verbose);

			fs::current_path(dir);

			++i;
		}

		fs::current_path(current);
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

	auto retrieveChains()
	{
		std::vector<std::shared_ptr<Entity3d_Chain>> chains;
		chains.reserve(myEntities.size());
		for (const auto& x : myEntities)
		{
			if (auto ent = std::dynamic_pointer_cast<GeoIntsct3d_PlnTris::segIntsct>(x))
			{
				auto chain = std::make_shared<Entity3d_Chain>();
				chain->Points() = ent->RetrievePoints();
				connectivity::dual I;
				I.Value(0) = 1;
				I.Value(1) = 2;
				std::vector<connectivity::dual> indices = { std::move(I) };
				chain->Connectivity() = std::move(indices);

				chains.push_back(std::move(chain));
			}
		}
		return std::move(chains);
	}

	void execute()
	{
		auto unMergedList = retrieveChains();

		std::shared_ptr<Entity3d_Chain> merged;
		{// merging the chain [2/7/2023 Payvand]
			Merge_StaticData<Entity3d_Chain> merge;
			merge.InfoAlg().SetRadius(myTol);
			merge.Import(unMergedList);
			merge.SetRemoveDegeneracy();

			merge.Perform();

			merged = merge.Merged();
		}

		unMergedList.clear();

		std::shared_ptr<Geo3d_PolygonGraph> graph;
		{
			auto knit = std::make_shared<Geo3d_KnitChain>();

			knit->Import(*merged);
			merged.reset();

			knit->Perform();

			graph = knit->Graph();
		}
		for (const auto& x : graph->Edges())
		{
			const auto& e = x.second;
			myPolygs.push_back(e->Polygon());
		}

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");

		// operators [12/21/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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

int main(int argc, char* argv[])
{
	//FatalError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to retrieve the polygons from the entities of the intersection of plane and mesh." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl
				<< " - setTolerance(x)" << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshToolPlnIntsctPolygons"));

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}