#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>
#include <Dir3d.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	static const std::string extension = Cad_Shape::extension;
	static unsigned short verbose(0);

	static std::shared_ptr<Cad_Shape> myShape;

	void set_verbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void save_to(const std::string& name)
	{
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myShape, name + extension, verbose);
	}

	void save_to()
	{
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		save_to(myShape->Name());
	}

	void make_box(const Pnt3d& p0, const Pnt3d& p1)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, p1));
		shape->SetIndex(0);
		shape->SetName("box");
		myShape = shape;
	}

	void make_box(const Pnt3d& p0, const Pnt3d& p1, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, p1));
		shape->SetIndex(0);
		shape->SetName(name);
		myShape = shape;
	}

	void make_box(const Pnt3d& p0, double dx, double dy, double dz)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, dx, dy, dz));
		shape->SetIndex(0);
		shape->SetName("box");
		myShape = shape;
	}

	void make_box(const Pnt3d& p0, double dx, double dy, double dz, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, dx, dy, dz));
		shape->SetIndex(0);
		shape->SetName(name);
		myShape = shape;
	}

	void make_box(const gp_Ax2& ax, double dx, double dy, double dz)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(ax, dx, dy, dz));
		shape->SetIndex(0);
		shape->SetName("box");
		myShape = shape;
	}

	void make_box(const gp_Ax2& ax, double dx, double dy, double dz, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(ax, dx, dy, dz));
		shape->SetIndex(0);
		shape->SetName(name);
		myShape = shape;
	}

	void export_to_step(const std::string& file_name)
	{
		Cad_Tools::ExportToSTEP(myShape->Shape(), file_name+".step");
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
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {save_to(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {save_to(); }), "save_to");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)-> void {set_verbose(i); }), "set_verbose");


		//- functions

		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Pnt3d(x, y, z); }), "make_pnt");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Dir3d(x, y, z); }), "make_dir");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const Dir3d& N, const Dir3d& Vx)-> auto {return gp_Ax2(pt, N, Vx); }), "make_sys");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const Dir3d& V)-> auto {return gp_Ax2(pt, V); }), "make_sys");

		mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1)-> void {make_box(p0, p1); }), "make_box");
		mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1, const std::string& name)-> void {make_box(p0, p1, name); }), "make_box");
		mod->add(chaiscript::fun([](const Pnt3d& p0, double dx, double dy, double dz)-> void {make_box(p0, dx, dy, dz); }), "make_box");
		mod->add(chaiscript::fun([](const Pnt3d& p0, double dx, double dy, double dz, const std::string& name)-> void {make_box(p0, dx, dy, dz, name); }), "make_box");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double dx, double dy, double dz)-> void {make_box(ax, dx, dy, dz); }), "make_box");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double dx, double dy, double dz, const std::string& name)-> void {make_box(ax, dx, dy, dz, name); }), "make_box");

		mod->add(chaiscript::fun([](const std::string& file_name)-> void {export_to_step(file_name); }), "export_to_step");
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
			Info << " This application is aimed to create a box." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl
				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [Direction] createDirection(double, double, double)" << endl
				<< " - [Ax] createCoordinateSystem(Point, main Direction, x-Direction)" << endl
				<< " - [Ax] createCoordinateSystem(Point, main Direction);     - x- and y-direction are defined automatically." << endl
				<< endl
				<< " - makeBox(Point, Point, name [optional])" << endl
				<< " - makeBox(Point, dx, dy, dz, name [optional])" << endl
				<< " - makeBox(Ax, dx, dy, dz, name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbCadBox");
				fileName myFileName(address);

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