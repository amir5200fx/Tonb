#include <PtdShapeFit_Section.hxx>
#include <PtdShapeFit2d_ScatterMap.hxx>
#include <PtdShapeFit_Par.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Galgo.hpp>

#include <Standard_Real.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Section> mySection;
	static std::shared_ptr<PtdShapeFit2d_ScatterMap> myScatters;
	static std::shared_ptr<galgo::GeneticAlgorithm<double>> myGA;

	static double myMutationRate = 0.15;
	static double myCrossOverRate = 0.5;
	static int myNbElites = 1;

	static int myPopSize = 50;
	static int myNbGens = 40;

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	class OptRunTime
	{

		/*Private Data*/

		std::shared_ptr<galgo::GeneticAlgorithm<double>> theGA_;

		std::shared_ptr<PtdShapeFit_Section> theSection_;
		std::shared_ptr<PtdShapeFit2d_ScatterMap> theScatters_;


	public:

		// constructor [2/10/2023 Payvand]

		OptRunTime();


		// Public functions and operators [2/10/2023 Payvand]

		void Perform();

	};

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMaxNbGens(int n)
	{
		myNbGens = n;
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of gens is set to: " << myNbGens << endl;
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
		myMutationRate = x;
		if (verbose)
		{
			Info << endl
				<< " - the mutation is set to: " << myMutationRate << endl;
		}
	}

	void setCrossOverRate(double x)
	{
		myCrossOverRate = x;
		if (verbose)
		{
			Info << endl
				<< " - the cross over rate is set to: " << myCrossOverRate << endl;
		}
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

	void loadSection()
	{
		checkFolder("section");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\section)");

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
					auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit_Section::extension).string();

					mySection = file::LoadFile<std::shared_ptr<PtdShapeFit_Section>>(name + PtdShapeFit_Section::extension, verbose);
					if (NOT mySection)
					{
						FatalErrorIn(FunctionSIG)
							<< " the section is null." << endl
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
			auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit_Section::extension).string();

			mySection = file::LoadFile<std::shared_ptr<PtdShapeFit_Section>>(name + PtdShapeFit_Section::extension, verbose);
			if (NOT mySection)
			{
				FatalErrorIn(FunctionSIG)
					<< " the section is null." << endl
					<< abort(FatalError);
			}
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadScatterMap()
	{
		checkFolder("scatters");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\scatters)");

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
					auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit2d_ScatterMap::extension).string();

					myScatters = file::LoadFile<std::shared_ptr<PtdShapeFit2d_ScatterMap>>(name + PtdShapeFit2d_ScatterMap::extension, verbose);
					if (NOT myScatters)
					{
						FatalErrorIn(FunctionSIG)
							<< " the scatter map is null." << endl
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
			auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit2d_ScatterMap::extension).string();

			myScatters = file::LoadFile<std::shared_ptr<PtdShapeFit2d_ScatterMap>>(name + PtdShapeFit2d_ScatterMap::extension, verbose);
			if (NOT myScatters)
			{
				FatalErrorIn(FunctionSIG)
					<< " the scatter map is null." << endl
					<< abort(FatalError);
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadSectionFile(const std::string& name)
	{
		file::CheckExtension(name);
		mySection = file::LoadFile<std::shared_ptr<PtdShapeFit_Section>>(name + PtdShapeFit_Section::extension, verbose);
		if (NOT mySection)
		{
			FatalErrorIn(FunctionSIG)
				<< " the section is null." << endl
				<< abort(FatalError);
		}
	}

	void loadScatterMapFile(const std::string& name)
	{
		file::CheckExtension(name);

		myScatters = file::LoadFile<std::shared_ptr<PtdShapeFit2d_ScatterMap>>(name + PtdShapeFit2d_ScatterMap::extension, verbose);
		if (NOT myScatters)
		{
			FatalErrorIn(FunctionSIG)
				<< " the scatter map is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (boost::filesystem::is_directory("section"))
		{
			loadSection();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit_Section::extension).string();
			loadSectionFile(name);
		}
		
		if (boost::filesystem::is_directory("scatters"))
		{
			loadScatterMap();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), PtdShapeFit2d_ScatterMap::extension).string();
			loadScatterMapFile(name);
		}

		loadTag = true;
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
		if (NOT loadTag)
		{
			Info << endl
				<< " no file has been loaded." << endl
				<< abort(FatalError);
		}

		OptRunTime ga;

		ga.Perform();

		
		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - the application is performed." << endl;
		}
	}
}

tnbLib::OptRunTime::OptRunTime()
{
	theGA_ = std::make_shared<galgo::GeneticAlgorithm<double>>(myPopSize, myNbGens, true);

	theSection_ = mySection;
	theScatters_ = myScatters;
}

void tnbLib::OptRunTime::Perform()
{
	auto costFun = [this](const std::vector<double>& xs) -> std::vector<double>
	{
		try
		{
			auto cost = theSection_->CalcError(xs, theScatters_);
			return { -cost };
		}
		catch (const Standard_Failure& x)
		{
			Info << x.GetMessageString() << endl;
			return { RealFirst() };
		}
		catch (...)
		{
			Info << " Unknown Error has been detected." << endl;
			return { RealFirst() };
		}
	};

	myGA = theGA_;

	/**/

	auto variables = mySection->RetrieveParList();

	int idx = 0;
	for (const auto& x : variables)
	{
		if (NOT x)
		{
			FatalErrorIn(FunctionSIG)
				<< "variable is null." << endl
				<< abort(FatalError);
		}
		const auto lower = x->LowerVal();
		const auto upper = x->UpperVal();
		//std::cout << x->Name() << ": " << lower << ", " << upper << std::endl;
		galgo::Parameter<double> par({ lower,upper });

		myGA->param.emplace_back(new galgo::Parameter<double>(par));
		myGA->lowerBound.push_back(lower);
		myGA->upperBound.push_back(upper);

		if (idx == 0)
		{
			myGA->idx.push_back(idx);
		}
		else
		{
			myGA->idx.push_back(myGA->idx.at(idx - 1) + par.size());
		}
		idx++;
	}

	//std::exit(1);
	myGA->Objective = costFun;
	myGA->genstep = 1;
	myGA->mutrate = myMutationRate;
	myGA->nbparam = variables.size();
	myGA->nbbit = variables.size() * 16;
	myGA->covrate = myCrossOverRate;

	const int nbElits = myNbElites;
	//myGA->elitpop = nbElits == 0 ? 1 : nbElits;

	myGA->run();

	const auto& bestResult = myGA->pop(0)->getParam();

	mySection->SetParameters(bestResult);

	const auto& bestParams = mySection->Pars();
	if (verbose)
	{
		Info << endl;
		for (const auto& x : bestParams->x)
		{
			Info << " - " << x.name << ": " << x.x << endl;
		}
	}

	if (verbose)
	{
		Info << endl
			<< " the application is performed, successfully!" << endl;
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
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setCrossOverRate(x); }), "setCrossOverRate");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbGens(n); }), "setNbGens");
		mod->add(chaiscript::fun([](double x)->void {setMutation(x); }), "setMutationRate");
		mod->add(chaiscript::fun([](int n)-> void {setPopSize(n); }), "setPopSize");

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
			Info << " This application is aimed to fit a parametric section to scatters." << endl
				<< " - files: section, scatters" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setCrossOverRate(x)" << endl
				<< " - setMutationRate(x)" << endl
				<< " - setNbGens(n)" << endl
				<< " - setPopSize(n)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbShapeFitSection"));
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