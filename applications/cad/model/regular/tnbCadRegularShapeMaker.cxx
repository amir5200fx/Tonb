#include <Cad_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>
#include <Dir3d.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);

	std::vector<std::shared_ptr<Cad_Shape>> myShapes;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void saveTo()
	{
		for (size_t i = 0; i < myShapes.size(); i++)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + myShapes[i]->Name();
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);
			oa << myShapes[i];

			if (verbose)
			{
				Info << " - the shape is saved in: " << address << ", successfully!" << endl;
			}

			file.close();
		}

		if (verbose)
		{
			Info << endl
				<< " All shapes are saved, successfully!" << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		for (size_t i = 0; i < myShapes.size(); i++)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);
			oa << myShapes[i];

			if (verbose)
			{
				Info << " - the shape is saved in: " << address << ", successfully!" << endl;
			}

			file.close();
		}

		if (verbose)
		{
			Info << endl
				<< " All shapes are saved, successfully!" << endl;
		}
	}

	void makeBox(const Pnt3d& p0, const Pnt3d& p1)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, p1));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("box");
		myShapes.push_back(std::move(shape));
	}

	void makeBox(const Pnt3d& p0, const Pnt3d& p1, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, p1));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeBox(const Pnt3d& p0, double dx, double dy, double dz)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, dx, dy, dz));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("box");
		myShapes.push_back(std::move(shape));
	}

	void makeBox(const Pnt3d& p0, double dx, double dy, double dz, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(p0, dx, dy, dz));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeBox(const gp_Ax2& ax, double dx, double dy, double dz)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(ax, dx, dy, dz));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("box");
		myShapes.push_back(std::move(shape));
	}

	void makeBox(const gp_Ax2& ax, double dx, double dy, double dz, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Box(ax, dx, dy, dz));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeCylinder(const gp_Ax2& ax, double r, double h)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("cylinder");
		myShapes.push_back(std::move(shape));
	}

	void makeCylinder(const gp_Ax2& ax, double r, double h, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeCylinder(const gp_Ax2& ax, double r, double h, double angle)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h, angle));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("cylinder");
		myShapes.push_back(std::move(shape));
	}

	void makeCylinder(const gp_Ax2& ax, double r, double h, double angle, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Cylinder(ax, r, h, angle));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const Pnt3d& c, double r)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(c, r));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("sphere");
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const Pnt3d& c, double r, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(c, r));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("sphere");
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("sphere");
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1, double angle2)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("sphere");
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1, double angle2, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1, double angle2, double angle3)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2, angle3));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName("sphere");
		myShapes.push_back(std::move(shape));
	}

	void makeSphere(const gp_Ax2& ax, double r, double angle1, double angle2, double angle3, const std::string& name)
	{
		auto shape = std::make_shared<Cad_Shape>(Cad_ShapeTools::Sphere(ax, r, angle1, angle2, angle3));
		shape->SetIndex(myShapes.size() + 1);
		shape->SetName(name);
		myShapes.push_back(std::move(shape));
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		

		//- functions

		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Pnt3d(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return Dir3d(x, y, z); }), "createDirection");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const Dir3d& N, const Dir3d& Vx)-> auto {return gp_Ax2(pt, N, Vx); }), "createCoordinateSystem");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const Dir3d& V)-> auto {return gp_Ax2(pt, V); }), "createCoordinateSystem");

		mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1)-> void {makeBox(p0, p1); }), "makeBox");
		mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1, const std::string& name)-> void {makeBox(p0, p1, name); }), "makeBox");
		mod->add(chaiscript::fun([](const Pnt3d& p0, double dx, double dy, double dz)-> void {makeBox(p0, dx, dy, dz); }), "makeBox");
		mod->add(chaiscript::fun([](const Pnt3d& p0, double dx, double dy, double dz, const std::string& name)-> void {makeBox(p0, dx, dy, dz, name); }), "makeBox");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double dx, double dy, double dz)-> void {makeBox(ax, dx, dy, dz); }), "makeBox");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double dx, double dy, double dz, const std::string& name)-> void {makeBox(ax, dx, dy, dz, name); }), "makeBox");

		mod->add(chaiscript::fun([](const gp_Ax2& ax, double r, double h)-> void {makeCylinder(ax, r, h); }), "makeCylinder");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double r, double h, const std::string& name)-> void {makeCylinder(ax, r, h, name); }), "makeCylinder");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double r, double h, double angle)-> void {makeCylinder(ax, r, h, angle); }), "makeCylinder");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, double r, double h, double angle, const std::string& name)-> void {makeCylinder(ax, r, h, angle, name); }), "makeCylinder");

		mod->add(chaiscript::fun([](const Pnt3d& c, double r)-> void {makeSphere(c, r); }), "makeSphere");
		mod->add(chaiscript::fun([](const Pnt3d& c, double r, const std::string& name)-> void {makeSphere(c, r, name); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r)-> void {makeSphere(c, r); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, const std::string& name)-> void {makeSphere(c, r, name); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1)-> void {makeSphere(c, r, angle1); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1, const std::string& name)-> void {makeSphere(c, r, angle1, name); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1, double angle2)-> void {makeSphere(c, r, angle1, angle2); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1, double angle2, const std::string& name)-> void {makeSphere(c, r, angle1, angle2, name); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1, double angle2, double angle3)-> void {makeSphere(c, r, angle1, angle2, angle3); }), "makeSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& c, double r, double angle1, double angle2, double angle3, const std::string& name)-> void {makeSphere(c, r, angle1, angle2, angle3, name); }), "makeSphere");
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
			Info << " This application is aimed to create regular shapes." << endl;
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
				<< endl
				<< " - makeCylinder(Ax, radius, height, name [optional])" << endl
				<< " - makeCylinder(Ax, radius, height, angle, name [optional])" << endl
				<< endl
				<< " - makeSphere(Point, radius, name [optional])" << endl
				<< " - makeSphere(Ax, radius, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, angle2, name [optional])" << endl
				<< " - makeSphere(Ax, radius, angle1, angle2, angle3, name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbCadRegularShapeMaker";
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