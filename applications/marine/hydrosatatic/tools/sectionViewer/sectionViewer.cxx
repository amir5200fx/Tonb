#include <Global_Timer.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_Tools.hxx>
#include <Pnt3d.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Cad_Tools.hxx>
#include <Marine_SectionsIO.hxx>
#include <Marine_ShapeIO.hxx>
#include <Marine_PlnCurves.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <fstream>

namespace tnbLib
{

	static unsigned short verbose(0);

	static bool loadTag = false;

	static std::shared_ptr<marineLib::io::Sections> mySections;

	static int mySection = -1;
	static std::string sModel = "union";

	void selectSection(int i)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded yet!" << endl
				<< abort(FatalError);
		}
		const auto& sections = mySections->GetSections();
		mySection = (i < 0 ? 0 : i);
		mySection = (i > sections.size() ? (int)sections.size() : i);
		if (verbose)
		{
			Info << endl
				<< " - section nb. " << mySection << " has been selected." << endl;
		}
		sModel = "section";
	}

	void printNbSections()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded, yet!" << endl
				<< abort(FatalError);
		}
		Info << endl
			<< " - nb. of sections: " << mySections->GetSections().size() << endl;
	}

	void setType(const std::string& name)
	{
		sModel = name;
		if (verbose)
		{
			Info << endl
				<< " - application mode is set to: " << sModel << endl;
		}
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

	auto getChain3d(const Entity2d_Chain& chain, double coord)
	{
		auto chain3d = std::make_shared<Entity3d_Chain>();
		chain3d->Connectivity() = chain.Connectivity();
		auto& pts = chain3d->Points();
		pts.reserve(chain.NbPoints());
		for (const auto& x : chain.Points())
		{
			auto pt = Pnt3d(coord, x.X(), x.Y());
			pts.push_back(std::move(pt));
		}
		return std::move(chain3d);
	}

	auto getSectionMesh(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges, double x)
	{
		if (theEdges.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "the list is empty!" << endl
				<< abort(FatalError);
		}
		auto chain = std::make_shared<Entity2d_Chain>();
		for (const auto& x : theEdges)
		{
			chain->Add(*Pln_Tools::RetrieveTriangulation(*x));
		}

		auto chain3d = getChain3d(*chain, x);
		return std::move(chain3d);
	}

	auto getSections(const std::vector<std::shared_ptr<marineLib::io::Sections::Section>>& sections)
	{
		std::vector<std::shared_ptr<Entity3d_Chain>> chains;
		for (const auto& x : sections)
		{
			auto sect = getSectionMesh(x->Edges(), x->X());
			chains.push_back(std::move(sect));
		}
		return std::move(chains);
	}

	auto mergeChains(const std::vector<std::shared_ptr<Entity3d_Chain>>& chains)
	{
		auto chain = std::make_shared<Entity3d_Chain>();
		for (const auto& x : chains)
		{
			chain->Add(*x);
		}
		return std::move(chain);
	}

	auto getCorners(const Entity3d_Box& b)
	{
		std::vector<Pnt3d> pts;
		pts.reserve(8);

		pts.push_back(b.Corner(Box3d_PickAlgorithm_Aft_NE));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Aft_NW));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Aft_SE));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Aft_SW));

		pts.push_back(b.Corner(Box3d_PickAlgorithm_Fwd_NE));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Fwd_NW));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Fwd_SE));
		pts.push_back(b.Corner(Box3d_PickAlgorithm_Fwd_SW));

		return std::move(pts);
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no model has been loaded yet!" << endl
				<< abort(FatalError);
		}

		const auto& sections = mySections->GetSections();


		if (sModel IS_EQUAL "union")
		{
			auto edges = getSections(sections);
			auto chain = mergeChains(edges);

			auto tri = Geo_Tools::Triangulation(*chain);

			fileName fn(name);
			std::ofstream myFile(fn);

			TNB_oARCH_FILE_TYPE ar(myFile);
			ar << tri;

			myFile.close();

			if (verbose)
			{
				Info << endl;
				Info << " the file is saved in: " << fn << ", successfully!" << endl;
				Info << endl;
			}
		}
		else if (sModel IS_EQUAL "list")
		{
			auto edges = getSections(sections);

			size_t i = 0;
			for (const auto& x : edges)
			{
				std::string address = ".\\" + std::to_string(i) + "\\" + name;
				boost::filesystem::path dir(std::to_string(i));
				boost::filesystem::create_directory(dir);

				std::ofstream file(address);

				auto tri = Geo_Tools::Triangulation(*x);

				TNB_oARCH_FILE_TYPE oa(file);

				oa << tri;

				file.close();

				if (verbose)
				{
					Info << " section, " << i << " saved in: " << address << ", successfully!" << endl;
				}
				i++;
			}
			if (verbose)
			{
				Info << endl;
				Info << " all sections have been saved, successfully!" << endl;
				Info << endl;
			}
		}
		else if (sModel IS_EQUAL "section")
		{
			auto chain = getSectionMesh(sections[mySection]->Edges(), sections[mySection]->X());

			auto tri = Geo_Tools::Triangulation(*chain);

			const auto& b = *mySections->GetShape()->PreciseBndBox();
			auto corners = getCorners(b);

			auto& pts = tri->Points();
			for (const auto& x : corners)
			{
				pts.push_back(x);
			}

			fileName fn(name);
			std::ofstream myFile(fn);

			TNB_oARCH_FILE_TYPE ar(myFile);
			ar << tri;

			myFile.close();

			if (verbose)
			{
				Info << endl;
				Info << " the file is saved in: " << fn << ", successfully!" << endl;
				Info << endl;
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid application mode has been detected!" << endl
				<< " - application modes: union, list" << endl
				<< abort(FatalError);
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
		mod->add(chaiscript::fun([](int i)->void {selectSection(i); }), "selectSection");
		mod->add(chaiscript::fun([](const std::string& name)->void {setType(name); }), "setType");
		mod->add(chaiscript::fun([]()-> void {printNbSections(); }), "printNbSections");

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
			Info << " This application is aimed to retrieve the mesh from the shape." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setType(string);             - types: union, list" << endl
				<< " - selectSection(int)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - printNbSections()" << endl << endl

				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hydstcSectionViewer");

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