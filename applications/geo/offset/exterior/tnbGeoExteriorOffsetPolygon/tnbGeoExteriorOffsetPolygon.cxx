#include <Geo2d_OffsetPolygon_Exterior.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Entity2d_Polygon> myPolygon;
	static std::shared_ptr<Entity2d_Polygon> myOffsetPolygon;

	static double myMaxOffset = 0;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;
	static const std::string model_directory = "polygon";

	TNB_SET_VERBOSE_FUN;

	void setMaxoffset(double x)
	{
		myMaxOffset = x;
		if (verbose)
		{
			Info << endl
				<< " - the offset is set to: " << myMaxOffset << endl;
		}
	}

	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myPolygon, model_directory, myOffsetPolygon);

	void execute()
	{
		TNB_CHECK_LOAD_TAG;
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto alg = std::make_shared<Geo2d_OffsetPolygon_Exterior>(myPolygon, myMaxOffset);
			alg->Perform();
			if (NOT alg->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed." << endl
					<< abort(FatalError);
			}
			myOffsetPolygon = alg->Offset();
		}
		if (verbose)
		{
			Info << endl
				<< " - The application is successfully performed, in, " << global_time_duration << " ms." << endl;
		}
		TNB_EXECUTE_TAG;
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
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(myFileName + "_offset"); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setMaxoffset(x); }), "setMaxOffset");

		//- operators
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
			Info << " This application is aimed to offset a polygon." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setMaxOffset(x)" << endl << endl

				<< " ~ Operators: "<<endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbGeoExteriorOffsetPolygon"));

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