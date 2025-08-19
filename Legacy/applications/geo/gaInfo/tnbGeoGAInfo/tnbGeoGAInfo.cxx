#include <NumAlg_GA.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<NumAlg_GA_Base::GA_Info> myInfo;

	static auto myMaxNbGens = 20;
	static auto myPopSize = 20;
	static auto myMutation = 0.05;
	static auto mySelection = 0.5;

	static unsigned short verbose = 0;
	static bool exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMaxNbGens(int n)
	{
		myMaxNbGens = n;
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of gens is set to: " << myMaxNbGens << endl;
		}
	}

	void setPopSize(int n)
	{
		myPopSize = n;
		if (verbose)
		{
			Info << endl
				<< " - the pop. size is set to: " << myPopSize << endl;
		}
	}

	void setMutation(double x)
	{
		myMutation = x;
		if (verbose)
		{
			Info << endl
				<< " - the mutation is set to: " << myMutation << endl;
		}
	}

	void setSelection(double x)
	{
		mySelection = x;
		if (verbose)
		{
			Info << endl
				<< " - the selection is set to: " << mySelection << endl;
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

		file::SaveTo(myInfo, name + NumAlg_GA_Base::GA_Info::extension, verbose);
	}

	void execute()
	{
		myInfo = std::make_shared<NumAlg_GA_Base::GA_Info>();
		myInfo->SetMaxNbGenerations(myMaxNbGens);
		myInfo->SetMutation(myMutation);
		myInfo->SetNbParameters(0);
		myInfo->SetPopSize(myPopSize);
		myInfo->SetSelection(mySelection);

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbGens(n); }), "setMaxNbGens");
		mod->add(chaiscript::fun([](int n)-> void {setPopSize(n); }), "setPopSize");
		mod->add(chaiscript::fun([](double x)-> void {setMutation(x); }), "setMutation");
		mod->add(chaiscript::fun([](double x)-> void {setSelection(x); }), "setSelection");

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
			Info << " This application is aimed to GA file info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setMaxNbGens(n)" << endl
				<< " - setPopSize(n)" << endl
				<< " - setMutation(x)" << endl
				<< " - setSelection(x)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbGeoGAInfo"));

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