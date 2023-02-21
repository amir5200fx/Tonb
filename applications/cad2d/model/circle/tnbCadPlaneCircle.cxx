#include <Cad2d_Plane.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Vec2d.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

#include <gp_Circ2d.hxx>

namespace tnbLib
{
	static const std::string extension = Cad2d_Plane::extension;

	static unsigned short verbose = 0;
	static gp_Ax2 mySys = gp::XOY();
	//static bool exeTag = false;

	static std::shared_ptr<Cad2d_Plane> myShape;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void saveTo(const std::string& name)
	{
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " no shape has been created!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myShape, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " no shape has been created!" << endl
				<< abort(FatalError);
		}

		saveTo(myShape->Name());
	}

	auto createGeoCircle(const gp_Ax2d& ax, double r)
	{
		gp_Circ2d g(ax, r);
		return std::move(g);
	}

	void makeCircle(const gp_Circ2d& c, const std::string& name)
	{
		myShape = Cad2d_Plane::MakeCircle(c, mySys);
		myShape->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the circle shape is created!" << endl
				<< " - name: " << myShape->Name() << endl;
		}
	}

	void makeCircle(const gp_Circ2d& c)
	{
		makeCircle(c, "circle");
	}

	void makeCircle(const gp_Circ2d& c, const Pnt2d& p, const std::string& name)
	{
		myShape = Cad2d_Plane::MakeCircle(c, p, mySys);
		myShape->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the circle shape is created!" << endl
				<< " - name: " << myShape->Name() << endl;
		}
	}

	void makeCircle(const gp_Circ2d& c, const Pnt2d& p)
	{
		makeCircle(c, p, "circle");
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2, const std::string& name)
	{
		myShape = Cad2d_Plane::MakeCircle(p0, p1, p2, mySys);
		myShape->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the circle shape is created!" << endl
				<< " - name: " << myShape->Name() << endl;
		}
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		makeCircle(p0, p1, p2, "circle");
	}

	void makeCircle(const Pnt2d& p0, double r, const std::string& name)
	{
		myShape = Cad2d_Plane::MakeCircle(p0, r, mySys);
		myShape->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the circle shape is created!" << endl
				<< " - name: " << myShape->Name() << endl;
		}
	}

	void makeCircle(const Pnt2d& p0, double r)
	{
		makeCircle(p0, r, "circle");
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1, const std::string& name)
	{
		myShape = Cad2d_Plane::MakeCircle(p0, p1, mySys);
		myShape->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the circle shape is created!" << endl
				<< " - name: " << myShape->Name() << endl;
		}
	}

	void makeCircle(const Pnt2d& p0, const Pnt2d& p1)
	{
		makeCircle(p0, p1, "circle");
	}

	auto createPoint(double x, double y)
	{
		return Pnt2d(x, y);
	}

	auto makeDir(double x, double y)
	{
		return Dir2d(x, y);
	}

	auto makeVec(double x, double y)
	{
		return Vec2d(x, y);
	}

	auto makeAxis(const Pnt2d& pt, const Dir2d& d)
	{
		return gp_Ax2d(pt, d);
	}

	void setSystem(const gp_Ax2& ax)
	{
		mySys = ax;
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

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators

		mod->add(chaiscript::fun([](double x, double y)-> auto {return createPoint(x, y); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y)-> auto {return makeVec(x, y); }), "createVector");
		mod->add(chaiscript::fun([](double x, double y)-> auto {return makeDir(x, y); }), "createDirection");

		mod->add(chaiscript::fun([](const Pnt2d& P, const Dir2d& d)-> auto {return makeAxis(P, d); }), "createAxis");

		mod->add(chaiscript::fun([](const gp_Ax2d& ax, double r) -> auto {return createGeoCircle(ax, r); }), "createGeoCircle");

		mod->add(chaiscript::fun([](const gp_Circ2d& c)-> void {makeCircle(c); }), "makeCircle");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const std::string& name)-> void {makeCircle(c, name); }), "makeCircle");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p)-> void {makeCircle(c, p); }), "makeCircle");
		mod->add(chaiscript::fun([](const gp_Circ2d& c, const Pnt2d& p, const std::string& name)-> void {makeCircle(c, p, name); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> void {makeCircle(p0, p1, p2); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2, const std::string& name)-> void {makeCircle(p0, p1, p2, name); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p, double r)-> void {makeCircle(p, r); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p, double r, const std::string& name)-> void {makeCircle(p, r, name); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1)-> void {makeCircle(p0, p1); }), "makeCircle");
		mod->add(chaiscript::fun([](const Pnt2d& p0, const Pnt2d& p1, const std::string& name)-> void {makeCircle(p0, p1, name); }), "makeCircle");
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
			Info << " This application is aimed to create a planar circle." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(x, y)" << endl
				<< " - [Dir] createDirection(x, y)" << endl << endl

				<< " - [Axis] createAxis(Point, Dir)" << endl << endl

				<< " - [gCir] createGeoCircle(Axis, radius)" << endl << endl

				<< " - makeCircle(gCircle, name [optional])" << endl
				<< " - makeCircle(gCircle, Point, name [optional])" << endl
				<< " - makeCircle(Point, Point, Point, name [optional])" << endl
				<< " - makeCircle(Point, double, name [optional])" << endl
				<< " - makeCircle(Point, Point, name [optional])" << endl
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
				fileName theFileName(file::GetSystemFile("tnbCadPlaneCircle"));

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