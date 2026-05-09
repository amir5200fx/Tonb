#include <Cad_Shape.hxx>
#include <Cad_Boolean.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad_Shape> myShape0;
	static std::shared_ptr<Cad_Shape> myShape1;

	static std::shared_ptr<Cad_Shape> myShape;

	static std::string myOp = "union";

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setOp(const std::string& name)
	{
		myOp = name;
		if (verbose)
		{
			Info << endl
				<< " - the Operator is set to: " << name << endl;
		}
	}

	auto getAllFilesNames(const boost::filesystem::path& p)
	{
		boost::filesystem::directory_iterator end_itr;

		std::vector<std::string> names;
		for (boost::filesystem::directory_iterator iter(p); iter != end_itr; iter++)
		{
			if (boost::filesystem::is_regular_file(iter->path()))
			{
				auto file = iter->path().filename().string();
				names.push_back(std::move(file));
			}
		}
		return std::move(names);
	}

	auto getSingleFile(const boost::filesystem::path& p)
	{
		auto files = getAllFilesNames(p);
		if (files.size())
		{
			return files[0];
		}
		return std::string();
	}

	void loadModels()
	{
		{//- loading the shape0
			boost::filesystem::path dir("0");
			if (NOT boost::filesystem::is_directory(dir))
			{
				FatalErrorIn(FunctionSIG)
					<< "no '0' directory has been found!" << endl
					<< abort(FatalError);
			}

			auto name = getSingleFile(dir);

			fileName fn(name);
			std::string address = ".\\0\\" + name;

			std::fstream file;

			file.open(address, std::ios::in);
			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to open the file: " << address << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ar(file);

			{//- timer scope
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				ar >> myShape0;
			}

			if (NOT myShape0)
			{
				FatalErrorIn(FunctionSIG)
					<< " the shape 0 is null" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << endl;
				Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
				Info << endl;
			}
		}

		{//- loading the shape1
			boost::filesystem::path dir("1");
			if (NOT boost::filesystem::is_directory(dir))
			{
				FatalErrorIn(FunctionSIG)
					<< "no '1' directory has been found!" << endl
					<< abort(FatalError);
			}

			auto name = getSingleFile(dir);

			fileName fn(name);
			std::string address = ".\\1\\" + name;

			std::fstream file;

			file.open(address, std::ios::in);
			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to open the file: " << address << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ar(file);

			{//- timer scope
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				ar >> myShape1;
			}

			if (NOT myShape1)
			{
				FatalErrorIn(FunctionSIG)
					<< " the shape 0 is null" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << endl;
				Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
				Info << endl;
			}
		}

		if (verbose)
		{
			Info << endl
				<< " All models are loaded, successfully!" << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		ar << myShape;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
				<< abort(FatalError);
		}

		if (myOp IS_EQUAL "union")
		{
			myShape = std::make_shared<Cad_Shape>(0, name, Cad_Boolean::Union(myShape0->Shape(), myShape1->Shape()));
		}
		else if (myOp IS_EQUAL "subtract")
		{
			myShape = std::make_shared<Cad_Shape>(0, name, Cad_Boolean::Subtract(myShape0->Shape(), myShape1->Shape()));
		}
		else if (myOp IS_EQUAL "intersect")
		{
			myShape = std::make_shared<Cad_Shape>(0, name, Cad_Boolean::Intersection(myShape0->Shape(), myShape1->Shape()));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of operation has been detected!" << endl
				<< " types: \"union\", \"intersect\", \"subtract\"" << endl
				<< abort(FatalError);
		}
		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("shape");
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
		mod->add(chaiscript::fun([]()-> void {loadModels(); }), "loadShapes");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");


		//- functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {setOp(name); }), "setOperation");
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
			Info << " This application is aimed to apply a boolean operation." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadShapes()" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl
				<< " - setOperation(string);        - operations: \"union\", \"subtract\", \"intersect\"" << endl << endl

				<< " # functions: " << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbBooleanShape";
			fileName myFileName(address);

			try
			{
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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
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