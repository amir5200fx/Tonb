#include <HydStatic_SolutionData_Coeffs.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Models.hxx>
#include <Marine_BodyTools.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_Wave> wave_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;
	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;

	static unsigned short verbose(0);

	static soluData_t mySolutionData;

	static unsigned int Nx = 40;
	static unsigned int Ny = 40;

	enum class tessellation
	{
		low,
		medium,
		high,
		custom
	};

	static tessellation level;

	void setLevel(const std::string& name)
	{
		if (name IS_EQUAL "low")
		{
			level = tessellation::low;
		}
		else if (name IS_EQUAL "medium")
		{
			level = tessellation::medium;
		}
		else if (name IS_EQUAL "high")
		{
			level = tessellation::high;
		}
		else if (name IS_EQUAL "custom")
		{
			level = tessellation::custom;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified tessellation mode has been found!" << endl
				<< " please make sure you've selected a valid mode:" << endl
				<< " - low" << endl
				<< " - medium" << endl
				<< " - high" << endl
				<< " - custom" << endl
				<< abort(FatalError);
		}
	}

	void loadModel(const std::string& name)
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

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::wave))
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is not updated" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}

	}

	void saveTo(const std::string& name)
	{
		auto tris = std::make_shared<Entity3d_Triangulation>();
		const auto& wave = mySolutionData->Wave();
		if (NOT wave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wave has been found!" << endl
				<< abort(FatalError);
		}

		auto triDomain = Cad_PreviewTools::Box(*wave->Domain()->Dim());
		//auto& triRef = *tri;
		//tris->Add(std::move(triRef));

		const auto& geom = wave->SurfaceGeometry();
		if (NOT geom)
		{
			FatalErrorIn(FunctionSIG)
				<< "no surface geometry has been found!" << endl
				<< abort(FatalError);
		}

		const auto& body = mySolutionData->Hull();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		auto chain = Marine_BodyTools::RetrieveTriangulations(*body);
		if (NOT chain)
		{
			FatalErrorIn(FunctionSIG)
				<< "the body has no mesh!" << endl
				<< abort(FatalError);
		}

		auto mesh = Geo_Tools::Triangulation(*chain);
		auto& meshRef = *mesh;
		tris->Add(std::move(meshRef));

		switch (level)
		{
		case tnbLib::tessellation::low:
		{
			auto tri = Cad_Tools::Triangulation(geom, 15, 15);
			auto& triRef = *tri;
			tris->Add(std::move(triRef));
			break;
		}
		case tnbLib::tessellation::medium:
		{
			auto tri = Cad_Tools::Triangulation(geom, 25, 25);
			auto& triRef = *tri;
			tris->Add(std::move(triRef));
			break;
		}
		case tnbLib::tessellation::high:
		{
			auto tri = Cad_Tools::Triangulation(geom, 40, 40);
			auto& triRef = *tri;
			tris->Add(std::move(triRef));
			break;
		}
		case tnbLib::tessellation::custom:
		{
			auto tri = Cad_Tools::Triangulation(geom, Nx, Ny);
			auto& triRef = *tri;
			tris->Add(std::move(triRef));
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified tessellation mode has been found!" << endl
				<< abort(FatalError);
			break;
		}

		auto& pts = tris->Points();
		for (const auto& x : triDomain->Points())
		{
			pts.push_back(x);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << tris;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the mesh is saved in: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {setLevel(name); }), "setLevel");
		mod->add(chaiscript::fun([](unsigned int nx, unsigned int ny)-> void {Nx = nx; Ny = ny; }), "setCustomLevel");
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\hullDataWaveViewer";
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}