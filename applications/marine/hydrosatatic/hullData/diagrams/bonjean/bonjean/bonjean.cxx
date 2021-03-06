#include <HydStatic_SolutionData_Bonjean.hxx>
#include <HydStatic_Bonjean.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterLib.hxx>
#include <Geo_CosineDistb.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Bonjean> soluData_t;
	typedef std::shared_ptr<Marine_MultLevWaterDomain> domains_t;

	static unsigned short verbose(0);

	static size_t nbWaters = 20;
	static double offsetD = 0.005;

	soluData_t mySolutionData;

	void loadSolutionDate(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> mySolutionData;
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
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

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

	auto calcZs(const double z0, const double z1, const int n, const double d)
	{
		const auto c = (z1 - z0) / 2;
		const auto dt = M_PI / (double)n;
		const auto dz = c * ((double)1.0 - std::cos(dt));

		auto disZ = std::make_shared<Geo_CosineDistb>(n);

		disZ->SetLower(z0 + d * dz);
		disZ->SetUpper(z1 + d * dz);
		disZ->Perform();

		return std::move(disZ);
	}

	void execute()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " no solution data has been loaded!" << endl
				<< abort(FatalError);
		}
		if (nbWaters < 3)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid nb. of waters has been detected!" << endl
				<< abort(FatalError);
		}
		const auto& domain = mySolutionData->Domain();
		const auto& body = mySolutionData->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body is found!" << endl
				<< abort(FatalError);
		}
		auto b = Marine_BodyTools::BoundingBox(*body);

		auto Z = calcZs(b.P0().Z(), b.P1().Z(), nbWaters, offsetD);
		auto domains = Marine_WaterLib::MultiLevelsStillWaterDomain(*body, domain, *Z);

		auto bonj = std::make_shared<HydStatic_Bonjean>();
		bonj->LoadWaters(domains);
		bonj->Perform();

		mySolutionData->SetGraph(bonj->Graph());

		if (verbose)
		{
			Info << endl;
			Info << " Bonjean-Curves are calculated, successfully!" << endl;
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
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](int n)-> void {nbWaters = n; }), "setNbWaters");
		mod->add(chaiscript::fun([](double d)-> void {offsetD = d; }), "setOffsetZ");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionDate(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](unsigned short c)-> void {verbose = c; }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short c)-> void {HydStatic_Bonjean::verbose = c; }), "setBonjeanVerbose");

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

			fileName myFileName("hullDataBonjean");

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