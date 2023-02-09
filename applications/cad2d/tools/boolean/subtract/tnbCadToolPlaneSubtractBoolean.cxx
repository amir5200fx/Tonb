#include <Cad2d_Boolean.hxx>
#include <Cad2d_Plane.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static auto loadExt = Cad2d_Plane::extension;
	static auto saveExt = Cad2d_Plane::extension + "list";

	static std::vector<std::shared_ptr<Cad2d_Plane>> myPlanes;
	static std::shared_ptr<Cad2d_Plane> myPlane;

	static std::shared_ptr<Cad2d_Plane> myPlane0;
	static std::shared_ptr<Cad2d_Plane> myPlane1;

	static bool verbose = false;
	static bool exeTag = false;
	static bool loadTag = false;

	static double myTol = 1.0E-6;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTol(double t)
	{
		myTol = t;
		if (verbose)
		{
			Info << endl
				<< " - the tol. is set to: " << myTol << endl;
		}
	}

	void loadPlane0(const std::string& name)
	{
		if (boost::filesystem::exists(name))
		{
			myPlane0 = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name, verbose);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such a file has been found." << endl
				<< " file: " << name << endl
				<< abort(FatalError);
		}
	}

	void loadPlane1(const std::string& name)
	{
		if (boost::filesystem::exists(name))
		{
			myPlane1 = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name, verbose);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such a file has been found." << endl
				<< " file: " << name << endl
				<< abort(FatalError);
		}
	}

	void loadFiles()
	{
		auto currentPath = boost::filesystem::current_path().string();
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto name = file::GetSingleFile(currentPath + std::to_string(i), loadExt).string();
				file::CheckExtension(name);

				myPlane0 = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name + loadExt, verbose);
			}

			i = 1;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto name = file::GetSingleFile(currentPath + std::to_string(i), loadExt).string();
				file::CheckExtension(name);

				myPlane1 = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name + loadExt, verbose);
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - All files have been loaded, successfully!" << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}
		if (myPlanes.size())
		{
			file::SaveTo(myPlanes, name + saveExt, verbose);
		}
		if (myPlane)
		{
			file::SaveTo(myPlane, name + Cad2d_Plane::extension, verbose);
		}
	}

	void execute(const std::string& name)
	{
		if (myPlane0 AND myPlane1)
		{
			loadTag = true;
		}

		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no file has been loaded!" << endl
				<< abort(FatalError);
		}

		auto plns = Cad2d_Boolean::Subtract(myPlane0, myPlane1, myTol);

		if (plns.empty())
		{
			myPlane = myPlane0;
		}
		else if (plns.size() IS_EQUAL 1)
		{
			myPlane = plns.at(0);
		}
		else
		{
			myPlanes = plns;
		}

		if (myPlane)
		{
			myPlane->SetName(name);
		}
		else
		{
			int i = 0;
			for (const auto& x : myPlanes)
			{
				x->SetName(name + std::to_string(++i));
			}
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

	void setGlobals(const module_t& mod)
	{
		// io functions [1/23/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadPlane0(name); }), "loadPlane0");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadPlane1(name); }), "loadPlane1");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [1/23/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short c)->void {verbose = c; }), "setVerbose");
		mod->add(chaiscript::fun([](double tol)-> void {setTol(tol); }), "setTolerance");

		// operators [1/23/2023 Payvand]
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
			Info << endl;
			Info << " This application is aimed to apply the subtract boolean to the planes." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl
				<< " - loadFiles()" << endl
				<< " - loadPlane0(file)" << endl
				<< " - loadPlane1(file)" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Operators: " << endl << endl
				<< " - execute(name)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setTolerance(double) "
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneSubtractBoolean"));

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