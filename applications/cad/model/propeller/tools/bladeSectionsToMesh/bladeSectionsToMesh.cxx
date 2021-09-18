#include <PtdModel_BladeRadialSections.hxx>
#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_RadialSection.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Tools.hxx>

#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <vector>

#include <Bnd_Box2d.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static double myApprox = 1.0E-4;
	static double myMinSize = 1.0E-6;

	static std::shared_ptr<PtdModel_BladeRadialSections> myBlade;
	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myTris;

	static auto myInfo = std::make_shared<Geo_ApprxCurve_Info>();

	class SetInfoConfig_RunTime
	{

	public:

		static void init();

		SetInfoConfig_RunTime()
		{
			init();
		}
	};

	void SetInfoConfig_RunTime::init()
	{
		myInfo->SetAngle(2.0);
		myInfo->SetApprox(1.0E-4);
		myInfo->SetInitNbSubdivision(5);
		myInfo->SetMaxNbSubdivision(100);
		myInfo->SetMinSize(1.0E-6);
		myInfo->SetNbSamples(5);
	}

	static SetInfoConfig_RunTime myRunTimeConfig;
	
	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setApprox(double x)
	{
		myApprox = x;
		if (verbose)
		{
			Info << endl
				<< " - the approx. is set to: " << myApprox << endl;
		}
	}

	void setMinSize(double x)
	{
		myMinSize = x;
		if (verbose)
		{
			Info << endl
				<< " - the min. size is set to: " << myMinSize << endl;
		}
	}

	void setNbSamples(int n)
	{
		myInfo->SetNbSamples(n);
		if (verbose)
		{
			Info << endl
				<< " - the nb. of sample points is set to: " << n << endl;
		}
	}

	void setMaxNbSubdivisions(int n)
	{
		myInfo->SetMaxNbSubdivision(n);
		if (verbose)
		{
			Info << endl
				<< " - the max. nb. of subdivisions is set to: " << n << endl;
		}
	}

	void setAngle(double x)
	{
		myInfo->SetAngle(x);
		if (verbose)
		{
			Info << endl
				<< " - the angle is set to: " << x << endl;
		}
	}

	void setInitNbSubdivisions(int n)
	{
		myInfo->SetInitNbSubdivision(n);
		if (verbose)
		{
			Info << endl
				<< " - the init. nb. of subdivisions is set to: " << n << endl;
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
			ar >> myBlade;
		}

		if (NOT myBlade)
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
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		size_t i = 0;
		for (const auto& x : myTris)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			boost::archive::polymorphic_text_oarchive oa(file);

			oa << x;

			if (verbose)
			{
				Info << " the triangulation, " << i << " is saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}

		if (verbose)
		{
			Info << endl
				<< " - All triangulations are saved, successfully!" << endl;
		}
	}

	auto retrieveMesh(const Handle(Geom2d_Curve)& curve)
	{
		auto b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(curve));
		const auto d = b.Diameter();

		myInfo->SetApprox(d*myApprox);
		myInfo->SetMinSize(d*myMinSize);

		auto alg = std::make_shared<Geo2d_ApprxCurve>();
		alg->LoadCurve(curve, curve->FirstParameter(), curve->LastParameter(), myInfo);
		alg->Perform();

		const auto& poly = alg->Chain();
		auto ids = dualConnectivityList_Chain(poly->NbPoints() - 1);
		auto pts = std::move(poly->Points());

		auto chain = std::make_shared<Entity2d_Chain>(std::move(pts), std::move(ids));
		return std::move(chain);
		
	}

	auto retrieveTriMesh(const std::shared_ptr<Entity2d_Chain>& chain)
	{
		auto tri = std::make_shared<Entity2d_Triangulation>();
		tri->Points() = std::move(chain->Points());
		std::vector<connectivity::triple> ids;
		ids.reserve(chain->NbConnectivity());
		for (const auto& x : chain->Connectivity())
		{
			connectivity::triple t;
			t.Value(0) = x.Value(0);
			t.Value(1) = x.Value(1);
			t.Value(2) = x.Value(0);

			ids.push_back(std::move(t));
		}
		tri->Connectivity() = std::move(ids);
		return std::move(tri);
	}

	auto retrieveMesh(const std::shared_ptr<PtdModel_RadialSection>& section)
	{
		auto tris = std::make_shared<Entity2d_Triangulation>();
		for (const auto& c : section->Curves())
		{
			auto chain = retrieveMesh(c);
			auto tri = *retrieveTriMesh(chain);

			tris->Add(std::move(tri));
		}
		return std::move(tris);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		myTris.reserve(myBlade->Sections().size());

		if (verbose)
		{
			Info << endl;
		}

		size_t k = 0;
		for (const auto& x : myBlade->Sections())
		{
			if (verbose)
			{
				Info << " - section id: " << k++ << endl;
			}

			auto tri = retrieveMesh(x);
			myTris.push_back(std::move(tri));
		}

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setApprox(x); }), "setApprox");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "setMinSize");
		mod->add(chaiscript::fun([](int n)-> void {setNbSamples(n); }), "setNbSamples");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbSubdivisions(n); }), "setMaxNbSubdivisions");
		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](int n)-> void {setInitNbSubdivisions(n); }), "setInitNbSubdivisions");

		//- functions

		
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
			Info << " This application is aimed to discrete the curves of the blade sections." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl
				<< " - setApprox(double)" << endl
				<< " - setMinSize(double)" << endl
				<< " - setNbSamples(int)" << endl
				<< " - setMaxNbSubdivisions(int)" << endl
				<< " - setAngle(double)" << endl
				<< " - setInitNbSubdivisions(int)" << endl
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

			std::string address = ".\\system\\bladeSectionsToMesh";
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