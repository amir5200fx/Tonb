#include <Marine_AnalysisSectionsReportIO.hxx>
#include <Marine_AnalysisSectionsIO.hxx>
#include <Marine_SectionsIO.hxx>
#include <Marine_DisctSectionsIO.hxx>
#include <Marine_ShapeIO.hxx>
#include <Marine_RepairSections.hxx>
#include <MarineRepairSect_AnalyzSection.hxx>
#include <MarineRepairSect_AnalyzBody.hxx>
#include <MarineRepairSect_FixedBody.hxx>
#include <MarineRepairSect_FixedSection.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Entity3d_Box.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <fstream>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static std::shared_ptr<marineLib::io::AnalysisSectionsReport> myReport;

	auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static auto mySections = std::make_shared<marineLib::io::Sections>();

	class IntegInfoRunTime
	{

	public:

		IntegInfoRunTime()
		{
			Config();
		}

		static void Config();
	};

	static IntegInfoRunTime myIntegInfoObj;

	void IntegInfoRunTime::Config()
	{
		myIntegInfo->SetMaxNbIterations(500);
		myIntegInfo->SetNbInitIterations(5);
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> myReport;
		}

		if (NOT myReport)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
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
		ar << mySections;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto removeDegeneracies(const std::vector<Handle(Geom2d_Curve)>& curves, double tol)
	{
		std::vector<Handle(Geom2d_Curve)> feasibles;
		for (const auto& x : curves)
		{
			myIntegInfo->SetTolerance(Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(x)).Diameter()*1.0E-8);
			auto len = Pln_Tools::Length(*x, myIntegInfo);

			if (len > tol)
			{
				feasibles.push_back(x);
			}
		}
		return std::move(feasibles);
	}

	auto retrieveGeomCurves(const std::vector<std::shared_ptr<Pln_Curve>>& curves)
	{
		std::vector<Handle(Geom2d_Curve)> gCurves;
		gCurves.reserve(curves.size());

		for (const auto& x : curves)
		{
			gCurves.push_back(x->Geometry());
		}
		return std::move(gCurves);
	}

	auto retrieveEdges(const std::vector<std::shared_ptr<Pln_Curve>>& curves, double tol)
	{
		auto geomCurves = retrieveGeomCurves(curves);
		auto paraCurves = removeDegeneracies(geomCurves, tol);

		std::vector<std::shared_ptr<Pln_Curve>> plnCurves;
		plnCurves.reserve(paraCurves.size());
		size_t k = 0;
		for (const auto& x : paraCurves)
		{
			auto c = std::make_shared<Pln_Curve>(x);
			c->SetIndex(++k);

			plnCurves.push_back(std::move(c));
		}

		auto plnEdges = Pln_Tools::RetrieveEdges(plnCurves);
		return std::move(plnEdges);
	}

	auto Y0(const Entity3d_Box& b)
	{
		return std::min(b.P0().Y(), b.P1().Y());
	}

	auto Y1(const Entity3d_Box& b)
	{
		return std::max(b.P0().Y(), b.P1().Y());
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT myReport->Valid())
		{
			const auto& analysis = myReport->Analysis();
			if (NOT analysis)
			{
				FatalErrorIn(FunctionSIG)
					<< "no analysis is provided!" << endl
					<< abort(FatalError);
			}
	
			if (NOT analysis->Model())
			{
				FatalErrorIn(FunctionSIG)
					<< "no model is provided!" << endl
					<< abort(FatalError);
			}

			const auto& model = analysis->Model()->GetSections();
			const auto& myShape = model->GetShape();
			if (NOT myShape)
			{
				FatalErrorIn(FunctionSIG)
					<< "no shape is provided!" << endl
					<< abort(FatalError);
			}

			Debug_Null_Pointer(myShape->PreciseBndBox());
			const auto& b = *myShape->PreciseBndBox();
			const auto tol = myShape->Tolerance();

			const auto& ioSections = analysis->GetSections();

			std::vector<std::shared_ptr<MarineRepairSect_AnalyzSection>> sections;
			sections.reserve(ioSections.size());

			std::vector<double> xs;
			xs.reserve(ioSections.size());
			for (const auto& x : ioSections)
			{
				auto sect = std::make_shared<MarineRepairSect_AnalyzSection>(x->Segments());
				sections.push_back(std::move(sect));
				xs.push_back(x->X());
			}

			auto body = std::make_shared<MarineRepairSect_AnalyzBody>(std::move(sections));

			auto repairAlg = std::make_shared<Marine_RepairSections>(std::move(body));
			repairAlg->Perform();
			Debug_If_Condition_Message(NOT repairAlg->IsDone(), "the algorithm is not performed!");

			const auto& fixedBody = repairAlg->FixedBody();
			const auto& fixedSections = fixedBody->Sections();

			auto& myEdges = mySections->GetSectionsRef();
			myEdges.reserve(fixedSections.size());

			size_t k = 0;
			for (const auto& x : fixedSections)
			{
				const auto& curves = x->Curves();
				auto edges = retrieveEdges(curves, tol*(std::abs(Y1(b) - Y0(b))));

				auto section = std::make_shared<marineLib::io::Sections::Section>();
				section->EdgesRef() = std::move(edges);
				section->SetX(xs[k++]);

				myEdges.push_back(std::move(section));
			}

			mySections->LoadShape(myShape);
		}
		else
		{
			const auto& analysis = myReport->Analysis();
			if (NOT analysis)
			{
				FatalErrorIn(FunctionSIG)
					<< "no analysis is provided!" << endl
					<< abort(FatalError);
			}

			if (NOT analysis->Model())
			{
				FatalErrorIn(FunctionSIG)
					<< "no model is provided!" << endl
					<< abort(FatalError);
			}

			const auto& model = analysis->Model()->GetSections();
			mySections = model;
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
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
			Info << " This application is aimed to repair the defected sections." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

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

			std::string address = ".\\system\\hydstcRepairSections";
			fileName myFileName(address);

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

}