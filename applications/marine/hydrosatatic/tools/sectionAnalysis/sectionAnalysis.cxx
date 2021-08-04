#include <Marine_BodyModelType.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_SectionsIO.hxx>
#include <Marine_AnalysisSectionsIO.hxx>
#include <Geo_BoxTools.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_RemoveNonManifold.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

#include <TopoDS_Shape.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static std::shared_ptr<marineLib::io::Sections> mySections;

	static const double DEFAULT_MIN_TOL = 1.0E-4;
	static const double DEFAULT_MAX_TOL = 1.0E-3;

	static auto myMinTol = DEFAULT_MIN_TOL;
	static auto myMaxTol = DEFAULT_MAX_TOL;

	typedef std::shared_ptr<Cad2d_RemoveNonManifold::Segment> segment_t;
	typedef std::shared_ptr<std::vector<segment_t>> segmentList_t;
	static std::vector<segmentList_t> mySegments;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMinTol(double x)
	{
		myMinTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the minTol is set to: " << myMinTol << endl;
		}
	}

	void setMaxTol(double x)
	{
		myMaxTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the maxTol is set to: " << myMaxTol << endl;
		}
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
			ar >> mySections;
		}

		if (NOT mySections)
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

		auto analyzerIO = std::make_shared<marineLib::io::AnalysisSections>();
		analyzerIO->LoadModel(mySections);

		auto& sections = analyzerIO->SectionsRef();
		sections.reserve(mySegments.size());

		for (const auto& x : mySegments)
		{
			auto section = std::make_shared<marineLib::io::AnalysisSections::Section>();
			section->SegmentsRef() = *x;

			sections.push_back(std::move(section));
		}

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << analyzerIO;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto retrieveCmpEdges(const std::vector<std::shared_ptr<Pln_Edge>>& edges)
	{
		auto analyzer = std::make_shared<Cad2d_RemoveNonManifold>(edges);
		analyzer->Perform();
		auto compEdges = analyzer->RetrieveCompundEdges();
		return std::move(compEdges);
	}

	auto calcBoundingBox(const std::vector<std::shared_ptr<Pln_Edge>>& edges)
	{
		auto iter = edges.begin();
		auto b = (*iter)->BoundingBox(0);
		iter++;
		while (iter NOT_EQUAL edges.end())
		{
			b = Geo_BoxTools::Union((*iter)->BoundingBox(0), b);
			iter++;
		}
		return std::move(b);
	}

	auto retrieveMergedEdges(const std::vector<std::shared_ptr<Pln_Edge>>& edges)
	{
		const auto b = calcBoundingBox(edges);
		const auto d = b.Diameter();

		const auto minTol = d * myMinTol;
		const auto maxTol = d * myMaxTol;

		const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(edges, minTol, maxTol);
		return std::move(mergedEdges);
	}

	void execute()
	{
		//Cad2d_RemoveNonManifold::verbose = 2;
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& sections = mySections->GetSections();

		mySegments.reserve(sections.size());
		size_t k = 0;
		for (const auto& x : sections)
		{
			auto edges = retrieveMergedEdges(x->Edges());
			auto cmpEdges = retrieveCmpEdges(edges);
			auto cmpEdges_ptr = std::make_shared<std::vector<segment_t>>(std::move(cmpEdges));

			if (verbose)
			{
				Info << " - compound edges of the section nb. " << k++ << " has been calculated." << endl;
				if (verbose > 1) Info << "   Nb. of edges: " << cmpEdges_ptr->size() << endl;
				if (verbose > 1)
				{
					auto manifold = true;
					for (const auto& e : *cmpEdges_ptr)
					{
						if (!e->IsRing())
						{
							manifold = false;
							break;
						}
					}
					Info << "   The manifold criterion: " << (manifold ? "PASSED" : "FAILED") << endl << endl;
				}
			}

			mySegments.push_back(std::move(cmpEdges_ptr));
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

		//- settings
		mod->add(chaiscript::fun([](double x)-> void {setMinTol(x); }), "setMinTol");
		mod->add(chaiscript::fun([](double x)-> void {setMaxTol(x); }), "setMaxTol");
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
	FatalError.dontThrowExceptions();

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
			Info << " This application is aimed to analyze the sections." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1, 2" << endl
				<< " - setMinTol(double);" << endl
				<< " - setMaxTol(double);" << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hydstcSectionAnalysis");

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