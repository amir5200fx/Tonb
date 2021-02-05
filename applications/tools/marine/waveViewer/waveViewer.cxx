#include <Entity3d_Box.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Cad_PreviewTools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Models.hxx>
#include <StbGMaker_Model.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_Wave> wave_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;
	typedef std::shared_ptr<StbGMaker_Model> stbModel_t;

	static size_t verbose = 0;

	static wave_t myWave;

	enum class tessellation
	{
		low,
		medium,
		high
	};

	static tessellation level;

	void loadWave(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file: " << fn << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);
		//ia >> myWave;
		Marine_Wave::Load(ia, myWave);

		if (NOT myWave)
		{
			FatalErrorIn(FunctionSIG)
				<< " the wave is null" << endl
				<< abort(FatalError);
		}

		if (NOT myWave->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the wave algorithm is not performed!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " the wave is loaded from: " << fn << ",successfully!" << endl;
		}
	}

	void setDegree(const std::string& t)
	{
		if (t IS_EQUAL "low")
		{
			level = tessellation::low;
		}
		else if (t IS_EQUAL "medium")
		{
			level = tessellation::medium;
		}
		else if (t IS_EQUAL "high")
		{
			level = tessellation::high;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified level of tessellation" << endl
				<< abort(FatalError);
		}
	}

	void exportToPlt(const std::string& name)
	{
		fileName fn(name);
		OFstream f(fn);

		auto tri = Cad_PreviewTools::Box(*myWave->Domain()->Dim());
		if (tri) tri->ExportToPlt(f);

		const auto& geom = myWave->SurfaceGeometry();

		switch (level)
		{
		case tnbLib::tessellation::low:
		{
			auto tri = Cad_Tools::Triangulation(geom, 15, 15);
			tri->ExportToPlt(f);
			break;
		}
		case tnbLib::tessellation::medium:
		{
			auto tri = Cad_Tools::Triangulation(geom, 25, 25);
			tri->ExportToPlt(f);
			break;
		}
		case tnbLib::tessellation::high:
		{
			auto tri = Cad_Tools::Triangulation(geom, 40, 40);
			tri->ExportToPlt(f);
			break;
		}
		default:
			break;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadWave(name); }), "loadWave");
		mod->add(chaiscript::fun([](const std::string& name)->void {exportToPlt(name); }), "exportToPlt");

		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");	
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

			fileName myFileName("TnbWaveViewer");

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