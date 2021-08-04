#include <Global_Timer.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Shape.hxx>
#include <IGESControl_Reader.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Cad_Shape> shape_t;

	static unsigned short verbose(0);
	static bool loadTag = false;

	static shape_t myShape;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		
		{// timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			IGESControl_Reader Reader;
			Reader.ReadFile(name.c_str());

			Handle(TColStd_HSequenceOfTransient) myList = Reader.GiveList("iges-faces");
			Reader.TransferList(myList);

			myShape = std::make_shared<Cad_Shape>(0, name, Reader.OneShape());
		}

		if (verbose)
		{
			Info << "IGES File Imported Successfully in "
				<< global_time_duration << " seconds.";
		}
		if (verbose)
		{
			Info << endl;
			Info << " the shape is loaded, from: " << name << ", successfully!" << endl;
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded!" << endl
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
			Info << " the shape is saved in: " << fn << ", successfully!" << endl;
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
		//- io functions

		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
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
			Info << " Function list:" << endl;
			Info << " - loadModel(string)" << endl;
			Info << " - saveTo(string)" << endl;
			Info << " - setVerbose(unsigned int)" << endl;
			Info << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("igesReader");

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