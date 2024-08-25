#include <Cad_API.hxx>
#include <Geo_API.hxx>
#include <Geo_Tools.hxx>
#include <Global_Chaiscript.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static api::cad::Tessellation my_tessellation;

	class TessellationRunTime
	{
		/*Private Data*/
		static void configs();
	public:
		static const double default_angle;
		static const double default_deflection;
		static const double default_min_size;
		static const bool default_relative_mode;
		static const bool default_parallel_mode;
		static const bool default_adaptive_min_mode;
		static const bool default_internal_vertices_mode;
		static const bool default_control_surf_deflection;

		// constructor
		TessellationRunTime()
		{
			configs();
		}
	};
}

const double tnbLib::TessellationRunTime::default_angle = tnbLib::Geo_Tools::DegToRadian(5.0);
const double tnbLib::TessellationRunTime::default_deflection = 1.e-3;
const double tnbLib::TessellationRunTime::default_min_size = 1.e-5;
const bool tnbLib::TessellationRunTime::default_parallel_mode = false;
const bool tnbLib::TessellationRunTime::default_relative_mode = true;
const bool tnbLib::TessellationRunTime::default_adaptive_min_mode = false;
const bool tnbLib::TessellationRunTime::default_internal_vertices_mode = true;
const bool tnbLib::TessellationRunTime::default_control_surf_deflection = true;


static const tnbLib::TessellationRunTime TessellationRunTimeObj;

void tnbLib::TessellationRunTime::configs()
{
	api::cad::set_angle(my_tessellation, default_angle);
	api::cad::set_deflection(my_tessellation, default_deflection);
	api::cad::set_min_size(my_tessellation, default_min_size);
	api::cad::set_relative_mode(my_tessellation, default_relative_mode);
	api::cad::set_parallel_mode(my_tessellation, default_parallel_mode);
	api::cad::set_adaptive_min(my_tessellation, default_adaptive_min_mode);
	api::cad::set_internal_vertices_mode(my_tessellation, default_internal_vertices_mode);
	api::cad::set_control_surf_deflection(my_tessellation, default_control_surf_deflection);
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	bool IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument == command;
	}

	void activate(const module_t mod)
	{
		chai::app::functions(mod);
		chai::geo::functions(mod);
		chai::cad::functions(mod);
	}

	void set_general_functions(const module_t& mod)
	{
		mod->add(chaiscript::fun([](const api::cad::Shape& shape)->void {api::cad::tessellate(shape, my_tessellation, 0); }), "tessellate");
		mod->add(chaiscript::fun([](const api::cad::Shape& shape, unsigned short i)->void {api::cad::tessellate(shape, my_tessellation, i); }), "tessellate");
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
			Info << " This application is aimed to create a sphere." << endl;
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
			auto address = file::GetSystemFile("tonbApi");
			fileName myFileName(address);

			try
			{
				auto mod = std::make_shared<chaiscript::Module>();
				activate(mod);
				set_general_functions(mod);

				chai::obj.add(mod);

				chai::obj.eval_file(myFileName);
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}