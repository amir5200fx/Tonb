#include <Marine_AnalysisSectionsIO.hxx>
#include <Marine_SectionsIO.hxx>
#include <Marine_ShapeIO.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_CmpSection.hxx>
#include <MarineBase_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Geo_BoxTools.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static std::string sectionType = "displacer";
	static std::shared_ptr<marineLib::io::AnalysisSections> myAnalyzer;

	static std::vector<std::shared_ptr<Marine_CmpSection>> mySections;

	static auto algInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	class RunTimeAlgInfo
	{

	public:

		RunTimeAlgInfo()
		{
			SetSettings();
		}

		static void SetSettings();
	};

	static RunTimeAlgInfo myRunTimeAlgInfoObj;

	void tnbLib::RunTimeAlgInfo::SetSettings()
	{
		algInfo->SetMaxNbIterations(500);
		algInfo->SetNbInitIterations(5);
		algInfo->SetTolerance(1.0E-6);
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setSectionType(const std::string& name)
	{
		sectionType = name;
		if (verbose)
		{
			Info << endl
				<< " - the type of section is set to: " << sectionType << endl;
		}
	}

	void printSettings()
	{
		Info << endl
			<< " - section type: " << sectionType << endl;
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
			ar >> myAnalyzer;
		}

		if (NOT myAnalyzer)
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

	auto retrieveWires(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments)
	{
		std::vector<std::shared_ptr<Pln_Wire>> wires;
		wires.reserve(segments.size());
		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x->Node0());
			Debug_Null_Pointer(x->Node0()->Vtx());
			auto ring = Pln_Tools::RetrieveWire(x->Node0()->Vtx());
			wires.push_back(std::move(ring));
		}
		return std::move(wires);
	}

	auto calcBoundingBox(const std::vector<std::shared_ptr<Pln_Wire>>& wires)
	{
		auto iter = wires.begin();
		auto b = (*iter)->BoundingBox(0);
		iter++;
		while (iter NOT_EQUAL wires.end())
		{
			b = Geo_BoxTools::Union(b, (*iter)->BoundingBox(0));
			iter++;
		}
		return std::move(b);
	}

	auto removeDegeneracies(const std::vector<std::shared_ptr<Pln_Wire>>& wires)
	{
		const auto b = calcBoundingBox(wires);
		const auto d = b.Diameter()*1.0E-6;
		std::vector<std::shared_ptr<Pln_Wire>> feasibles;
		for (const auto& x : wires)
		{
			auto area = Cad2d_CmptLib::Area(*x, algInfo);
			if (x->Orientation() IS_EQUAL Pln_Orientation::Pln_Orientation_CW) area *= (-1.0);
			if (area > d)
			{
				feasibles.push_back(x);
			}
		}
		return std::move(feasibles);
	}

	auto retrieveSections(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments, const gp_Ax2& ax2, double coord)
	{
		auto wires = retrieveWires(segments);

		wires = removeDegeneracies(wires);
		for (const auto& x : wires)
		{
			x->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
		}

		Marine_SectionType t;
		Marine_PlnCurveType pt;
		if (sectionType IS_EQUAL "displacer")
		{
			t = Marine_SectionType::displacer;
			pt = Marine_PlnCurveType::displacer;
		}
		else if (sectionType IS_EQUAL "tank")
		{
			t = Marine_SectionType::tank;
			pt = Marine_PlnCurveType::tank;
		}
		else if (sectionType IS_EQUAL "sail")
		{
			t = Marine_SectionType::sail;
			pt = Marine_PlnCurveType::sail;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no valid section has been found!" << endl
				<< " - section type: displacer, tank and sail" << endl
				<< abort(FatalError);
		}

		for (const auto& x : wires)
		{
			Marine_SectTools::ForcedToChangeType(x, pt);
		}
		
		const auto sections = Marine_SectTools::SectionCreator(wires, ax2, t);
		const auto cmpSection = Marine_SectTools::CmpSectionCreator(sections);
		Marine_SectTools::SetLocation(cmpSection, coord);

		return std::move(cmpSection);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& model = myAnalyzer->Model();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been found!" << endl
				<< abort(FatalError);
		}
		const auto& shape = model->GetShape();
		if (NOT shape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been found!" << endl
				<< abort(FatalError);
		}

		const auto& b = shape->PreciseBndBox();

		const auto Oxyz = MarineBase_Tools::CalcOxyz(*b);
		const auto ax2 = gp_Ax2(Oxyz, gp::DZ());

		const auto& shapes = model->GetSections();
		const auto& sections = myAnalyzer->GetSections();
		size_t k = 0;

		mySections.reserve(sections.size());
		for (const auto& x : sections)
		{
			auto section = retrieveSections(x->Segments(), ax2, shapes[k++]->X());
			section->SetIndex(k);

			if (verbose)
			{
				Info << " - section nb. " << section->Index() << " is created, successfully." << endl;
			}
			
			mySections.push_back(std::move(section));
		}
		if (verbose)
		{
			Info << endl
				<< " All sections are created, successfully." << endl;
		}

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
		mod->add(chaiscript::fun([]()-> void {printSettings(); }), "printSettings");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setSectionType(name); }), "setSectionType");
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
			Info << " This application is aimed to create a section list." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setSectionType(string);      - types: displacer, tank, sail" << endl
				<< " - printSettings()" << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hydstcSectionCreator");

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