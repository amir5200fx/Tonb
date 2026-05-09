#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);

	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned int nbSegments = 20;

	static std::shared_ptr<Pln_Edge> myEdge;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setNbSegments(unsigned int n)
	{
		nbSegments = n;
		if (verbose)
		{
			Info << endl
				<< " - the nb. of segments is set to: " << nbSegments << endl;
		}
	}

	void loadEdge(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the edge from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> myEdge;
		}

		if (NOT myEdge)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded edge is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the edge is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << myEdge;

		if (verbose)
		{
			Info << endl;
			Info << " the edge is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		const auto& curve = myEdge->Curve();
		if (NOT curve)
		{
			FatalErrorIn(FunctionSIG)
				<< " the curve is null!" << endl
				<< abort(FatalError);
		}
		if (nbSegments < 1) nbSegments = 1;
		const auto du = (curve->LastParameter() - curve->FirstParameter()) / (double)nbSegments;
		auto poly = std::make_shared<Entity2d_Polygon>();
		auto& pnts = poly->Points();
		pnts.reserve(nbSegments + 1);
		for (size_t i = 0; i <= nbSegments; i++)
		{
			auto u = curve->FirstParameter() + i * du;
			if (u > curve->LastParameter()) u = curve->LastParameter();
			auto pt = curve->Value(u);
			pnts.push_back(std::move(pt));
		}
		myEdge->Mesh() = std::move(poly);
		exeTag = true;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadEdge(name); }), "loadEdge");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

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
			Info << " This application is aimed to discretize an edge." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " - loadEdge(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - execute()" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbDiscretizeUniformEdge2d";
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