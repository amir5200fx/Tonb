#include <HydStatic_SolutionData_Coeffs.hxx>
#include <HydStatic_FormDims.hxx>
#include <HydStatic_FormCoeff.hxx>
#include <Marine_Wave.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>
#include <sstream>

#define HTML_FUN(NAME) std::string NAME(const std::string& st)

namespace tnbLib
{

	static bool loadTag = false;
	static unsigned short verbose = 0;

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;

	static soluData_t mySolutionData;

	void loadData(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);

		TNB_iARCH_FILE_TYPE ar(f);
		ar >> mySolutionData;

		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "null solution-data has been detected!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " the solution data has been loaded from: " << fn << ", successfully!" << endl;
		}
	}

	namespace html
	{
		HTML_FUN(td)
		{
			std::stringstream os;
			os << "<td>" << st << "</td>";
			return os.str();
		}

		HTML_FUN(th)
		{
			std::stringstream os;
			os << "<th>" << st << "</th>";
			return os.str();
		}

		HTML_FUN(tr)
		{
			std::stringstream os;
			os << "<tr>" << st << "</tr>";
			return os.str();
		}

		HTML_FUN(caption)
		{
			std::stringstream os;
			os << "<caption>" << st << "</caption>";
			return os.str();
		}

		HTML_FUN(table)
		{
			std::stringstream os;
			os << "<table>" << st << "</table>";
			return os.str();
		}

		HTML_FUN(h1)
		{
			std::stringstream os;
			os << "<h1>" << st << "</h1>";
			return os.str();
		}

		HTML_FUN(h2)
		{
			std::stringstream os;
			os << "<h2>" << st << "</h2>";
			return os.str();
		}

		HTML_FUN(h3)
		{
			std::stringstream os;
			os << "<h3>" << st << "</h3>";
			return os.str();
		}
	}
	
	std::string print_point(const Pnt3d& pt)
	{
		std::ostringstream os;
		os << "(" << pt.X() << ", " << pt.Y() << ", " << pt.Z() << ")";
		return os.str();
	}

	std::string print_vector(const Vec3d& vt)
	{
		std::ostringstream os;
		os << "(" << vt.X() << ", " << vt.Y() << ", " << vt.Z() << ")";
		return os.str();
	}

	std::string print_direction(const Dir3d& vt)
	{
		std::ostringstream os;
		os << "(" << vt.X() << ", " << vt.Y() << ", " << vt.Z() << ")";
		return os.str();
	}

	std::string print_double(double x)
	{
		return std::to_string(x);
	}

	std::string printTable1()
	{
		const auto& myWave = mySolutionData->Wave();
		if (NOT myWave)
		{
			return " ";
		}
		std::ostringstream os;
		std::ostringstream row1;
		row1 << html::th("Wave Type") << std::endl
			<< html::th("Point On Water [m]") << std::endl
			<< html::th("Vertical Direction [-]") << std::endl
			<< html::th("Current [m/s]") << std::endl
			<< html::th("Wind [m/s]") << std::endl;
		//std::cout << myWave->PointOnWater() << std::endl;
		std::ostringstream row2;
		row2 << html::td("wave type") << std::endl
			<< html::td(print_point(myWave->PointOnWater())) << std::endl
			<< html::td(print_direction(myWave->VerticalDirection())) << std::endl
			<< html::td(print_vector(myWave->Current())) << std::endl
			<< html::td(print_vector(myWave->Wind())) << std::endl;

		os << "<table class=\"table1\">"
			<< std::endl
			<< html::caption("Wave characteristics") << std::endl
			<< html::tr(row1.str())
			<< html::tr(row2.str())
			<< "</table>"
			<< std::endl;
		return os.str();
	}

	std::string printWave()
	{
		std::ostringstream os;
		os << "<div class=\"myWave\">" << std::endl
			<< html::h3("1. Wave:") << std::endl
			<< printTable1() << std::endl
			<< "</div>" << std::endl;
		return os.str();
	}


	// Dimensional Analysis [7/8/2021 Amir]

	std::string printTable2()
	{
		const auto& myAnalys = mySolutionData->DisplacerAnalysis();
		if (NOT myAnalys)
		{
			return " ";
		}
		const auto& pars = myAnalys->Parameters();
		const auto breadth = pars->B();
		const auto depth = pars->D();
		const auto loa = pars->Loa();
		
		std::ostringstream row1;
		row1 << html::th("Parameter") << std::endl
			<< html::th("Value") << std::endl
			<< html::th("Unit") << std::endl;

		std::ostringstream row2;
		row2 << html::td("Breadth (B)") << std::endl
			<< html::td(print_double(breadth)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row3;
		row3 << html::td("Depth (D)") << std::endl
			<< html::td(print_double(depth)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row4;
		row4 << html::td("Overall Length (LOA)") << std::endl
			<< html::td(print_double(loa)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream os;
		os << "<table class=\"table2\">" << std::endl
			<< html::caption("print caption here!") << std::endl
			<< html::tr(row1.str()) << std::endl
			<< html::tr(row2.str()) << std::endl
			<< html::tr(row3.str()) << std::endl
			<< html::tr(row4.str()) << std::endl
			<< "</table>" << std::endl;
		return os.str();
	}

	std::string printDimensionalAnalys()
	{
		std::ostringstream os;
		os << "<div class=\"myDimensionalAnalysis\">" << std::endl
			<< html::h3("2. Dimensional Analysis:") << std::endl	
			<< printTable2() << std::endl
			<< "</div>" << std::endl;
		return os.str();
	}


	// print wetted dimensional analysis [7/8/2021 Amir]

	std::string printTable3()
	{
		const auto& myAnalys = mySolutionData->WettedAnalysis();
		if (NOT myAnalys)
		{
			return " ";
		}

		const auto& pars = myAnalys->Parameters();

		const auto tm = pars->Tm();
		const auto app = pars->App();
		const auto fpp = pars->Fpp();
		const auto mpp = pars->Mpp();
		const auto lpp = pars->Lpp();
		const auto bwl = pars->Bwl();
		const auto lwl = pars->Lwl();
		const auto fwl = pars->Fwl();
		const auto awl = pars->Awl();
		const auto fuw = pars->Fuw();
		const auto auw = pars->Auw();
		const auto los = pars->Los();

		std::ostringstream row1;
		row1 << html::th("Parameter") << std::endl
			<< html::th("Value") << std::endl
			<< html::th("Unit") << std::endl;

		std::ostringstream row2;
		row2 << html::td("Draft at Mid. (TM)") << std::endl
			<< html::td(print_double(tm)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row3;
		row3 << html::td("After Perpendicular (App)") << std::endl
			<< html::td(print_double(app)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row4;
		row4 << html::td("Forward Perpendicular (Fpp)") << std::endl
			<< html::td(print_double(fpp)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row5;
		row5 << html::td("Middle Perpendicular (Mpp)") << std::endl
			<< html::td(print_double(mpp)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row6;
		row6 << html::td("Length between Perpendiculars (Lpp)") << std::endl
			<< html::td(print_double(lpp)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row7;
		row7 << html::td("Breadth Waterline (BWL)") << std::endl
			<< html::td(print_double(bwl)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row8;
		row8 << html::td("Waterline Length (LWL)") << std::endl
			<< html::td(print_double(lwl)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row9;
		row9 << html::td("Fwd. Waterline (FWL)") << std::endl
			<< html::td(print_double(fwl)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row10;
		row10 << html::td("Aft. Waterline (AWL)") << std::endl
			<< html::td(print_double(awl)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row11;
		row11 << html::td("Fwd. Underwater (FUW)") << std::endl
			<< html::td(print_double(fuw)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row12;
		row12 << html::td("Aft. Underwater (AUW)") << std::endl
			<< html::td(print_double(auw)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row13;
		row13 << html::td("Submerged Overall Length (LOS)") << std::endl
			<< html::td(print_double(los)) << std::endl
			<< html::td("[m]") << std::endl;

		std::ostringstream row14;
		row14 << html::td("App. mode:") << std::endl
			<< html::td((myAnalys->AppMode() IS_EQUAL formDim::Wetted::appMode::Auto ? "auto" : "rudder axis")) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream os;
		os << "<table class=\"table3\">" << std::endl
			<< html::caption("print caption here!") << std::endl
			<< html::tr(row1.str()) << std::endl
			<< html::tr(row2.str()) << std::endl
			<< html::tr(row3.str()) << std::endl
			<< html::tr(row4.str()) << std::endl
			<< html::tr(row5.str()) << std::endl
			<< html::tr(row6.str()) << std::endl
			<< html::tr(row7.str()) << std::endl
			<< html::tr(row8.str()) << std::endl
			<< html::tr(row9.str()) << std::endl
			<< html::tr(row10.str()) << std::endl
			<< html::tr(row11.str()) << std::endl
			<< html::tr(row12.str()) << std::endl
			<< html::tr(row13.str()) << std::endl
			<< html::tr(row14.str()) << std::endl
			<< "</table>" << std::endl;
		return os.str();
	}

	std::string printWettedDimAnalys()
	{
		std::ostringstream os;
		os << "<div class=\"myWettedDimAnalys\">" << std::endl
			<< html::h3("3. Wetted Dimensional Analysis:") << std::endl
			<< printTable3() << std::endl
			<< "</div>" << std::endl;
		return os.str();
	}

	// print hull's coefficients [7/8/2021 Amir]

	std::string printTable4()
	{
		const auto& myAnalys = mySolutionData->CoeffAnalysis();
		if (NOT myAnalys)
		{
			return " ";
		}

		const auto& pars = myAnalys->Parameters();

		const auto cb = pars->Cb();
		const auto dispv = pars->Dispv();
		const auto cm = pars->Cm();
		const auto am = pars->Am();
		const auto cp = pars->Cp();
		const auto cvp = pars->Cvp();
		const auto aw = pars->Aw();
		const auto cwl = pars->Cwl();

		std::ostringstream row1;
		row1 << html::th("Parameter") << std::endl
			<< html::th("Value") << std::endl
			<< html::th("Unit") << std::endl;

		std::ostringstream row2;
		row2 << html::td("Block Coeff. (CB)") << std::endl
			<< html::td(print_double(cb)) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream row3;
		row3 << html::td("Displacement (DISPV)") << std::endl
			<< html::td(print_double(dispv)) << std::endl
			<< html::td("[m^3]") << std::endl;

		std::ostringstream row4;
		row4 << html::td("Midship coeff. (CM)") << std::endl
			<< html::td(print_double(cm)) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream row5;
		row5 << html::td("Midship-section Area (AM)") << std::endl
			<< html::td(print_double(am)) << std::endl
			<< html::td("[m^2]") << std::endl;

		std::ostringstream row6;
		row6 << html::td("Prismatic Coeff. (CP)") << std::endl
			<< html::td(print_double(cp)) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream row7;
		row7 << html::td("Vertical Prismatic Coeff. (CVP)") << std::endl
			<< html::td(print_double(cvp)) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream row8;
		row8 << html::td("Waterplane Area (AW)") << std::endl
			<< html::td(print_double(aw)) << std::endl
			<< html::td("[m^2]") << std::endl;

		std::ostringstream row9;
		row9 << html::td("Waterplane-area Coeff. (CWL)") << std::endl
			<< html::td(print_double(cwl)) << std::endl
			<< html::td("[-]") << std::endl;

		std::ostringstream os;
		os << "<table class=\"table4\">" << std::endl
			<< html::caption("print caption here!") << std::endl
			<< html::tr(row1.str()) << std::endl
			<< html::tr(row2.str()) << std::endl
			<< html::tr(row3.str()) << std::endl
			<< html::tr(row4.str()) << std::endl
			<< html::tr(row5.str()) << std::endl
			<< html::tr(row6.str()) << std::endl
			<< html::tr(row7.str()) << std::endl
			<< html::tr(row8.str()) << std::endl
			<< html::tr(row9.str()) << std::endl
			<< "</table>" << std::endl;
		return os.str();
	}

	std::string printCoeffsAnalys()
	{
		std::ostringstream os;
		os << "<div class=\"myCoeffs\">" << std::endl
			<< html::h3("4. Wetted Coefficients:") << std::endl
			<< printTable4() << std::endl
			<< "</div>" << std::endl;
		return os.str();
	}

	std::string printContainter()
	{
		std::ostringstream os;
		os << "<div class=\"container\">" << std::endl
			<< printWave() << std::endl
			<< printDimensionalAnalys() << std::endl
			<< printWettedDimAnalys() << std::endl
			<< printCoeffsAnalys() << std::endl
			<< "</div>" << std::endl;
		return os.str();
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		f << "<!DOCTYPE html>" << std::endl
			<< "<html>" << std::endl
			<< "<head>" << std::endl
			<< "<title>Tonb's Technical Report</title>" << std::endl
			<< "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">" << std::endl
			<< "</head>" << std::endl
			<< "<body>" << std::endl
			<< "<header>" << std::endl
			<< "<h1 class = myMainHeader>TECHNICAL REPORT</h1>" << std::endl
			<< "</header>" << std::endl
			<< printContainter() << std::endl
			<< "</body>" << std::endl
			<< "</html>" << std::endl;
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
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadData(name); }), "loadSoluData");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("tecReportWettedCoeff");

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