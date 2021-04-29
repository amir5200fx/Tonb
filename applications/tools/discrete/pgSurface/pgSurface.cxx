#include <Cad_GeomSurface.hxx>
#include <Cad_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <memory>
#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<Cad_GeomSurface> surface_t;

	static std::vector<surface_t> mySurfaces;
	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myTriangulations;

	static const unsigned int LOW_TESSELLATION = 15;
	static const unsigned int MEDIUM_TESSELLATION = 25;
	static const unsigned int HIGH_TESSELLATION = 40;

	static unsigned int uSpace = MEDIUM_TESSELLATION;
	static unsigned int vSpace = MEDIUM_TESSELLATION;

	static unsigned int custom_uSpace = MEDIUM_TESSELLATION;
	static unsigned int custom_vSpace = MEDIUM_TESSELLATION;

	static bool verbose = false;

	void setTessellation(const std::string& lev)
	{
		if (lev IS_EQUAL "low")
		{
			uSpace = LOW_TESSELLATION;
			vSpace = LOW_TESSELLATION;
		}
		else if (lev IS_EQUAL "medium")
		{
			uSpace = MEDIUM_TESSELLATION;
			vSpace = MEDIUM_TESSELLATION;
		}
		else if (lev IS_EQUAL "high")
		{
			uSpace = HIGH_TESSELLATION;
			vSpace = HIGH_TESSELLATION;
		}
		else if (lev IS_EQUAL "custom")
		{
			uSpace = custom_uSpace;
			vSpace = custom_vSpace;
		}

		if (verbose)
		{
			Info << endl;
			Info << " the tessellation level is set to: " << lev << endl;
			Info << endl;
		}
	}

	void setSpaceU(unsigned int nb)
	{
		custom_uSpace = nb;
	}

	void setSpaceV(unsigned int nb)
	{
		custom_vSpace = nb;
	}

	void loadSurfaces(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the surfaces..." << endl;
			Info << endl;
		}

		fileName fn(name);
		std::fstream file;
		file.open(fn, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		ia >> mySurfaces;
		if (NOT mySurfaces.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is null" << endl
				<< abort(FatalError);
		}
		for (const auto& x : mySurfaces)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null surface has been detected!" << endl
					<< abort(FatalError);
			}
		}

		if (verbose)
		{
			Info << endl;
			Info << " - " << mySurfaces.size() << " nb. of surfaces has been loaded, successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		for (const auto& x : mySurfaces)
		{
			auto tri = Cad_Tools::Triangulation(x->Geometry(), uSpace, vSpace);
			if (tri)
			{
				myTriangulations.push_back(std::move(tri));
			}
		}
	}

	void exportToPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);
		for (const auto& x : myTriangulations)
		{
			if (x)
			{
				x->ExportToPlt(f);
			}
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

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSurfaces(name); }), "loadSurfaces");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setTessellation(name); }), "setTessellation");
		mod->add(chaiscript::fun([](unsigned int n)-> void {setSpaceU(n); }), "setU");
		mod->add(chaiscript::fun([](unsigned int n)-> void {setSpaceV(n); }), "setV");

		mod->add(chaiscript::fun([](unsigned int i)-> void {verbose = i; }), "setVerbose");

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
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
	FatalError.throwExceptions();

	//Cad2d_RemoveNonManifold::verbose = 1;

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbPgSurfaceDiscretizer");

			try
			{
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