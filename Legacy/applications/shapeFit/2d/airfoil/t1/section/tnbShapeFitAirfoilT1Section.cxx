#include <PtdShapeFit2d_Airfoil_t1.hxx>
#include <PtdShapeFit_Par.hxx>
#include <Dir2d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Section> mySection;

	static Dir2d myDir(1.0, 0.0);

	static auto xo = std::make_pair(0.0, 0.0);
	static auto yo = std::make_pair(0.0, 0.0);

	static auto chordlen = std::make_pair(0.75, 1.25);

	static auto maxCamb = std::make_pair(0.01, 0.04);
	static auto maxCambLoc = std::make_pair(0.2, 0.5);

	static auto leadCambSteep = std::make_pair(0.5, 0.99);
	static auto leadCambSteepTight = std::make_pair(0.5, 0.99);
	static auto leadCambSteepWeight = std::make_pair(1.0, 1.0);

	static auto trailCambSteep = std::make_pair(0.2, 0.99);
	static auto trailCambSteepTight = std::make_pair(0.5, 0.99);
	static auto trailCambSteepWeight = std::make_pair(1.0, 1.0);

	static auto maxThick = std::make_pair(0.15, 0.22);
	static auto maxThickLoc = std::make_pair(0.2, 0.5);

	static auto leadThickSteep = std::make_pair(0.5, 0.99);
	static auto leadThickSteepTight = std::make_pair(0.5, 0.99);
	static auto leadThickSteepWeight = std::make_pair(1.0, 1.0);

	static auto trailThickSteep = std::make_pair(0.2, 0.99);
	static auto trailThickSteepTight = std::make_pair(0.5, 0.99);
	static auto trailThickSteepWeight = std::make_pair(1.0, 1.0);

	static unsigned short verbose = 0;
	static auto exeTag = false;

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

	void setMaxCamb(double lower, double upper)
	{
		maxCamb = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the max camber is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setMaxCambLoc(double lower, double upper)
	{
		maxCambLoc = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the max camber loc. is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadCambSteep(double lower, double upper)
	{
		leadCambSteep = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading camber steep is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadCambSteepTight(double lower, double upper)
	{
		leadCambSteepTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading camber steep tightness is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadCambSteepWeight(double lower, double upper)
	{
		leadCambSteepWeight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading camber steep weight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailCambSteep(double lower, double upper)
	{
		trailCambSteep = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing camber steep is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailCambSteepTight(double lower, double upper)
	{
		trailCambSteepTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing camber steep tightness is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailCambSteepWeight(double lower, double upper)
	{
		trailCambSteepWeight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thickness steep weight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setMaxThick(double lower, double upper)
	{
		maxThick = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the max thickness is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setMaxThickLoc(double lower, double upper)
	{
		maxThickLoc = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the max thickness loc. is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadThickSteep(double lower, double upper)
	{
		leadThickSteep = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading thickness steep is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadThickSteepTight(double lower, double upper)
	{
		leadThickSteepTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading thickness steep tightness is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLeadThickSteepWeight(double lower, double upper)
	{
		leadThickSteepWeight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the leading thickness steep weight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailThickSteep(double lower, double upper)
	{
		trailThickSteep = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thickness steep is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailThickSteepTight(double lower, double upper)
	{
		trailThickSteepTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thickness steep tightness is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setTrailThickSteepWeight(double lower, double upper)
	{
		trailThickSteepWeight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thickness steep weight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
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
		auto myXo = airfoilLib::Type1::CreateXo(xo.first, xo.second);
		auto myYo = airfoilLib::Type1::CreateYo(yo.first, yo.second);

		auto myChord = airfoilLib::Type1::CreateChordLen(chordlen.first, chordlen.second);

		auto myMaxCamb = airfoilLib::Type1::CreateMaxCamb(maxCamb.first, maxCamb.second);
		auto myMaxCambLoc = airfoilLib::Type1::CreateMaxCambLoc(maxCambLoc.first, maxCambLoc.second);

		auto myLeadCambSteep = airfoilLib::Type1::CreateLeadCambSteep(leadCambSteep.first, leadCambSteep.second);
		auto myLeadCambSteepTight = airfoilLib::Type1::CreateLeadCambSteepTight(leadCambSteepTight.first, leadCambSteepTight.second);
		auto myLeadCambSteepWeight = airfoilLib::Type1::CreateLeadCambSteepWeight(leadCambSteepWeight.first, leadCambSteepWeight.second);

		auto myTrailCambSteep = airfoilLib::Type1::CreateTrailCambSteep(trailCambSteep.first, trailCambSteep.second);
		auto myTrailCambSteepTight = airfoilLib::Type1::CreateTrailCambSteepTight(trailCambSteepTight.first, trailCambSteepTight.second);
		auto myTrailCambSteepWeight = airfoilLib::Type1::CreateTrailCambSteepWeight(trailCambSteepWeight.first, trailCambSteepWeight.second);

		auto myMaxThick = airfoilLib::Type1::CreateMaxThick(maxThick.first, maxThick.second);
		auto myMaxThickLoc = airfoilLib::Type1::CreateMaxThickLoc(maxThickLoc.first, maxThickLoc.second);

		auto myLeadThickSteep = airfoilLib::Type1::CreateLeadThickSteep(leadThickSteep.first, leadThickSteep.second);
		auto myLeadThickSteepTight = airfoilLib::Type1::CreateLeadThickSteepTight(leadThickSteepTight.first, leadThickSteepTight.second);
		auto myLeadThickSteepWeight = airfoilLib::Type1::CreateLeadThickSteepWeight(leadThickSteepWeight.first, leadThickSteepWeight.second);

		auto myTrailThickSteep = airfoilLib::Type1::CreateTrailThickSteep(trailThickSteep.first, trailThickSteep.second);
		auto myTrailThickSteepTight = airfoilLib::Type1::CreateTrailThickSteepTight(trailThickSteepTight.first, trailThickSteepTight.second);
		auto myTrailThickSteepWeight = airfoilLib::Type1::CreateTrailThickSteepWeight(trailThickSteepWeight.first, trailThickSteepWeight.second);

		auto sect = std::make_shared<airfoilLib::Type1>();
		
		sect->SetDir(myDir);

		sect->SetXo(std::move(myXo));
		sect->SetYo(std::move(myYo));

		sect->SetChordLen(std::move(myChord));

		sect->SetMaxCamb(std::move(myMaxCamb));
		sect->SetMaxCambLoc(std::move(myMaxCambLoc));

		sect->SetLeadCambSteep(std::move(myLeadCambSteep));
		sect->SetLeadCambSteepTight(std::move(myLeadCambSteepTight));
		sect->SetLeadCambSteepWeight(std::move(myLeadCambSteepWeight));

		sect->SetTrailCambSteep(std::move(myTrailCambSteep));
		sect->SetTrailCambSteepTight(std::move(myTrailCambSteepTight));
		sect->SetTrailCambSteepWeight(std::move(myTrailCambSteepWeight));

		sect->SetMaxThick(std::move(myMaxThick));
		sect->SetMaxThickLoc(std::move(myMaxThickLoc));

		sect->SetLeadThickSteep(std::move(myLeadThickSteep));
		sect->SetLeadThickSteepTight(std::move(myLeadThickSteepTight));
		sect->SetLeadThickSteepWeight(std::move(myLeadThickSteepWeight));

		sect->SetTrailThickSteep(std::move(myTrailThickSteep));
		sect->SetTrailThickSteepTight(std::move(myTrailThickSteepTight));
		sect->SetTrailThickSteepWeight(std::move(myTrailThickSteepWeight));

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
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setYo(lower, upper); }), "setYo");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setChord(lower, upper); }), "setChord");
		
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setMaxCamb(lower, upper); }), "setMaxCamb");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setMaxCambLoc(lower, upper); }), "setMaxCambLoc");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadCambSteep(lower, upper); }), "setLeadCambSteep");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadCambSteepTight(lower, upper); }), "setLeadCambSteepTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadCambSteepWeight(lower, upper); }), "setLeadCambSteepWeight");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailCambSteep(lower, upper); }), "setTrailCambSteep");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailCambSteepTight(lower, upper); }), "setTrailCambSteepTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailCambSteepWeight(lower, upper); }), "setTrailCambSteepWeight");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setMaxThick(lower, upper); }), "setMaxThick");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setMaxThickLoc(lower, upper); }), "setMaxThickLoc");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadThickSteep(lower, upper); }), "setLeadThickSteep");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadThickSteepTight(lower, upper); }), "setLeadThickSteepTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLeadThickSteepWeight(lower, upper); }), "setLeadThickSteepWeight");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailThickSteep(lower, upper); }), "setTrailThickSteep");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailThickSteepTight(lower, upper); }), "setTrailThickSteepTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setTrailThickSteepWeight(lower, upper); }), "setTrailThickSteepWeight");

		mod->add(chaiscript::fun([](double u, double v) -> void {setDir(u, v); }), "setDir");

		// operators [2/10/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
			Info << " This application is aimed to create a type1 airfoil parametric shape for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setDir(u, v)" << endl << endl

				<< " - setXo(lower, upper)" << endl
				<< " - setYo(lower, upper)" << endl << endl

				<< " - setChord(lower, upper)" << endl << endl

				<< " - setMaxCamb(lower, upper)" << endl
				<< " - setMaxCambLoc(lower, upper)" << endl << endl

				<< " - setLeadCambSteep(lower, upper)" << endl
				<< " - setLeadCambSteepTight(lower, upper)" << endl
				<< " - setLeadCambSteepWeight(lower, upper)" << endl << endl

				<< " - setTrailCambSteep(lower, upper)" << endl
				<< " - setTrailCambSteepTight(lower, upper)" << endl
				<< " - setTrailCambSteepWeight(lower, upper)" << endl << endl

				<< " - setMaxThick(lower, upper)" << endl
				<< " - setMaxThickLoc(lower, upper)" << endl << endl

				<< " - setLeadThickSteep(lower, upper)" << endl
				<< " - setLeadThickSteepTight(lower, upper)" << endl
				<< " - setLeadThickSteepWeight(lower, upper)" << endl << endl

				<< " - setTrailThickSteep(lower, upper)" << endl
				<< " - setTrailThickSteepTight(lower, upper)" << endl
				<< " - setTrailThickSteepWeight(lower, upper)" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbShapeFitAirfoilT1Section"));
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