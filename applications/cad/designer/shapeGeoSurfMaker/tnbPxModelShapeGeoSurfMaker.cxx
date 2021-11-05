#include <Cad_GeomSurface.hxx>
#include <ShapePx_TopoCtrlNet.hxx>
#include <ShapePx_Tools.hxx>
#include <OpenCascade_Serialization.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <Geom_Surface.hxx>

namespace tnbLib
{

	static const std::string loadExt = ShapePx_TopoCtrlNet::extension + "list";
	static const std::string saveExt = Cad_GeomSurface::extension;

	typedef std::shared_ptr<ShapePx_TopoCtrlNet> net_t;

	static unsigned short verbose;
	static std::vector<net_t> myNets;

	static std::vector<std::shared_ptr<Cad_GeomSurface>> mySurf;
	static std::vector<unsigned int> mySurfDegs;

	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadNet(const std::string& name)
	{
		file::CheckExtension(name);

		myNets = file::LoadFile<std::vector<net_t>>(name + loadExt, verbose);
		if (myNets.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no control net has been found!" << endl
				<< abort(FatalError);
		}

		mySurfDegs.resize(myNets.size(), 3);

		loadTag = true;
	}

	void loadNet()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadNet(myFileName);
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

		size_t i = 0;
		for (const auto& x : mySurf)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address + saveExt);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << x;

			if (verbose)
			{
				Info << " surface " << i << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}
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

	const auto& selectNet(int i)
	{
		if (NOT INSIDE(i, 0, myNets.size() - 1))
		{
			FatalErrorIn(FunctionSIG)
				<< " the index is exceeded the bounds of the net list" << endl
				<< abort(FatalError);
		}
		return myNets[i];
	}

	void makeSurf(const net_t& s, int vdeg)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no control-net list has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		auto net = ShapePx_Tools::CreateControlNet(*s);
		auto t = ShapePx_Tools::Surface(*net, vdeg);
		auto surf = std::make_shared<Cad_GeomSurface>(std::move(t));
		mySurf.push_back(std::move(surf));
	}

	void setDeg(size_t i, unsigned int deg)
	{
		if (NOT INSIDE(i, 0, myNets.size() - 1))
		{
			FatalErrorIn(FunctionSIG)
				<< " the index is exceeded the bounds of the net list" << endl
				<< abort(FatalError);
		}
		mySurfDegs[i] = deg;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no control-net list has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " creating surfaces..."
				<< endl;
		}
		for (size_t i = 0; i < myNets.size(); i++)
		{
			makeSurf(myNets[i], mySurfDegs[i]);
			if (verbose)
			{
				Info << " - surface nb. " << i + 1 << " is created, successfully!" << endl;
			}
		}

		if (verbose)
		{
			Info << endl
				<< " The application is done: All surfaces are created, successfully!" << endl;
		}
		exeTag = true;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {loadNet(name); }), "loadNets");
		mod->add(chaiscript::fun([]()->void {loadNet(); }), "loadNets");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- methods
		mod->add(chaiscript::fun([](size_t i, unsigned int deg)-> void {setDeg(i, deg); }), "setDegree");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		//mod->add(chaiscript::fun([](int i)->const auto& {return selectNet(i); }), "selectNet");
		//mod->add(chaiscript::fun([](const net_t& n, int d)->void {makeSurf(n, d); }), "createSurface");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
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
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << "This application is aimed to create geometric surfaces from control-net vector." << endl;
			Info << endl
				<< " - the function list is: " << endl
				<< " - loadNets(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " - setDegree(net index, deg);   the default value for a surface is 3." << endl
				<< " - execute()" << endl
				<< endl
				<< " # settings: " << endl
				<< " - setVerbose(unsigned short);  levels: 0, 1" << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				std::string address = ".\\system\\tnbPxModelShapeGeoSurfMaker";
				fileName theFileName(address);

				chai.eval_file(theFileName);
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