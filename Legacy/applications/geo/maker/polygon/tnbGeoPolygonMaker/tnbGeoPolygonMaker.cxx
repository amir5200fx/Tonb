#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::vector<Pnt2d> myPoints;
	static std::shared_ptr<Entity2d_Polygon> myPolygon;

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_EXETAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	auto createPoint(double x, double y)
	{
		return Pnt2d(x, y);
	}

	void setPoint(const Pnt2d& pt)
	{
		myPoints.push_back(pt);
	}

	void execute()
	{
		myPolygon = std::make_shared<Entity2d_Polygon>(myPoints, 0);
		TNB_EXECUTE_TAG;
		if (verbose)
		{
			Info << endl
				<< " - The application is successfully performed." << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		TNB_CHECK_EXE_TAG;
		file::CheckExtension(name);
		file::SaveTo(myPolygon, name + Entity2d_Polygon::extension, verbose);
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

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](double x, double y)-> auto{ return createPoint(x,y); }), "createPoint");
		mod->add(chaiscript::fun([](const Pnt2d& c) -> void {setPoint(c); }), "setPoint");
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
			Info << " This application is aimed to create a polygon." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl

				<< " ~ Operators: " << endl << endl

				<< " - execute()" << endl
				<< " - [Point] createPoint(x, y)" << endl
				<< " - setPoint(Point)" << endl

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
				fileName myFileName(file::GetSystemFile("tnbGeoPolygonMaker"));

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