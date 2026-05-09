#include <HydStatic_SolutionData.hxx>
#include <HydStatic_Shapes.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>
#include <map>

namespace tnbLib
{

	typedef std::shared_ptr<HydStatic_SolutionData> soluData_t;
	typedef std::shared_ptr<HydStatic_TankShape> tank_t;

	static unsigned short verbose = 0;

	static soluData_t mySolutionData;

	static std::map<std::string, tank_t> myTanks;

	void checkData()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadSoluData(const std::string& name)
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
				<< " the solution data is null" << endl
				<< abort(FatalError);
		}

		for (const auto& x : mySolutionData->Tanks())
		{
			const auto& tank = x.second;
			auto paired = std::make_pair(tank->Name(), tank);
			auto insert = myTanks.insert(std::move(paired));
			if (NOT insert.second)
			{
				// duplicate data!
			}
		}

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is loaded, successfully!" << endl;
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
		}
	}

	auto selectTank(unsigned int i)
	{
		checkData();
		auto t = mySolutionData->SelectTank(i);
		return std::move(t->second);
	}

	auto selectTank(const std::string& name)
	{
		checkData();
		auto iter = myTanks.find(name);
		if (iter IS_EQUAL myTanks.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the tank is not registered!" << endl
				<< " - name: " << name << endl
				<< abort(FatalError);
		}
		return std::move(iter->second);
	}

	void setFullness(const tank_t& t, double x)
	{
		t->SetFullnessPerc(x);
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSoluData(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](unsigned int i)-> auto {auto t = selectTank(i); return std::move(t); }), "selectTank");
		mod->add(chaiscript::fun([](const std::string& i)-> auto {auto t = selectTank(i); return std::move(t); }), "selectTank");
		mod->add(chaiscript::fun([](const tank_t& t, double x)-> void {setFullness(t, x); }), "setFullness");

		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
	}

	std::string getstring(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getstring(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
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
			setFunctions(mod);
			chai.add(mod);

			fileName myFileName("setTankFullness");

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