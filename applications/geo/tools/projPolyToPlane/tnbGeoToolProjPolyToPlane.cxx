#include <Entity3d_Polygon.hxx>
#include <Entity2d_Polygon.hxx>
#include <Geo_Serialization.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom_Plane.hxx>
#include <gp_Pln.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity3d_Polygon> myPoly3d;
	static std::shared_ptr<gp_Pln> myPlane;

	static std::shared_ptr<Entity2d_Polygon> myPoly2d;

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;

	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadPlane()
	{
		checkFolder("plane");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\plane)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			if (myFile.is_open())
			{
				std::string address;
				std::getline(myFile, address);

				// change the current path [2/6/2023 Payvand]
				boost::filesystem::current_path(address);

				{
					auto name = file::GetSingleFile(boost::filesystem::current_path(), ".gpln").string();

					myPlane = file::LoadFile<std::shared_ptr<gp_Pln>>(name + ".gpln", verbose);
					if (NOT myPlane)
					{
						FatalErrorIn(FunctionSIG)
							<< " the plane is null." << endl
							<< abort(FatalError);
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl;
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".gpln").string();

			myPlane = file::LoadFile<std::shared_ptr<gp_Pln>>(name + ".gpln", verbose);
			if (NOT myPlane)
			{
				FatalErrorIn(FunctionSIG)
					<< " the plane is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadPoly3d()
	{
		checkFolder("polygon");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\polygon)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);

			std::string address;
			std::getline(myFile, address);

			// change the current path [2/6/2023 Payvand]
			boost::filesystem::current_path(address);

			{
				auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Polygon::extension).string();

				myPoly3d = file::LoadFile<std::shared_ptr<Entity3d_Polygon>>(name + Entity3d_Polygon::extension, verbose);
				if (NOT myPoly3d)
				{
					FatalErrorIn(FunctionSIG)
						<< " the mesh file is null!" << endl
						<< abort(FatalError);
				}
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Polygon::extension).string();

			myPoly3d = file::LoadFile<std::shared_ptr<Entity3d_Polygon>>(name + Entity3d_Polygon::extension, verbose);
			if (NOT myPoly3d)
			{
				FatalErrorIn(FunctionSIG)
					<< " the mesh file is null!" << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadPolygonFile(const std::string& name)
	{
		file::CheckExtension(name);

		myPoly3d = file::LoadFile<std::shared_ptr<Entity3d_Polygon>>(name + Entity3d_Polygon::extension, verbose);
		if (NOT myPoly3d)
		{
			FatalErrorIn(FunctionSIG)
				<< "the polygon is null." << endl
				<< abort(FatalError);
		}
	}

	void loadPlaneFile(const std::string& name)
	{
		file::CheckExtension(name);

		myPlane = file::LoadFile<std::shared_ptr<gp_Pln>>(name + ".gpln", verbose);
		if (NOT myPlane)
		{
			FatalErrorIn(FunctionSIG)
				<< "the plane is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("polygon"))
		{
			loadPoly3d();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity3d_Polygon::extension).string();
			loadPolygonFile(name);
		}
		
		if (boost::filesystem::is_directory("plane"))
		{
			loadPlane();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".gpln").string();
			loadPlaneFile(name);
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);
		file::SaveTo(myPoly2d, name + Entity2d_Polygon::extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		Handle(Geom_Plane) g = new Geom_Plane(*myPlane);
		std::vector<Pnt2d> ppts;
		GeomAPI_ProjectPointOnSurf alg;
		for (const auto& x3d : myPoly3d->Points())
		{
			alg.Init(x3d, g);
			if (alg.NbPoints())
			{
				Standard_Real u, v;
				alg.LowerDistanceParameters(u, v);
				Pnt2d p2(u, v);
				ppts.push_back(std::move(p2));
			}
			else
			{
				Info << " - WARNING! the projection algorithm is failed to calculate the parametric point." << endl;
			}
		}
		myPoly2d = std::make_shared<Entity2d_Polygon>(std::move(ppts), 0);
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

	void setFunctions(const module_t& mod)
	{
		// io functions [12/5/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		// settings [12/5/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/5/2021 Amir]
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
			Info << " This application is aimed to project a 3d-polygon to a plane." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbGeoToolProjPolyToPlane"));

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