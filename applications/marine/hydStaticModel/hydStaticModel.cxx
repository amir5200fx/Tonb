#include <Entity2d_Polygon.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Cad_Tools.hxx>
#include <Cad_PreviewTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Section.hxx>
#include <StbGMaker_Model.hxx>
#include <HydStatic_Model.hxx>
#include <HydStatic_FloatBody.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	static auto hydrModel = std::make_shared<HydStatic_Model>();

	typedef std::shared_ptr<StbGMaker_Model> stbModel_t;
	typedef std::shared_ptr<Marine_Wave> wave_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	static stbModel_t myModel;
	static wave_t myWave;

	static size_t verbose = 0;
	static bool loadTag = false;

	void perform()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the wave is not loaded!" << endl
				<< abort(FatalError);
		}
		hydrModel->LoadModel(myModel);
		hydrModel->LoadWave(myWave);
		hydrModel->Perform();

		if (verbose)
		{
			Info << " the hydrostatic model is created, successfully!" << endl;
		}
	}


	//- io functions

	void loadModel(const std::string& name)
	{
		fileName myFileName(name);
		std::ifstream myFile(myFileName);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myModel;
		ar >> myWave;

		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< " the model is null" << endl
				<< abort(FatalError);
		}

		if (NOT myWave)
		{
			FatalErrorIn(FunctionSIG)
				<< " the wave is null" << endl
				<< abort(FatalError);
		}

		if (NOT myWave->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< " the wave algorithm is not performed!" << endl
				<< abort(FatalError);
		}

		loadTag = true;

		if (verbose)
		{
			Info << " the wave is loaded, successfully!" << endl;
		}
	}

	void saveModelTo(const std::string& name)
	{
		fileName myFileName(name);
		std::ofstream myFile(myFileName);

		boost::archive::polymorphic_text_oarchive ar(myFile);

		if (NOT hydrModel->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		ar << hydrModel;

		if (verbose)
		{
			Info << " the hydrostatic model is saved in: " << myFileName << ", successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadWave");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveModelTo(name); }), "saveTo");

		mod->add(chaiscript::fun([]()-> void {perform(); }), "execute");

		mod->add(chaiscript::fun([](unsigned short i)-> void {HydStatic_Model::verbose = i; }), "setVerbose");
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

	//hydrModel = std::make_shared<HydStatic_Model>();
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

			fileName myFileName("hydStaticModel");

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