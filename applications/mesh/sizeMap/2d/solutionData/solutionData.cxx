#include <Mesh2d_SolutionData.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Cad2d_Plane.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static unsigned short verbose = 0;

	typedef std::shared_ptr<Mesh_ReferenceValues> refValues_t;
	typedef std::shared_ptr<Cad2d_Plane> plane_t;

	static refValues_t myRef;
	static plane_t myPlane;

	static bool loadTag = false;

	typedef std::shared_ptr<Mesh2d_SolutionData> soluData_t;

	static soluData_t mySoluData;

	static const std::string refFolder = "reference";
	static const std::string geoFolder = "geometry";

	void load(const std::string& name)
	{
		if (verbose)
		{
			Info << "loading the geometry..." << endl;
			Info << endl;
		}

		if (boost::filesystem::is_directory(boost::filesystem::path(refFolder)))
		{
			std::string address = ".\\" + refFolder + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);

			ia >> myRef;
			if (NOT myRef)
			{
				FatalErrorIn(FunctionSIG)
					<< "no reference values have been found!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " Reference values are loaded from: " << address << ", successfully!" << endl;
				Info << endl;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the " << refFolder << " directory is not found!" << endl
				<< abort(FatalError);
		}

		if (boost::filesystem::is_directory(boost::filesystem::path(geoFolder)))
		{
			std::string address = ".\\" + geoFolder + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ia(file);

			ia >> myRef;
			if (NOT myRef)
			{
				FatalErrorIn(FunctionSIG)
					<< "no reference values have been found!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " the geometry is loaded from: " << address << ", successfully!" << endl;
				Info << endl;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the " << geoFolder << " directory is not found!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no data has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been created!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << mySoluData;

		if (verbose)
		{
			Info << " the solution data has saved in: " << fn << ", successfully!" << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no data has been loaded!" << endl
				<< abort(FatalError);
		}

		mySoluData = std::make_shared<Mesh2d_SolutionData>(myPlane, myRef);
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {load(name); }), "loadData");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
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

			setFuns(mod);

			chai.add(mod);

			fileName myFileName("sizeMap2dSoluData");

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
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Undefined command has been detected!" << endl
				<< abort(FatalError);
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}