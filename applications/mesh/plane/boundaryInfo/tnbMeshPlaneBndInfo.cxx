#include <Aft2d_SolutionData.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_BoundaryOfPlane_Info::extension;

	static unsigned short verbose = 0;
	static bool exeTag = false;

	static auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	static auto myInfo = std::make_shared<Aft2d_BoundaryOfPlane_Info>();
	static double myTol = 1.0E-6;
	static bool overrideInfo = false;

	class IntegInfoRunTime
	{
		/*Private Data*/

	public:

		IntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

static const tnbLib::IntegInfoRunTime myIntegInfoRunTimeObj;

void tnbLib::IntegInfoRunTime::SetInfo()
{
	myIntegInfo->SetMaxNbIterations(50);
	myIntegInfo->SetNbInitIterations(4);
	myIntegInfo->SetTolerance(1.0E-4);
}

namespace tnbLib
{
	bool isNumber(const std::string s)
	{
		if (s.size() IS_EQUAL 0) return false;
		for (int i = 0; i < s.size(); i++)
		{
			if ((s[i] >= '0' && s[i] <= '9') IS_EQUAL false)
			{
				return false;
			}
		}
		return true;
	}

	void loadSubCurveInfos()
	{
		const auto current = boost::filesystem::current_path();
		for (boost::filesystem::directory_iterator iter(current); iter != boost::filesystem::directory_iterator(); iter++)
		{
			auto fname = iter->path().string();
			if (isNumber(fname))
			{
				auto curveNb = std::stoi(fname);

				// Change the current path [12/2/2021 Amir]
				boost::filesystem::current_path(current.string() + R"(\)" + fname);

				try
				{
					auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();
					auto curveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
					if (NOT curveInfo)
					{
						FatalErrorIn(FunctionSIG)
							<< "the info curve is null!" << endl
							<< abort(FatalError);
					}

					auto paired = std::make_pair(curveNb, std::move(curveInfo));
					myInfo->Curve().insert(std::move(paired));

					if (verbose)
					{
						Info << " - the curve mesh info, " << curveNb << ", has been loaded, successfully!" << endl;
					}
				}
				catch (const error&)
				{
					Info << " Couldn't find the curve info file!" << endl;
				}
			}
		}

		//- change back the current path
		boost::filesystem::current_path(current);
	}

	void loadGlobal()
	{
		const auto current = boost::filesystem::current_path();
		if (NOT boost::filesystem::is_directory("global"))
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'global' directory has been found!" << endl
				<< abort(FatalError);
		}

		//- change the current path
		boost::filesystem::current_path(current.string() + R"(\global)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();

		auto globalInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
		if (NOT globalInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global mesh curve info file is null!" << endl
				<< abort(FatalError);
		}

		myInfo->OverrideGlobalCurve(globalInfo);

		//- change back the current path
		boost::filesystem::current_path(current);

		if (verbose)
		{
			Info << " the global mesh curve info file is loaded, successfully!" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myInfo, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo("bndInfo");
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << " - the merging tolerance is set to: " << myTol << endl;
		}
	}

	void setOverrideInfo(bool c)
	{
		overrideInfo = c;
		if (verbose)
		{
			Info << " - the override info condition is set to: " << (overrideInfo ? "TRUE" : "FALSE") << endl;
		}
	}

	void setMaxNbIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << " - the max. nb. of iterations is set to: " << n << endl;
		}
	}

	void setNbInitIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetNbInitIterations(n);
		if (verbose)
		{
			Info << " - the initial nb. of iterations is set to: " << n << endl;
		}
	}

	void setTolerance(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)
	{
		info->SetTolerance(x);
		if (verbose)
		{
			Info << " - the tolerance is set to: " << x << endl;
		}
	}

	void execute()
	{
		loadGlobal();

		loadSubCurveInfos();

		myInfo->OverrideGlobalMetricPrcsr(myIntegInfo);
		myInfo->SetMergeTolerance(myTol);
		myInfo->SetOverrideInfo(overrideInfo);

		exeTag = true;

		if (verbose)
		{
			Info << " the application is performed, successfully!" << endl;
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

	void setFunctions(const module_t& mod)
	{

		// io functions [12/2/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/2/2021 Amir]
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setMaxNbIterations(info, n); }), "setMaxNbIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setNbInitIterations(info, n); }), "setNbInitIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)->void {setTolerance(x); }), "setMergingTol");
		mod->add(chaiscript::fun([](bool c)-> void {setOverrideInfo(c); }), "setOverrideInfo");

		// Operators [12/2/2021 Amir]

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([]()-> const auto& {return myIntegInfo; }), "getMetricInfo");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a boundary plane info." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - [MetricInfo].setMaxNbIterations(n)" << endl
				<< " - [MetricInfo].setNbInitIterations(n)" << endl
				<< " - [MetricInfo].setTolerance(double)" << endl << endl

				<< " - setMergingTol(double)" << endl
				<< " - setOverrideInfo(bool)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [MetricInfo] getMetricInfo()" << endl
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


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshPlaneBndInfo"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}