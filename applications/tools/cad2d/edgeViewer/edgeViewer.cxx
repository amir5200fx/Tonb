#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <memory>

namespace tnbLib
{

	typedef std::shared_ptr<Pln_Edge> curve_t;

	static std::vector<curve_t> myCurves;
	static int verbose = 0;

	void loadCurves(const std::string& name)
	{
		fileName fn(name);
		std::fstream file;
		file.open(fn, std::ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		TNB_iARCH_FILE_TYPE ia(file);

		ia >> myCurves;
		if (NOT myCurves.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is null" << endl
				<< abort(FatalError);
		}
		for (const auto& x : myCurves)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null curve has been detected!" << endl
					<< abort(FatalError);
			}

			if (NOT x->Mesh())
			{
				FatalErrorIn(FunctionSIG)
					<< "the curve is not discretized!" << endl
					<< abort(FatalError);
			}
		}
		if (verbose)
		{
			Info << "the curve list has been loaded, successfully!" << endl;
			Info << " - nb. of curves: " << myCurves.size() << endl;
		}
	}

	void exportToPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		for (const auto& x : myCurves)
		{
			if (x)
			{
				if (x->Mesh())
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
		mod->add(chaiscript::fun([](int v)-> void {verbose = v; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCurves(name); }), "loadEdges");
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

			fileName myFileName("TnbEdgeViewer2d");

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