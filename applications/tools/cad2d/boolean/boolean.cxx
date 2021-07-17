#include <Cad2d_Boolean.hxx>
#include <Cad2d_Plane.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<Cad2d_Plane> plane_t;

	static unsigned short verbose = 0;
	static bool loaded = false;

	static std::vector<plane_t> myPlanes;
	static std::vector<plane_t> mySumPlanes;

	static double myTol = 1.0e-6;

	void loadPlanes(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the plane list..." << endl;
			Info << endl;
		}

		std::fstream file;
		file.open(name, std::ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found: " << name << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(file);

		ia >> myPlanes;

		if (myPlanes.size() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be two planes in the list" << endl
				<< abort(FatalError);
		}

		loaded = true;

		if (verbose)
		{
			Info << endl;
			Info << " the plane list has been loaded, successfully!" << endl;
			Info << endl;
		}
	}

	void unionOp()
	{
		if (mySumPlanes.size())
		{
			mySumPlanes.clear();
		}

		auto pln = Cad2d_Boolean::Union(myPlanes[0], myPlanes[1], myTol);
		if (pln)
		{
			mySumPlanes.push_back(std::move(pln));
		}
		else
		{
			mySumPlanes.push_back(myPlanes[0]);
			mySumPlanes.push_back(myPlanes[1]);
		}
	}

	void subtractOp()
	{
		if (mySumPlanes.size())
		{
			mySumPlanes.clear();
		}

		auto plns = Cad2d_Boolean::Subtract(myPlanes[0], myPlanes[1], myTol);
		if (plns.empty())
		{
			mySumPlanes.push_back(myPlanes[0]);
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

		auto plns = Cad2d_Boolean::Intersection(myPlanes[0], myPlanes[1], myTol);
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
		if (NOT loaded)
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been loaded!" << endl
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
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("boolean");

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