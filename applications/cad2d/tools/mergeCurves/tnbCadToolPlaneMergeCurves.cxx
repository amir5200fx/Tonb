#include <Cad2d_CurveLength_UniDiscret.hxx>
#include <Cad2d_MergeCurves.hxx>
#include <Cad2d_MergeCurvesInfo.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string myFileName;
	static auto loadExt = Pln_Edge::extension + "list";
	static auto saveExt = Pln_Edge::extension + "list";

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static double myTol = 1.0E-4;

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Pln_Edge>> myMergedCurves;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		file::SaveTo(myMergedCurves, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto removeDegenerateCurves
	(
		const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
		const double tol
	)
	{
		static auto lengthCalculator = std::make_shared<cad2dLib::CurveLength_UniDiscret>();

		std::vector<std::shared_ptr<Pln_Edge>> curves;
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			const auto& c = x->Curve();
			if (lengthCalculator->CalcLength(c) > tol)
			{
				curves.push_back(x);
			}
		}
		return std::move(curves);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		const auto b = Pln_Tools::BoundingBox(myCurves);
		const auto tol = myTol * b.Diameter();

		auto curves = removeDegenerateCurves(myCurves, tol);

		auto algInfo = std::make_shared<Cad2d_MergeCurvesInfo>(tol, 10.0 * tol);
		auto mergeAlg = std::make_shared<Cad2d_MergeCurves>(curves, algInfo);
		mergeAlg->Perform();
		//auto merged = Pln_Tools::RetrieveMergedEdges(curves, tol, 10.0*tol);

		exeTag = true;

		myMergedCurves = std::move(curves);

		if (verbose)
		{
			Info << endl
				<< " the application is performed successfully!" << endl;
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
		// io functions [2/16/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		// settings [2/16/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTolerance(x); }), "setTolerance");

		//- operators
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to merge an array of planar curves." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setTolerance(double)" << endl << endl

				<< " # functions: " << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneMergeCurves"));

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