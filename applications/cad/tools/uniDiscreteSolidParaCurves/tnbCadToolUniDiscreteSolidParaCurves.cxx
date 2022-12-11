#include <Cad_Shape.hxx>
#include <Cad_TModel.hxx>
#include <TModel_Surface.hxx>
#include <TModel_GeneratedEdge.hxx>
#include <TModel_Wire.hxx>
#include <TModel_ParaCurve.hxx>
#include <Pln_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Cad_TModel::extension;
	static std::string saveExt = Entity2d_Triangulation::extension + "list";

	static std::shared_ptr<Cad_TModel> myShape;
	static std::vector<std::shared_ptr<Entity2d_Triangulation>> myTris;

	static std::string myFileName;

	static unsigned short verbose(0);
	static bool loadTag = false;

	static int nbSegments = 40;
	static bool exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_TModel>>(name + loadExt, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the shape is null" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myTris, name + saveExt, verbose);
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

	auto GetPolygon(const TModel_Wire& wire)
	{
		auto chain = std::make_shared<Entity2d_Chain>();
		auto curves = *TModel_Wire::RetrieveParaCurves(wire);
		for (const auto& x : curves)
		{
			auto pl = Pln_Tools::UniformDiscrete(x->Curve(), nbSegments);
			auto iChain = Geo_Tools::RetrieveChain(*pl);
			chain->Add(*iChain);
		}
		return std::move(chain);
	}

	auto GetPatch(const TModel_Surface& theSurface)
	{
		const auto& outer = theSurface.Outer();
		auto chain = GetPolygon(*outer);
		if (theSurface.Inner())
		{
			for (const auto& x : *theSurface.Inner())
			{
				auto iChain = GetPolygon(*x);
				chain->Add(*iChain);
			}
		}
		return std::move(chain);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded" << endl
				<< abort(FatalError);
		}

		for (const auto& x : myShape->RetrieveFaces())
		{
			auto chain = GetPatch(*x);
			auto tri = Geo_Tools::Triangulation(*chain);
			myTris.push_back(std::move(tri));
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< "- the application is performed, successfully, in " << global_time_duration << " ms." << endl;
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
		// io functions [1/31/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// operators [1/31/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		// settings [1/31/2022 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
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

int main(int argc, char* argv[])
{
	FatalError.throwExceptions();
	FatalConvError.throwExceptions();

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
			Info << " This application is aimed to discretize the parametric curves of the surfaces." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				auto address = file::GetSystemFile("tnbCadToolUniDiscreteSolidParaCurves");
				fileName myFileName(address);

				chai.eval_file(myFileName);
				return 0;
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
	return 1;
}