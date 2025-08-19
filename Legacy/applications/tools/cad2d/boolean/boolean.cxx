#include <Cad2d_Boolean.hxx>
#include <Cad2d_Plane.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <filesystem>

#include <fstream>
#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<Cad2d_Plane> plane_t;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static plane_t myPln0;
	static plane_t myPln1;

	//static std::vector<plane_t> myPlanes;
	static std::vector<plane_t> mySumPlanes;

	static double myTol = 1.0e-6;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadPlanes(const std::string& name)
	{
		if (verbose)
		{
			Info << endl
				<< " loading the planes..." << endl;
		}

		{//- timer scope
			size_t i = 0;

			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);
			ia >> myPln0;

			if (verbose)
			{
				Info << endl
					<< " the plane 0 is loaded, from: " << address << ", successfully in " << global_time_duration << " ms." << endl
					<< endl;
			}
		}

		{//- timer scope
			size_t i = 1;

			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);
			ia >> myPln1;

			if (verbose)
			{
				Info << endl
					<< " the plane 1 is loaded, from: " << address << ", successfully in " << global_time_duration << " ms." << endl
					<< endl;
			}
		}

		if (verbose)
		{
			Info << endl
				<< " all planes are loaded, successfully!" << endl
				<< endl;
		}

		loadTag = true;
	}

	void unionOp()
	{
		if (mySumPlanes.size())
		{
			mySumPlanes.clear();
		}

		auto pln = Cad2d_Boolean::Union(myPln0, myPln1, myTol);
		if (pln)
		{
			mySumPlanes.push_back(std::move(pln));
		}
		else
		{
			mySumPlanes.push_back(myPln0);
			mySumPlanes.push_back(myPln1);
		}
	}

	void subtractOp()
	{
		if (mySumPlanes.size())
		{
			mySumPlanes.clear();
		}

		auto plns = Cad2d_Boolean::Subtract(myPln0, myPln1, myTol);
		if (plns.empty())
		{
			mySumPlanes.push_back(myPln0);
		}
		else
		{
			mySumPlanes = plns;
		}
	}

	void intersectOp()
	{
		if (mySumPlanes.size())
		{
			mySumPlanes.clear();
		}

		auto plns = Cad2d_Boolean::Intersection(myPln0, myPln1, myTol);
		if (plns.empty())
		{
			// empty body
		}
		else
		{
			mySumPlanes = plns;
		}
	}

	void execute(const std::string& op)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no planes have been loaded!" << endl
				<< abort(FatalError);
		}

		if (op IS_EQUAL "union")
		{
			unionOp();
		}
		else if (op IS_EQUAL "subtract")
		{
			subtractOp();
		}
		else if (op IS_EQUAL "intersect")
		{
			intersectOp();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " unidentified command has been detected: " << op << endl
				<< " - valid commands are: union, subtract, intersect" << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << endl;
			Info << " the operator " << op << " is applied, successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " nb. of planes are going to be saved: " << mySumPlanes.size() << endl;
			Info << endl;
		}
		size_t i = 0;
		for (const auto& x : mySumPlanes)
		{
			std::string address = ".\\results\\" + std::to_string(i) + "\\" + name;
			//boost::filesystem::path dir(std::to_string(i));
			std::filesystem::create_directories("results/" + std::to_string(i));

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << x;

			if (verbose)
			{
				Info << " plane, " << i << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}
		if (verbose)
		{
			Info << endl;
			Info << " all planes have been saved, successfully!" << endl;
			Info << endl;
		}
	}

	void setTolerance(double tol)
	{
		myTol = tol;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadPlanes(name); }), "loadPlanes");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](unsigned short c)->void {verbose = c; }), "setVerbose");

		mod->add(chaiscript::fun([](double tol)-> void {setTolerance(tol); }), "setTolerance");

		mod->add(chaiscript::fun([](const std::string& op)-> void {execute(op); }), "execute");
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
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to apply the boolean operators to the planes." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadPlanes(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Global functions: " << endl << endl

				<< " - setTolerance(double)" << endl
				<< " - execute(operation);    - operation: union, intersect, and subtract" << endl

				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\booleanOp2d";
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