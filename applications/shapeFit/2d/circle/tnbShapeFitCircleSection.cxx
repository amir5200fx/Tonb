#include <PtdShapeFit2d_Circle.hxx>
#include <PtdShapeFit_Par.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Section> mySection;

	static double lowerXo = 0;
	static double upperXo = 0;
	static double lowerYo = 0;
	static double upperYo = 0;

	static double lowerRadius = 1.0;
	static double upperRadius = 2.0;

	static unsigned short verbose = 0;
	static auto exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setLowerXo(double x)
	{
		lowerXo = x;
		if (verbose)
		{
			Info << endl
				<< " - the lower xo is set to: " << lowerXo << endl;
		}
	}

	void setUpperXo(double x)
	{
		upperXo = x;
		if (verbose)
		{
			Info << endl
				<< " - the upper xo is set to: " << upperXo << endl;
		}
	}

	void setLowerYo(double x)
	{
		lowerYo = x;
		if (verbose)
		{
			Info << endl
				<< " - the lower yo is set to: " << lowerYo << endl;
		}
	}

	void setUpperYo(double x)
	{
		upperYo = x;
		if (verbose)
		{
			Info << endl
				<< " - the upper yo is set to: " << upperYo << endl;
		}
	}

	void setLowerRadius(double x)
	{
		lowerRadius = x;
		if (verbose)
		{
			Info << endl
				<< " the lower radius is set to: " << lowerRadius << endl;
		}
	}

	void setUpperRadius(double x)
	{
		upperRadius = x;
		if (verbose)
		{
			Info << endl
				<< " the upper radius is set to: " << upperRadius << endl;
		}
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

		file::SaveTo(mySection, name + PtdShapeFit_Section::extension, verbose);
	}

	void execute()
	{
		auto xo = PtdShapeFit2d_Circle::CreateXo(lowerXo, upperXo);
		auto yo = PtdShapeFit2d_Circle::CreateYo(lowerYo, upperYo);
		auto radius = PtdShapeFit2d_Circle::CreateRadius(lowerRadius, upperRadius);

		auto sect = std::make_shared<PtdShapeFit2d_Circle>();
		sect->SetXo(std::move(xo));
		sect->SetYo(std::move(yo));
		sect->SetRadius(std::move(radius));

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}

		mySection = std::move(sect);

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

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setLowerXo(x); }), "setLowerXo");
		mod->add(chaiscript::fun([](double x)-> void {setUpperXo(x); }), "setUpperXo");
		mod->add(chaiscript::fun([](double x)-> void {setLowerYo(x); }), "setLowerYo");
		mod->add(chaiscript::fun([](double x)-> void {setUpperYo(x); }), "setUpperYo");
		mod->add(chaiscript::fun([](double x)-> void {setLowerRadius(x); }), "setLowerRadius");
		mod->add(chaiscript::fun([](double x)-> void {setUpperRadius(x); }), "setUpperRadius");

		// operators [2/10/2023 Payvand]
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to create a circular parametric shape for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setLowerXo(x)" << endl
				<< " - setUpperXo(x)" << endl
				<< " - setLowerYo(x)" << endl
				<< " - setUpperYo(x)" << endl
				<< " - setLowerRadius(x)" << endl
				<< " - setUpperRadius(x)" << endl
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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitCircleSection"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}