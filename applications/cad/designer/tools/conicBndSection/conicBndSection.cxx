#include <ShapePx_TopoCtrlNet.hxx>
#include <ShapePx_ConicSection.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Entity3d_Chain.hxx>
#include <Pnt3d.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <OFstream.hxx>

#include <fstream>
#include <fileName.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<ShapePx_TopoCtrlNet> net_t;

	static net_t myNet;
	static double myBaseWeight = std::sqrt(2.0) / 2.0;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	void setVerbose(unsigned short i)
	{
		tnbLib::Info << endl;
		tnbLib::Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setWeight(double x)
	{
		myBaseWeight = x;
		if (verbose)
		{
			tnbLib::Info << endl
				<< " - the weight is set to: " << myBaseWeight << endl;
		}
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::cout << "fn = " << fn << std::endl;
		if (verbose)
		{
			tnbLib::Info << endl;
			tnbLib::Info << " loading the model from, " << fn << endl;
			tnbLib::Info << endl;
		}
		std::ifstream myFile(fn);
		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> myNet;
		}

		if (NOT myNet)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			tnbLib::Info << endl;
			tnbLib::Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			tnbLib::Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myNet;

		myFile.close();

		if (verbose)
		{
			tnbLib::Info << endl;
			tnbLib::Info << " the file is saved in: " << fn << ", successfully!" << endl;
			tnbLib::Info << endl;
		}
	}

	void exportToPlt(const std::shared_ptr<ShapePx_CtrlNet>& net, OFstream& f)
	{
		std::vector<std::vector<Pnt3d>> rows;
		rows.reserve(net->NbRows());
		for (const auto& x : net->Rows())
		{
			std::vector<Pnt3d> row;
			row.reserve(x.NbPnts());
			auto z = x.X();
			for (const auto& p : x.Pnts())
			{
				const auto& pt2 = p.first;
				Pnt3d pt(pt2.X(), pt2.Y(), z);
				row.push_back(std::move(pt));
			}
			rows.push_back(std::move(row));
		}

		auto chain = Cad_PreviewTools::RetrieveChain(rows);
		chain->ExportToPlt(f);
	}

	void exportToPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);
		if (myNet)
		{
			auto net = ShapePx_Tools::CreateControlNet(*myNet);
			exportToPlt(net, f);

			if (verbose)
			{
				Info << endl;
				Info << " the ctrl-nets are exported to *.plt, successfully!" << endl;
				Info << endl;
			}
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& first = FirstItem(myNet->Sections());
		const auto& last = LastItem(myNet->Sections());

		auto alg = std::make_shared<ShapePx_ConicSection>();

		alg->SetBaseWeight(myBaseWeight);

		alg->LoadSection(first);
		alg->Perform();

		alg->LoadSection(last);
		alg->Perform();

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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(name); }), "exportToPlt");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setWeight(x); }), "setWeight");

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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			tnbLib::Info << endl;
			tnbLib::Info << " This application is aimed to modify boundary sections of a control net." << endl;
			tnbLib::Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setWeight(double);  " << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("conicBndSection");

			try
			{
				chai.eval_file(myFileName);
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

}