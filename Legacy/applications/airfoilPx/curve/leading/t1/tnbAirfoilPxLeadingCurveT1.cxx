#include <AirfoilPx_LeadingCurve_t1.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static auto myProfile = std::make_shared<profileLib::LeadingCurve_t1>();

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

	void setUpperTight(double x)
	{
		myProfile->SetUpperTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper tight. is set to: " << x << endl;
		}
	}

	void setUpperWeight0(double x)
	{
		myProfile->SetUpperWeight0(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight0 is set to: " << x << endl;
		}
	}

	void setUpperWeight1(double x)
	{
		myProfile->SetUpperWeight1(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight1 is set to: " << x << endl;
		}
	}

	void setUpperWeight2(double x)
	{
		myProfile->SetUpperWeight2(x);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight2 is set to: " << x << endl;
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

	void setLowerTight(double x)
	{
		myProfile->SetLowerTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower max. tight. is set to: " << x << endl;
		}
	}

	void setLowerWeight0(double x)
	{
		myProfile->SetLowerWeight0(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight0 is set to: " << x << endl;
		}
	}

	void setLowerWeight1(double x)
	{
		myProfile->SetLowerWeight1(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight1 is set to: " << x << endl;
		}
	}

	void setLowerWeight2(double x)
	{
		myProfile->SetLowerWeight2(x);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight2 is set to: " << x << endl;
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
		mod->add(chaiscript::fun([](double x) -> void {setUpperTight(x); }), "setUpperTight");
		mod->add(chaiscript::fun([](double x) -> void {setUpperWeight0(x); }), "setUpperWeight0");
		mod->add(chaiscript::fun([](double x) -> void {setUpperWeight1(x); }), "setUpperWeight1");
		mod->add(chaiscript::fun([](double x) -> void {setUpperWeight2(x); }), "setUpperWeight2");

		mod->add(chaiscript::fun([](double x) -> void {setLowerMax(x); }), "setLowerMax");
		mod->add(chaiscript::fun([](double x) -> void {setLowerMaxLoc(x); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double x) -> void {setLowerTight(x); }), "setLowerTight");
		mod->add(chaiscript::fun([](double x) -> void {setLowerWeight0(x); }), "setLowerWeight0");
		mod->add(chaiscript::fun([](double x) -> void {setLowerWeight1(x); }), "setLowerWeight1");
		mod->add(chaiscript::fun([](double x) -> void {setLowerWeight2(x); }), "setLowerWeight2");

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
				<< " - setUpperTight(x)" << endl
				<< " - setUpperWeight0(x)" << endl
				<< " - setUpperWeight1(x)" << endl
				<< " - setUpperWeight2(x)" << endl << endl

				<< " - setLowerMax(x)" << endl
				<< " - setLowerMaxLoc(x)" << endl
				<< " - setLowerTight(x)" << endl 
				<< " - setLowerWeight0(x)" << endl
				<< " - setLowerWeight1(x)" << endl
				<< " - setLowerWeight2(x)" << endl << endl

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