#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_Tools.hxx>
#include <OpenCascade_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <Geom_Surface.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<ShapePx_CtrlNet> net_t;

	static unsigned short verbose;
	static std::vector<net_t> myNets;

	static std::vector<Handle(Geom_Surface)> mySurf;

	static bool loadTag = false;

	void loadNet(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "couldn't open the file: " << fn << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);
		ia >> myNets;

		if (verbose)
		{
			Info << endl;
			Info << " the control-net list has been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}

		loadTag = true;
	}

	const auto& selectNet(int i)
	{
		if (NOT INSIDE(i, 0, myNets.size()))
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

		auto t = ShapePx_Tools::Surface(*s, vdeg);
		mySurf.push_back(std::move(t));
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);
		oa << mySurf;

		if (verbose)
		{
			Info << endl;
			Info << " the surfaces are saved in: " << fn << ", successfully!" << endl;
			Info << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadNet(name); }), "loadNets");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](int i)->const auto& {return selectNet(i); }), "selectNet");
		mod->add(chaiscript::fun([](const net_t& n, int d)->void {makeSurf(n, d); }), "createSurface");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbShapeGeoSurfMaker");

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