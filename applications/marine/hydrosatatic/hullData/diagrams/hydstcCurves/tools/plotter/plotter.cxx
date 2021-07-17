#include <HydStatic_SolutionData_HydCurves.hxx>
#include <HydStatic_HydCurves.hxx>
#include <Pnt3d.hxx>
#include <Vec3d.hxx>
#include <Dir3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>
#include <sstream>

#define HTML_FUN(NAME) std::string NAME(const std::string& st)

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_HydCurves> soluData_t;

	static soluData_t mySolutionData;

	static bool loadTag = false;
	static unsigned short verbose(0);

	void loadSolutionData(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> mySolutionData;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		loadTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
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

	std::string createCanvas(const std::string& id, const unsigned int width, const unsigned int height)
	{
		std::ostringstream os;
		os << "<canvas id=\"" << id << "\""
			<< " width=\"" << std::to_string(width) << "\""
			<< " height=\"" << std::to_string(height) << "\"></canvas>";
		return os.str();
	}

	void saveCsvTable(const std::string& name, const std::vector<HydStatic_HydCurves::colTable>& tables)
	{
		fileName fn(name);
		std::ofstream f(fn);

		//- print header
		for (size_t i = 0; i < tables.size() - 1; i++)
		{
			f << tables[i].Name << ",";
		}
		f << tables[tables.size() - 1].Name << std::endl;
		
		//- print values
		const auto nbCols = tables.size();
		for (size_t row = 0; row < tables[0].Values.size(); row++)
		{
			for (size_t col = 0; col < nbCols - 1; col++)
			{
				const auto& x = tables[col].Values;
				f << x[row] << ",";
			}
			const auto& x = tables[nbCols - 1].Values;
			f << x[row] << std::endl;
		}
	}

	/*std::string getLabels(const std::vector<double>& xs)
	{
		std::ostringstream os;
		os << "const xlabels = [];" << std::endl;

	}*/

	/*std::string getCsvChart(const std::string& contextName)
	{
		const auto& hydCurves = mySolutionData->Curves();
		if (NOT hydCurves)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hydrostatic curves have been found!" << endl
				<< abort(FatalError);
		}

		const auto& table = hydCurves->CsvTable();
		if (NOT table)
		{
			FatalErrorIn(FunctionSIG)
				<< "no table has been found!" << endl
				<< abort(FatalError);
		}

		const auto& columns = table->Columns;
		const auto nbColumns = columns.size();
		const auto nbrows = columns[0].Values.size();


	}*/

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& myCurves = mySolutionData->Curves();
		if (NOT myCurves)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hydrostatic curves have been detected!" << endl
				<< abort(FatalError);
		}

		const auto& myTable = myCurves->CsvTable();
		if (NOT myTable)
		{
			FatalErrorIn(FunctionSIG)
				<< "no csv has been detected!" << endl
				<< abort(FatalError);
		}

		saveCsvTable("data.csv", myTable->Columns);
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionData(name); }), "loadSoluData");
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

			setFuns(mod);

			chai.add(mod);

			fileName myFileName("hullDataHydstcCurvesPlotter");

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
		else
		{
			Info << " - Unspecified command has been detected!" << endl
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

}