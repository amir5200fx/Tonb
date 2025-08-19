#include <AirfoilPx_NoseCurve_t1.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static auto myProfile = std::make_shared<profileLib::NoseCurve_t1>();

	static unsigned short verbose = 0;
	static auto exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setXo(double x)
	{
		myProfile->SetXo(x);
		if (verbose)
		{
			Info << endl
				<< " - the Xo is set to: " << x << endl;
		}
	}

	void setYo(double x)
	{
		myProfile->SetYo(x);
		if (verbose)
		{
			Info << endl
				<< " - the Yo is set to: " << x << endl;
		}
	}

	void setUpperMax(double x)
	{
		myProfile->SetUpperMax(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper max. is set to: " << x << endl;
		}
	}

	void setUpperMaxLoc(double x)
	{
		myProfile->SetUpperMaxLoc(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper max. loc. is set to: " << x << endl;
		}
	}

	void setUpperNoseTight(double x)
	{
		myProfile->SetUpperNoseTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper nose tight. is set to: " << x << endl;
		}
	}

	void setUpperMaxTight(double x)
	{
		myProfile->SetUpperMaxTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper max. tight. is set to: " << x << endl;
		}
	}

	void setLowerMax(double x)
	{
		myProfile->SetLowerMax(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower max. is set to: " << x << endl;
		}
	}

	void setLowerMaxLoc(double x)
	{
		myProfile->SetLowerMaxLoc(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower max. loc. is set to: " << x << endl;
		}
	}

	void setLowerNoseTight(double x)
	{
		myProfile->SetLowerNoseTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower nose tight. is set to: " << x << endl;
		}
	}

	void setLowerMaxTight(double x)
	{
		myProfile->SetLowerMaxTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower max. tight. is set to: " << x << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);

		auto edges = Pln_Tools::RetrieveEdges({ myProfile->Surface() });
		file::SaveTo(edges.at(0), name + Pln_Edge::extension, verbose);
	}

	void saveTo()
	{
		saveTo("");
	}

	void execute()
	{
		myProfile->Perform();

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


		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		
		mod->add(chaiscript::fun([](double x) -> void {setXo(x); }), "setXo");
		mod->add(chaiscript::fun([](double x) -> void {setYo(x); }), "setYo");

		mod->add(chaiscript::fun([](double x) -> void {setUpperMax(x); }), "setUpperMax");
		mod->add(chaiscript::fun([](double x) -> void {setUpperMaxLoc(x); }), "setUpperMaxLoc");
		mod->add(chaiscript::fun([](double x) -> void {setUpperNoseTight(x); }), "setUpperNoseTight");
		mod->add(chaiscript::fun([](double x) -> void {setUpperMaxTight(x); }), "setUpperMaxTight");

		mod->add(chaiscript::fun([](double x) -> void {setLowerMax(x); }), "setLowerMax");
		mod->add(chaiscript::fun([](double x) -> void {setLowerMaxLoc(x); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double x) -> void {setLowerNoseTight(x); }), "setLowerNoseTight");
		mod->add(chaiscript::fun([](double x) -> void {setLowerMaxTight(x); }), "setLowerMaxTight");

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
			Info << " This application is aimed to create a parametric airfoil surface." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - exportToPlt(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setXo(x)" << endl
				<< " - setYo(x)" << endl << endl

				<< " - setUpperMax(x)" << endl
				<< " - setUpperMaxLoc(x)" << endl
				<< " - setUpperNoseTight(x)" << endl
				<< " - setUpperMaxTight(x)" << endl << endl

				<< " - setLowerMax(x)" << endl
				<< " - setLowerMaxLoc(x)" << endl
				<< " - setLowerNoseTight(x)" << endl
				<< " - setLowerMaxTight(x)" << endl << endl

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

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbAirfoilPxNoseCurveT1"));

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