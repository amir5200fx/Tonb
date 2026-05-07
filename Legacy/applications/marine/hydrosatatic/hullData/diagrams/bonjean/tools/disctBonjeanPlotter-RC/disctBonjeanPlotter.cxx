#include <HydStatic_SolutionData_Bonjean.hxx>
#include <HydStatic_BonjeanGraph.hxx>
#include <HydStatic_BnjCurve.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <Pln_Tools.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>
#include <Bnd_Box2d.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Bonjean> soluData_t;
	typedef std::shared_ptr<Geo_ApprxCurve_Info> info_t;

	soluData_t mySolutionData;
	static auto myInfo = std::make_shared<Geo_ApprxCurve_Info>();

	static unsigned short verbose(0);

	class InfoRunTime
	{
	public:

		InfoRunTime()
		{
			config();
		}

		static void config();
	};

	void InfoRunTime::config()
	{
		myInfo->SetAngle(Geo_Tools::DegToRadian(2.0));
		myInfo->SetApprox(1.0E-3);
		myInfo->SetInitNbSubdivision(10);
		myInfo->SetMaxNbSubdivision(20);
		myInfo->SetMinSize(1.0E-4);
		myInfo->SetNbSamples(6);
	}

	static InfoRunTime myInfoRunTime;

	void setAngle(double x)
	{
		myInfo->SetAngle(Geo_Tools::DegToRadian(x));
	}

	void setApprox(double x)
	{
		myInfo->SetApprox(x);
	}

	void setNbSamples(int n)
	{
		myInfo->SetNbSamples(n);
	}

	void loadSolutionDate(const std::string& name)
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

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto calcBoundingBox(const std::vector<std::shared_ptr<HydStatic_BnjCurve>>& curves)
	{
		auto iter = curves.begin();
		auto b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox((*iter)->Geometry()));

		iter++;
		while (iter NOT_EQUAL curves.end())
		{
			b = Geo_BoxTools::Union(b, Pln_Tools::BoundingBox(Pln_Tools::BoundingBox((*iter)->Geometry())));
			iter++;
		}
		return std::move(b);
	}

	void saveTo(const std::string& name)
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& graph = mySolutionData->Graph();
		if (NOT graph)
		{
			FatalErrorIn(FunctionSIG)
				<< "no bonjean graph has been found!" << endl
				<< abort(FatalError);
		}

		const auto& sections = graph->Sections();

		auto iter = sections.begin();
		auto box = calcBoundingBox((*iter)->Curves());
		iter++;

		while (iter NOT_EQUAL sections.end())
		{
			box = Geo_BoxTools::Union(box, calcBoundingBox((*iter)->Curves()));
			iter++;
		}

		myInfo->SetApprox(box.Diameter()*myInfo->Approx());
		myInfo->SetMinSize(box.Diameter()*myInfo->MinSize());	

		size_t i = 0;
		for (const auto& section : graph->Sections())
		{		
			auto tri = std::make_shared<Entity2d_Chain>();
			for (const auto& x : section->Curves())
			{
				const auto& geom = x->Geometry();
				auto t = std::make_shared<Geo2d_ApprxCurve>(geom, geom->FirstParameter(), geom->LastParameter(), myInfo);
				t->Perform();

				const auto& poly = t->Chain();
				auto& pts = poly->Points();

				auto chain = std::make_shared<Entity2d_Chain>();
				chain->Points() = std::move(pts);
				chain->Connectivity() = dualConnectivityList_Chain(chain->NbPoints() - 1);

				auto& chainRef = *chain;
				tri->Add(std::move(chainRef));
			}

			auto mesh = Geo_Tools::Triangulation(*tri);

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);
			oa << mesh;

			if (verbose)
			{
				Info << " section's curve are saved in: " << address << ", successfully!" << endl;
			}

			++i;
		}

		myInfo->SetApprox(1.0 / box.Diameter()*myInfo->Approx());
		myInfo->SetMinSize(1.0 / box.Diameter()*myInfo->MinSize());

		if (verbose)
		{
			Info << endl;
			Info << " all curves have been saved, successfully!" << endl;
			Info << endl;
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

	void setGlobals(const module_t& mod)
	{

		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setApprox(x); }), "setApproximate");
		mod->add(chaiscript::fun([](unsigned int n)-> void {setNbSamples(n); }), "setNbSamples");
		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionDate(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](unsigned short c)-> void {verbose = c; }), "setVerbose");

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

	FatalError.throwExceptions();

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

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("hullDataDisctBonjeanPlotter");

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