#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static std::shared_ptr<Pln_Edge> myBaseCurve;
	static std::shared_ptr<Pln_Edge> myCurve;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;
	static const auto model_directory = "curve";

	TNB_DEFINE_GLOBAL_PATH;

	TNB_SET_VERBOSE_FUN;

	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myBaseCurve, model_directory, myCurve);

	void execute(const std::string& name)
	{
		TNB_CHECK_LOAD_TAG;
		const auto& curve = myBaseCurve->Curve();
		Pnt2d p0, p1;
		if (myBaseCurve->Sense())
		{
			p0 = curve->LastCoord();
			p1 = curve->FirstCoord();
		}
		else
		{
			p0 = curve->FirstCoord();
			p1 = curve->LastCoord();
		}
		if (p0.Distance(p1) <= gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is already closed." << endl
				<< abort(FatalError);
		}
		auto seg_curve = std::make_shared<Pln_Curve>
			(0, name, Pln_CurveTools::MakeSegment(p0, p1));
		myCurve = Pln_Tools::MakeEdge(seg_curve);
		TNB_PERFORMED_TAG;
	}

	void execute()
	{
		execute("mySegment");
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
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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

int main(int argc, char* argv[])
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
			Info << " This application is aimed to create a segment to close a curve." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl

				<< " # functions: " << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneCloseCurve"));

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