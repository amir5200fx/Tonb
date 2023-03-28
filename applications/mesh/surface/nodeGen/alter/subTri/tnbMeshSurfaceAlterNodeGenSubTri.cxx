#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>
#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <NumAlg_NelderMeadInfo.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Aft_SizeCorr_IterativeInfo> mySizeCorrInfo;
	static std::shared_ptr<NumAlg_NelderMeadInfo> myNelderInfo;

	static std::shared_ptr<Aft2d_AltrOptNodeSurface> myAlg;

	static unsigned int myMaxLevs = Aft2d_AltrOptNodeSurface_SubTri::DEFAULT_MAX_LEV;

	static const std::string SIZE_CORR_INFO_DIRECTORY = "sizeCorr";
	static const std::string NELDER_MEAD_DIRECTORY = "nelderMead";

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setMaxLevs(int n)
	{
		myMaxLevs = (unsigned int)n;
		if (verbose)
		{
			Info << endl
				<< "- max. no. of levels is set to: " << myMaxLevs << endl;
		}
	}

	void loadSizeCorrInfo()
	{
		mySizeCorrInfo = 
			file::LoadSingleFile<std::shared_ptr<Aft_SizeCorr_IterativeInfo>>
			(
				SIZE_CORR_INFO_DIRECTORY, 
				Aft_SizeCorr_IterativeInfo::extension,
				verbose);
		if (NOT mySizeCorrInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< "the size correction info. file is null." << endl
				<< abort(FatalError);
		}
	}

	void loadNelderMeadInfo()
	{
		myNelderInfo = 
			file::LoadSingleFile<std::shared_ptr<NumAlg_NelderMeadInfo>>
			(
				NELDER_MEAD_DIRECTORY, 
				NumAlg_NelderMeadInfo::extension, verbose
				);
		if (NOT myNelderInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< "the Nelder-Mead info. file is null." << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		if (file::IsDirectory(SIZE_CORR_INFO_DIRECTORY))
		{
			loadSizeCorrInfo();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Aft_SizeCorr_IterativeInfo::extension).string();
			file::CheckExtension(name);
			mySizeCorrInfo = file::LoadFile<std::shared_ptr<Aft_SizeCorr_IterativeInfo>>
				(name + Aft_SizeCorr_IterativeInfo::extension, verbose);
			if (NOT mySizeCorrInfo)
			{
				FatalErrorIn(FunctionSIG)
					<< "the size correction info. file is null." << endl
					<< abort(FatalError);
			}
		}
		if (file::IsDirectory(NELDER_MEAD_DIRECTORY))
		{
			loadNelderMeadInfo();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), NumAlg_NelderMeadInfo::extension).string();
			file::CheckExtension(name);
			myNelderInfo = file::LoadFile<std::shared_ptr<NumAlg_NelderMeadInfo>>(name + NumAlg_NelderMeadInfo::extension, verbose);
			if (NOT myNelderInfo)
			{
				FatalErrorIn(FunctionSIG)
					<< "the Nelder-Mead info. file is null." << endl
					<< abort(FatalError);
			}
		}
		loadTag = true;
	}

	void saveTo(const std::string name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);

		file::SaveTo(myAlg, name + Aft2d_AltrOptNodeSurface::extension, verbose);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			Info << endl
				<< " no file has been loaded." << endl
				<< abort(FatalError);
		}

		auto alg = std::make_shared<Aft2d_AltrOptNodeSurface_SubTri>(mySizeCorrInfo, myNelderInfo);
		alg->SetMaxLev(myMaxLevs);

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		// settings [3/19/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](int n)->void {setMaxLevs(n); }), "setMaxNbLevs");

		// operators [3/19/2023 Payvand]
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
			Info << " This application is aimed to create alternative optimum node generator called SubTri." << endl
				<< " - directories: sizeCorr (SizeCorr_IterativeInfo), nelderMead (info)" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setMaxNbLevs(n)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshSurfaceAlterNodeGenSubTri"));
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