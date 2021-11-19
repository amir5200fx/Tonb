#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string saveExt = Pln_Edge::extension;

	static std::shared_ptr<Pln_Edge> myEdge;

	static unsigned short verbose(0);
	static bool exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void saveTo(const std::string& name)
	{
		if (NOT myEdge)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been created!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myEdge, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT myEdge)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been created!" << endl
				<< abort(FatalError);
		}

		if (NOT myEdge->Name().empty())
		{
			saveTo(myEdge->Name());
		}
		else
		{
			saveTo("curve");
		}
	}

	void makeEdge(const Pnt2d& p0, const Pnt2d& p1, const std::string& name)
	{
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		myEdge = Pln_Tools::MakeEdge(geom);

		myEdge->SetName(name);
	}

	void makeEdge(const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		myEdge = Pln_Tools::MakeEdge(geom);
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

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeEdge(p0, p1); }), "make");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const std::string& name)-> void {makeEdge(p0, p1, name); }), "make");
		mod->add(chaiscript::fun([](double x, double y)-> auto {return Pnt2d(x, y); }), "createPoint");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a line segment." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(double, double, double)" << endl

				<< " - make(Point0, Point1, name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				//std::string address = ".\\system\\tnbMeshCurve2d";
				fileName theFileName(file::GetSystemFile("tnbCad2dSegment"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}