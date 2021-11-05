#include <HydStatic_SolutionData_GZ.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_CrsCurvesGraph.hxx>
#include <HydStatic_Spacing.hxx>
#include <HydStatic_CustomSpacing.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <HydStatic_HeelSpacing_Arbt.hxx>
#include <HydStatic_HeelSpacing_Asym.hxx>
#include <HydStatic_HeelSpacing_Stb.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_CmptLib2.hxx>
#include <Geo_Tools.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_GZ> soluData_t;
	typedef std::shared_ptr<HydStatic_HeelSpacing> spacing_t;


	static unsigned short verbose(0);

	static const unsigned int DEFAULT_NB_WATERS = 5;
	static const unsigned int DEFAULT_NB_HEELS = 5;
	static auto nbWaters = DEFAULT_NB_WATERS;
	static const std::vector<double> DEFAULT_HEELS = { 0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90 };


	static soluData_t mySolutionData;

	static const auto crossCurves = std::make_shared<HydStatic_CrossCurves>();
	static spacing_t myHeels;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadSolutionData(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> mySolutionData;
		}

		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolutionData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	const auto& getCrossCurves()
	{
		return crossCurves;
	}

	void setVolumeTol(double x)
	{
		crossCurves->SetVolumeCoeff(x);
	}

	void SetNbWaters(unsigned int n)
	{
		nbWaters = std::max(DEFAULT_NB_WATERS, n);
	}

	void setStbHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}

		auto heels = std::make_shared<hydStcLib::HeelSpacing_Stb>();
		heels->Perform(h);
		myHeels = std::move(heels);
	}

	void setStbHeels(unsigned int n)
	{
		n = std::max(n, DEFAULT_NB_HEELS);

		auto heels = std::make_shared<hydStcLib::HeelSpacing_Stb>();
		heels->Perform(n);
		myHeels = std::move(heels);
	}

	void setAsymmHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}
		auto heels = std::make_shared<hydStcLib::HeelSpacing_Asym>();
		heels->Perform(h);
		myHeels = std::move(heels);
	}

	void setAsymmHeels(unsigned int n)
	{
		n = std::max(n, DEFAULT_NB_HEELS);

		auto heels = std::make_shared<hydStcLib::HeelSpacing_Asym>();
		heels->Perform(n);
		myHeels = std::move(heels);
	}

	void setArbtHeels(const std::vector<double>& h)
	{
		if (h.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty" << endl
				<< abort(FatalError);
		}
		auto iter = h.begin();
		auto x0 = *iter;
		iter++;
		while (iter NOT_EQUAL h.end())
		{
			auto x1 = *iter;
			if (x1 <= x0)
			{
				FatalErrorIn(FunctionSIG)
					<< "heel list is not sorted!" << endl
					<< abort(FatalError);
			}
			x0 = x1;
			iter++;
		}
		auto spacing = std::make_shared<HydStatic_CustomSpacing>(std::move(h));
		auto heels = std::make_shared<hydStcLib::HeelSpacing_Arbt>(std::move(spacing));
		myHeels = std::move(heels);
	}

	void setHeels()
	{
		std::vector<double> heels;
		heels.reserve(DEFAULT_HEELS.size());
		for (auto h : DEFAULT_HEELS)
		{
			heels.push_back(Geo_Tools::DegToRadian(h));
		}
		setStbHeels(heels);
	}

	void setArbtHeels(double l, double u, unsigned int n)
	{
		if (u <= l)
		{
			std::swap(l, u);
		}

		auto h = std::make_shared<HydStatic_UniformSpacing>(n);
		h->SetLower(Geo_Tools::DegToRadian(l));
		h->SetUpper(Geo_Tools::DegToRadian(u));
		myHeels = std::make_shared<hydStcLib::HeelSpacing_Arbt>(std::move(h));
	}

	void execute()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been loaded!" << endl
				<< abort(FatalError);
		}
		if (NOT myHeels)
		{
			setHeels();
		}

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			const auto& domain = mySolutionData->Domain();
			if (NOT domain)
			{
				FatalErrorIn(FunctionSIG)
					<< " no domain has been found in the solution data!" << endl
					<< abort(FatalError);
			}

			auto alg = std::make_shared<HydStatic_CrossCurves>();
			alg->LoadDomain(domain);

			const auto& body = mySolutionData->Body();
			if (NOT body)
			{
				FatalErrorIn(FunctionSIG)
					<< " no body found!" << endl
					<< abort(FatalError);
			}

			alg->LoadBody(body);

			gp_Ax1 ax(body->CoordinateSystem().Location(), body->CoordinateSystem().XDirection());

			alg->SetAx(ax);
			alg->SetNbWaters(nbWaters - 1);
			alg->LoadHeels(myHeels);

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "algorithm is not performed!");

			mySolutionData->SetCrossCurves(alg->CrossCurves());
		}

		if (verbose)
		{
			Info << endl;
			Info << " hull cross-curves is calculated, successfully!" << endl;
			Info << " the curves are calculated in, " << global_time_duration << " ms" << endl;
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

	void setFunctions(const module_t& mod)
	{

		mod->add(chaiscript::fun([]()-> auto {return std::vector<double>(); }), "createList");
		mod->add(chaiscript::fun([](std::vector<double>& v, double x)-> void {v.push_back(x); }), "pushBack");

		mod->add(chaiscript::fun([](double x)-> void {setVolumeTol(x); }), "setVolumeTol");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::vector<double>& h)-> void {setStbHeels(h); }), "setStbHeels");
		mod->add(chaiscript::fun([](int n)-> void {setStbHeels(n); }), "setStbHeels");
		mod->add(chaiscript::fun([](const std::vector<double>& h)-> void {setAsymmHeels(h); }), "setAsymHeels");
		mod->add(chaiscript::fun([](int n)-> void {setAsymmHeels(n); }), "setAsymHeels");
		mod->add(chaiscript::fun([](double l, double u, unsigned int n)-> void {setArbtHeels(l, u, n); }), "setHeels");
		mod->add(chaiscript::fun([](const unsigned int n)->void {SetNbWaters(n); }), "setNbWaters");
		mod->add(chaiscript::fun([](unsigned short i)->void {HydStatic_CrossCurves::verbose = i; verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {Marine_CmptLib2::CrossCurve_Verbose = i; }), "setCrossCurvesVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {Marine_CmptLib2::LeverArm_Verbose2 = i; }), "setLeverArmVerbose");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionData(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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

#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
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
			Info << " This application is aimed to calculate the Cross-Curves of hull." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadSoluData(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setNbWaters(int)" << endl
				<< " - setHeels(double lower, double upper, int n)" << endl
				<< " - setAsymHeels(int)" << endl
				<< " - setStbHeels(int)" << endl << endl

				<< " # Global functions: " << endl << endl

				<< " - execute()" << endl
				<< " - setVerbose(int)" << endl
				<< " - setCrossCurvesVerbose(int)" << endl
				<< " - setLeverArmVerbose(int)" << endl
				<< " - setVolumeTol(double)" << endl
				<< " - [double list] createList()" << endl
				<< " - (double List).pushBack(double)" << endl

				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbHydstcCrossCurves";
			fileName myFileName(address);

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