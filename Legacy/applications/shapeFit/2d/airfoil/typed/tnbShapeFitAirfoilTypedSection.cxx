#include <PtdShapeFit2d_TypedAirfoil.hxx>
#include <PtdShapeFit2d_TypedAirfoil_S833Offsets.hxx>
#include <PtdShapeFit2d_TypedAirfoil_MH102Offsets.hxx>
#include <Geo_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Section> mySection;
	static std::shared_ptr<PtdShapeFit2d_TypedAirfoil_Offsets> selectedType;

	static Dir2d myDir(1.0, 0.0);

	static auto xo = std::make_pair(0.0, 0.0);
	static auto yo = std::make_pair(0.0, 0.0);
	static auto phi = std::make_pair(Geo_Tools::DegToRadian(-5.0), Geo_Tools::DegToRadian(5.0));

	static auto chordlen = std::make_pair(0.75, 1.25);

	static unsigned short verbose = 0;
	static auto exeTag = false;

	static std::map<std::string, std::shared_ptr<PtdShapeFit2d_TypedAirfoil_Offsets>>
		myOffsets;

	class myOffsetsRunTime
	{

		/*Private Data*/

		void SetConfigs();

	public:

		// default constructor [5/5/2023 Payvand]

		myOffsetsRunTime()
		{
			SetConfigs();
		}

	};

	void tnbLib::myOffsetsRunTime::SetConfigs()
	{
		{
			auto offsets = std::make_shared<airfoilLib::offsetsLib::S833>();
			myOffsets.insert({ offsets->Name(),std::move(offsets) });
		}
		{
			auto offsets = std::make_shared<airfoilLib::offsetsLib::MH102>();
			myOffsets.insert({ offsets->Name(),std::move(offsets) });
		}
	}

	static const myOffsetsRunTime myOffsetsRunTimeObj;

	void printTypes()
	{
		for (const auto& x : myOffsets)
		{
			Info << " - " << x.first << endl;
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setDir(double u, double v)
	{
		myDir.SetX(u);
		myDir.SetY(v);

		if (verbose)
		{
			Info << endl
				<< " - the direction is set to: " << u << ", " << v << endl;
		}
	}

	void setXo(double lower, double upper)
	{
		xo = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the xo is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setYo(double lower, double upper)
	{
		yo = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the yo is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setAngle(double lower, double upper)
	{
		phi = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the phi is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setChord(double lower, double upper)
	{
		chordlen = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the chord is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setType(const std::string& name)
	{
		try
		{
			selectedType = myOffsets.at(name);
		}
		catch (const std::exception&)
		{
			FatalErrorIn(FunctionSIG)
				<< "Unrecognized type of airfoil has been detected." << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << endl
				<< " - the type is set to: " << name << endl;
		}
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

		file::SaveTo(mySection, name + PtdShapeFit_Section::extension, verbose);
	}

	void execute()
	{
		auto myXo = PtdShapeFit2d_TypedAirfoil::CreateXo(xo.first, xo.second);
		auto myYo = PtdShapeFit2d_TypedAirfoil::CreateYo(yo.first, yo.second);
		auto myAngle = PtdShapeFit2d_TypedAirfoil::CreateAngle(phi.first, phi.second);

		auto myChord = PtdShapeFit2d_TypedAirfoil::CreateChordLen(chordlen.first, chordlen.second);

		auto sect = std::make_shared<PtdShapeFit2d_TypedAirfoil>();

		sect->SetDir(myDir);

		sect->SetXo(std::move(myXo));
		sect->SetYo(std::move(myYo));
		sect->SetAngle(std::move(myAngle));

		sect->SetChordLen(std::move(myChord));

		if (NOT selectedType)
		{
			FatalErrorIn(FunctionSIG)
				<< "no airfoil has been detected." << endl
				<< abort(FatalError);
		}

		sect->SetOffsets(selectedType);

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}

		mySection = std::move(sect);

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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setXo(lower, upper); }), "setXo");
		mod->add(chaiscript::fun([](double x)-> void {setXo(x, x); }), "setXo");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setYo(lower, upper); }), "setYo");
		mod->add(chaiscript::fun([](double x)-> void {setYo(x, x); }), "setYo");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setChord(lower, upper); }), "setChord");
		mod->add(chaiscript::fun([](double x)-> void {setChord(x, x); }), "setChord");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setAngle(lower, upper); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setAngle(x, x); }), "setAngle");

		mod->add(chaiscript::fun([](const std::string& name)-> void {setType(name); }), "setType");

		mod->add(chaiscript::fun([](double u, double v) -> void {setDir(u, v); }), "setDir");

		// operators [2/10/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([]()-> void {printTypes(); }), "printTypes");
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to create a specific type of airfoil parametric shape for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl
				<< " - printTypes()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setDir(u, v)" << endl << endl

				<< " - setXo(lower, upper [optional])" << endl
				<< " - setYo(lower, upper [optional])" << endl
				<< " - setAngle(lower [Deg], upper [Deg] [optional])" << endl

				<< " - setChord(lower, upper [optional])" << endl << endl

				<< " - setType(name)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitAirfoilTypedSection"));
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