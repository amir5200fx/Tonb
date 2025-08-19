#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Cad2d_Plane::extension;
	static std::string saveExt = Entity2d_Triangulation::extension + "list";

	static std::shared_ptr<Cad2d_Plane> myPln;
	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myTris;

	static bool verbose = false;
	static bool loadTag = false;

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

		myFileName = name;
		myPln = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name + loadExt, verbose);
		loadTag = true;

		std::map<int, std::shared_ptr<Entity2d_Triangulation>> trisMap;
		const auto& outer = myPln->OuterWire();
		if (outer)
		{
			for (const auto& x : outer->Edges())
			{
				if (x)
				{
					auto id = x->Index();
					auto poly = x->Mesh();
					if (poly)
					{
						auto chain = Geo_Tools::RetrieveChain(x->Sense() ? *poly : poly->Reversed());
						auto tri = Geo_Tools::Triangulation(*chain);
						auto iter = trisMap.find(id);
						if (iter NOT_EQUAL trisMap.end())
						{
							FatalErrorIn(FunctionSIG)
								<< "duplicate data has been detected." << endl
								<< abort(FatalError);
						}
						trisMap.insert({ id, tri });
						//myTris.push_back(std::move(tri));
					}
				}
			}
		}

		const auto& inners = myPln->InnerWires();
		if (inners)
		{
			for (const auto& inner : *inners)
			{
				for (const auto& x : inner->Edges())
				{
					if (x)
					{
						auto id = x->Index();
						auto poly = x->Mesh();
						if (poly)
						{
							auto chain = Geo_Tools::RetrieveChain(x->Sense() ? *poly : poly->Reversed());
							auto tri = Geo_Tools::Triangulation(*chain);
							auto iter = trisMap.find(id);
							if (iter NOT_EQUAL trisMap.end())
							{
								FatalErrorIn(FunctionSIG)
									<< "duplicate data has been detected." << endl
									<< abort(FatalError);
							}
							trisMap.insert({ id, tri });
							//myTris.push_back(std::move(tri));
						}
					}
				}
			}
		}
		std::vector<std::pair<int, std::shared_ptr<Entity2d_Triangulation>>> trisList;
		for (const auto& x : trisMap)
		{
			trisList.push_back(x);
		}
		std::sort
		(
			trisList.begin(),
			trisList.end(),
			[](
				const std::pair<int, std::shared_ptr<Entity2d_Triangulation>>& p0,
				const std::pair<int, std::shared_ptr<Entity2d_Triangulation>>& p1
				) {return p0.first < p1.first; }
		);
		for (const auto& x : trisList)
		{
			myTris.push_back(x.second);
		}
	}

	void loadFile()
	{
		myFileName = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		loadFile(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		file::SaveTo(myTris, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
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
		// io functions [2/13/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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
	FatalError.throwExceptions();

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
			Info << " This application is aimed to retrieve the meshes of a plane." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneViewer"));

				chai.eval_file(myFileName);
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
}