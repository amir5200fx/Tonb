#include <ShapePx_TopoCtrlNet.hxx>
#include <ShapePx_ArcSection.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Entity3d_Chain.hxx>
#include <Pnt3d.hxx>
#include <NumAlg_FalsePos_Info.hxx>
#include <NumAlg_Secant_Info.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <OFstream.hxx>

#include <fstream>
#include <fileName.hxx>

namespace tnbLib
{

	static const std::string loadExt = ShapePx_TopoCtrlNet::extension;
	static const std::string saveExt = ShapePx_TopoCtrlNet::extension;

	typedef std::shared_ptr<ShapePx_TopoCtrlNet> net_t;

	static net_t myNet;
	static double myBaseWeight = std::sqrt(2.0) / 2.0;

	static bool loadTag = false;
	static bool exeTag = false;
	static std::string myFileName;

	static unsigned short verbose(0);

	static auto myAlg = std::make_shared<ShapePx_ArcSection>();

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
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
		file::CheckExtension(name);

		myNet = file::LoadFile<std::shared_ptr<ShapePx_TopoCtrlNet>>(name + loadExt, verbose);
		if (NOT myNet)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadModel()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadModel(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myNet;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
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

	auto createFalsePosInfo()
	{
		auto iterInfo = std::make_shared<NumAlg_FalsePos_Info>();

		iterInfo->SetDelta(1.0E-6);
		iterInfo->SetTolerance(1.0E-6);
		iterInfo->SetMaxIterations(100);

		return std::move(iterInfo);
	}

	auto createSecantInfo()
	{
		auto iterInfo = std::make_shared<NumAlg_Secant_Info>();

		iterInfo->SetMaxIterations(100);
		iterInfo->SetSmall(1.0E-6);
		iterInfo->SetTolerance(1.0E-6);
		iterInfo->SetUnderRelaxation(0.85);
		iterInfo->SetZero(1.0E-8);

		return std::move(iterInfo);
	}

	auto createBisection()
	{
		auto iterInfo = std::make_shared<NumAlg_BisectionSolver_Info>();

		iterInfo->SetDelta(1.0E-6);
		iterInfo->SetTolerance(1.0E-6);
		iterInfo->SetMaxIterations(100);

		return std::move(iterInfo);
	}

	void setSmall(const std::shared_ptr<NumAlg_Secant_Info>& info, double x)
	{
		info->SetSmall(x);
	}

	void setUnderRelaxation(const std::shared_ptr<NumAlg_Secant_Info>& info, double x)
	{
		info->SetUnderRelaxation(x);
	}

	void setZero(const std::shared_ptr<NumAlg_Secant_Info>& info, double x)
	{
		info->SetZero(x);
	}

	template<class SolverInfo>
	void setTolerance(const std::shared_ptr<SolverInfo>& info, double x)
	{
		info->SetTolerance(x);
	}

	template<class SolverInfo>
	void setDelta(const std::shared_ptr<SolverInfo>& info, double x)
	{
		info->SetDelta(x);
	}

	template<class SolverInfo>
	void setMaxIterations(const std::shared_ptr<SolverInfo>& info, int x)
	{
		info->SetMaxIterations(x);
	}

	void printInfo(const std::shared_ptr<NumAlg_FalsePos_Info>& info)
	{
		Info << " - Max. nb. of iterations: " << info->MaxIterations() << endl
			<< " - Delta: " << info->Delta() << endl
			<< " - Tolerance: " << info->Tolerance() << endl;
	}
	
	void printInfo(const std::shared_ptr<NumAlg_BisectionSolver_Info>& info)
	{
		Info << " - Max. nb. of iterations: " << info->MaxIterations() << endl
			<< " - Delta: " << info->Delta() << endl
			<< " - Tolerance: " << info->Tolerance() << endl;
	}

	void printInfo(const std::shared_ptr<NumAlg_Secant_Info>& info)
	{
		Info << " - Max. nb. of iterations: " << info->MaxIterations() << endl
			<< " - Small: " << info->Small() << endl
			<< " - Zero: " << info->Zero() << endl
			<< " - Tolerance: " << info->Tolerance() << endl
			<< " - Under relaxation: " << info->UnderRelaxation() << endl;
	}

	void setIterInfo(const std::shared_ptr<NumAlg_FalsePos_Info>& info)
	{
		auto myInfo = std::make_shared<ShapePx_ArcSectionIterInfo_FalsePos>(info);
		myAlg->SetIterInfo(myInfo);
	}
	
	void setIterInfo(const std::shared_ptr<NumAlg_BisectionSolver_Info>& info)
	{
		auto myInfo = std::make_shared<ShapePx_ArcSectionIterInfo_Bisection>(info);
		myAlg->SetIterInfo(myInfo);
	}

	void setIterInfo(const std::shared_ptr<NumAlg_Secant_Info>& info)
	{
		auto myInfo = std::make_shared<ShapePx_ArcSectionIterInfo_Secant>(info);
		myAlg->SetIterInfo(myInfo);
	}

	void printIterInfo(const std::shared_ptr<ShapePx_ArcSectionIterInfo>& info)
	{
		if (auto myInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_FalsePos>(info))
		{
			const auto& x = myInfo->Info();
			Info << " - Nb. of iterations: " << x->NbIterations() << endl
				<< " - Residual: " << x->Residual() << endl;
		}
		else if (auto myInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_Secant>(info))
		{
			const auto& x = myInfo->Info();
			Info << " - Nb. of iterations: " << x->NbIterations() << endl
				<< " - Residual: " << x->Residual() << endl;
		}
		else if (auto myInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_Bisection>(info))
		{
			const auto& x = myInfo->Info();
			Info << " - Nb. of iterations: " << x->NbIterations() << endl
				<< " - Residual: " << x->Residual() << endl;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unrecognized type of iteration has been detected!" << endl
				<< abort(FatalError);
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

		myAlg->SetBaseWeight(myBaseWeight);

		myAlg->LoadSection(first);
		myAlg->Perform();

		myAlg->LoadSection(last);
		myAlg->Perform();

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
		mod->add(chaiscript::fun([]()->void {loadModel(); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(name); }), "exportToPlt");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info)-> void {printInfo(info); }), "printInfo");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_FalsePos_Info>& info)-> void {printInfo(info); }), "printInfo");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_BisectionSolver_Info>& info)-> void {printInfo(info); }), "printInfo");
		mod->add(chaiscript::fun([]()-> void {printIterInfo(myAlg->IterInfo()); }), "printIterInfo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setWeight(x); }), "setWeight");

		mod->add(chaiscript::fun([]()-> auto {return createFalsePosInfo(); }), "createFalsePos");
		mod->add(chaiscript::fun([]()-> auto {return createSecantInfo(); }), "createSecant");
		mod->add(chaiscript::fun([]()-> auto {return createBisection(); }), "createBisection");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info)-> void {setIterInfo(info); }), "setIterInfo");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_FalsePos_Info>& info)-> void {setIterInfo(info); }), "setIterInfo");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_BisectionSolver_Info>& info)-> void {setIterInfo(info); }), "setIterInfo");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, double x)-> void {setSmall(info, x); }), "setSmall");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, double x)-> void {setUnderRelaxation(info, x); }), "setUnderRelaxation");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, double x)-> void {setZero(info, x); }), "setZero");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, double x)-> void {setDelta(info, x); }), "setDelta");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_Secant_Info>& info, int x)-> void {setMaxIterations(info, x); }), "setMaxNbIterations");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_FalsePos_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_FalsePos_Info>& info, double x)-> void {setDelta(info, x); }), "setDelta");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_FalsePos_Info>& info, int x)-> void {setMaxIterations(info, x); }), "setMaxNbIterations");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_BisectionSolver_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_BisectionSolver_Info>& info, double x)-> void {setDelta(info, x); }), "setDelta");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_BisectionSolver_Info>& info, int x)-> void {setMaxIterations(info, x); }), "setMaxNbIterations");


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
				<< " - loadModel(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " - printInfo(info)" << endl
				<< " - printIterInfo()" << endl
				<< " - exportToPlt(string)" << endl << endl

				<< " - [info] createFalsePos()" << endl
				<< " - [info] createSecant()" << endl
				<< " - [info] createBisection()" << endl

				<< " - setIterInfo(info)" << endl << endl

				<< " - (secant info).setSmall(double)" << endl
				<< " - (secant info).setUnderRelaxation(double)" << endl
				<< " - (secant info).setZero(double)" << endl << endl

				<< " - (info).setTolerance(double)" << endl
				<< " - (info).setMaxNbIterations(int)" << endl << endl

				<< " - (bisection info).setDelta(double)" << endl
				<< " - (falsePos info).setDelta(double)" << endl << endl

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

			fileName myFileName("arcBndSection");

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