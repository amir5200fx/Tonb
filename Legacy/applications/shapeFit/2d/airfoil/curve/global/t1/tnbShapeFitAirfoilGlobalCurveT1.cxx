#include <PtdShapeFit2d_AirfoilGlobal_t1.hxx>
#include <Geo_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit_Section> mySection;
	static Dir2d myDir(1.0, 0.0);

	static auto xo = std::make_pair(0.0, 0.0);
	static auto yo = std::make_pair(0.0, 0.0);

	static auto noseAngle = std::make_pair(0.0, 0.0);

	static auto chordLen = std::make_pair(1.0, 1.0);

	static auto upperMax = std::make_pair(1.0, 1.0);
	static auto upperMaxLoc = std::make_pair(10.0, 10.0);
	static auto upperNoseTight = std::make_pair(0.5, 0.5);
	static auto upperMaxTight = std::make_pair(0.5, 0.5);
	static auto upperTrailAngle = std::make_pair(30.0, 30.0);
	static auto upperMaxVel = std::make_pair(0.5, 0.5);
	static auto upperTrailVel = std::make_pair(0.5, 0.5);

	static auto lowerMax = std::make_pair(1.0, 1.0);
	static auto lowerMaxLoc = std::make_pair(10.0, 10.0);
	static auto lowerNoseTight = std::make_pair(0.5, 0.5);
	static auto lowerMaxTight = std::make_pair(0.5, 0.5);
	static auto lowerTrailAngle = std::make_pair(30.0, 30.0);
	static auto lowerMaxVel = std::make_pair(0.5, 0.5);
	static auto lowerTrailVel = std::make_pair(0.5, 0.5);

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

	void setNoseAngle(double lower, double upper)
	{
		noseAngle = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the nose angle is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setChordLen(double lower, double upper)
	{
		chordLen = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the chord length is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperMax(double lower, double upper)
	{
		upperMax = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperMax is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperMaxLoc(double lower, double upper)
	{
		upperMaxLoc = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperMaxLoc is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperNoseTight(double lower, double upper)
	{
		upperNoseTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperNoseTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperMaxTight(double lower, double upper)
	{
		upperMaxTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperMaxTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperTrailAngle(double lower, double upper)
	{
		upperTrailAngle = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the upperTrailAngle is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperMaxVel(double lower, double upper)
	{
		upperMaxVel = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperMaxVel is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperTrailVel(double lower, double upper)
	{
		upperTrailVel = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperTrailVel is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerMax(double lower, double upper)
	{
		lowerMax = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerMax is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerMaxLoc(double lower, double upper)
	{
		lowerMaxLoc = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerMaxLoc is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerNoseTight(double lower, double upper)
	{
		lowerNoseTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerNoseTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerMaxTight(double lower, double upper)
	{
		lowerMaxTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerMaxTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerTrailAngle(double lower, double upper)
	{
		lowerTrailAngle = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the lowerTrailAngle is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerMaxVel(double lower, double upper)
	{
		lowerMaxVel = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerMaxVel is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerTrailVel(double lower, double upper)
	{
		lowerTrailVel = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerTrailVel is set to: " << endl
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

	void saveTo()
	{
		saveTo("");
	}

	void execute()
	{
		auto myXo = curveLib::airfoilLib::Global_t1::CreateXo(xo.first, xo.second);
		auto myYo = curveLib::airfoilLib::Global_t1::CreateYo(yo.first, yo.second);

		auto myNoseAngle = curveLib::airfoilLib::Global_t1::CreateNoseAngle(noseAngle.first, noseAngle.second);

		auto myChordLen = curveLib::airfoilLib::Global_t1::CreateChordLen(chordLen.first, chordLen.second);

		auto myUpperMax = curveLib::airfoilLib::Global_t1::CreateUpperMax(upperMax.first, upperMax.second);
		auto myUpperMaxLoc = curveLib::airfoilLib::Global_t1::CreateUpperMaxLoc(upperMaxLoc.first, upperMaxLoc.second);
		auto myUpperNoseTight = curveLib::airfoilLib::Global_t1::CreateUpperNoseTight(upperNoseTight.first, upperNoseTight.second);
		auto myUpperMaxTight = curveLib::airfoilLib::Global_t1::CreateUpperMaxTight(upperMaxTight.first, upperMaxTight.second);
		auto myUpperMaxVel = curveLib::airfoilLib::Global_t1::CreateUpperMaxVel(upperMaxVel.first, upperMaxVel.second);
		auto myUpperTrailAngle = curveLib::airfoilLib::Global_t1::CreateUpperTrailAngle(upperTrailAngle.first, upperTrailAngle.second);
		auto myUpperTrailVel = curveLib::airfoilLib::Global_t1::CreateUpperTrailVel(upperTrailVel.first, upperTrailVel.second);

		auto myLowerMax = curveLib::airfoilLib::Global_t1::CreateLowerMax(lowerMax.first, lowerMax.second);
		auto myLowerMaxLoc = curveLib::airfoilLib::Global_t1::CreateLowerMaxLoc(lowerMaxLoc.first, lowerMaxLoc.second);
		auto myLowerNoseTight = curveLib::airfoilLib::Global_t1::CreateLowerNoseTight(lowerNoseTight.first, lowerNoseTight.second);
		auto myLowerMaxTight = curveLib::airfoilLib::Global_t1::CreateLowerMaxTight(lowerMaxTight.first, lowerMaxTight.second);
		auto myLowerMaxVel = curveLib::airfoilLib::Global_t1::CreateLowerMaxVel(lowerMaxVel.first, lowerMaxVel.second);
		auto myLowerTrailAngle = curveLib::airfoilLib::Global_t1::CreateLowerTrailAngle(lowerTrailAngle.first, lowerTrailAngle.second);
		auto myLowerTrailVel = curveLib::airfoilLib::Global_t1::CreateLowerTrailVel(lowerTrailVel.first, lowerTrailVel.second);

		auto sect = std::make_shared<curveLib::airfoilLib::Global_t1>();

		sect->SetDir(myDir);

		sect->SetXo(myXo);
		sect->SetYo(myYo);

		sect->SetNoseAngle(myNoseAngle);

		sect->SetChordLen(myChordLen);

		sect->SetUpperMax(myUpperMax);
		sect->SetUpperMaxLoc(myUpperMaxLoc);
		sect->SetUpperNoseTight(myUpperNoseTight);
		sect->SetUpperMaxTight(myUpperMaxTight);
		sect->SetUpperTrailAngle(myUpperTrailAngle);
		sect->SetUpperMaxVel(myUpperMaxVel);
		sect->SetUpperTrailVel(myUpperTrailVel);

		sect->SetLowerMax(myLowerMax);
		sect->SetLowerMaxLoc(myLowerMaxLoc);
		sect->SetLowerNoseTight(myLowerNoseTight);
		sect->SetLowerMaxTight(myLowerMaxTight);
		sect->SetLowerTrailAngle(myLowerTrailAngle);
		sect->SetLowerMaxVel(myLowerMaxVel);
		sect->SetLowerTrailVel(myLowerTrailVel);

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

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setNoseAngle(lower, upper); }), "setNoseAngle");
		mod->add(chaiscript::fun([](double x)-> void {setNoseAngle(x, x); }), "setNoseAngle");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setChordLen(lower, upper); }), "setChordLen");
		mod->add(chaiscript::fun([](double x)-> void {setChordLen(x, x); }), "setChordLen");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMax(lower, upper); }), "setUpperMax");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMax(x, x); }), "setUpperMax");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMaxLoc(lower, upper); }), "setUpperMaxLoc");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMaxLoc(x, x); }), "setUpperMaxLoc");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperNoseTight(lower, upper); }), "setUpperNoseTight");
		mod->add(chaiscript::fun([](double x)-> void {setUpperNoseTight(x, x); }), "setUpperNoseTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMaxTight(lower, upper); }), "setUpperMaxTight");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMaxTight(x, x); }), "setUpperMaxTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperTrailAngle(lower, upper); }), "setUpperTrailAngle");
		mod->add(chaiscript::fun([](double x)-> void {setUpperTrailAngle(x, x); }), "setUpperTrailAngle");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMaxVel(lower, upper); }), "setUpperMaxVel");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMaxVel(x, x); }), "setUpperMaxVel");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperTrailVel(lower, upper); }), "setUpperTrailVel");
		mod->add(chaiscript::fun([](double x)-> void {setUpperTrailVel(x, x); }), "setUpperTrailVel");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMax(lower, upper); }), "setLowerMax");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMax(x, x); }), "setLowerMax");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMaxLoc(lower, upper); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMaxLoc(x, x); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerNoseTight(lower, upper); }), "setLowerNoseTight");
		mod->add(chaiscript::fun([](double x)-> void {setLowerNoseTight(x, x); }), "setLowerNoseTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMaxTight(lower, upper); }), "setLowerMaxTight");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMaxTight(x, x); }), "setLowerTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerTrailAngle(lower, upper); }), "setLowerTrailAngle");
		mod->add(chaiscript::fun([](double x)-> void {setLowerTrailAngle(x, x); }), "setLowerTrailAngle");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMaxVel(lower, upper); }), "setLowerMaxVel");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMaxVel(x, x); }), "setLowerMaxVel");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerTrailVel(lower, upper); }), "setLowerTrailVel");
		mod->add(chaiscript::fun([](double x)-> void {setLowerTrailVel(x, x); }), "setLowerTrailVel");

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
			Info << " This application is aimed to create a global parametric airfoil curve for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl
				<< " - printTypes()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setDir(u, v)" << endl << endl

				<< " - setXo(lower, upper [optional])" << endl
				<< " - setYo(lower, upper [optional])" << endl << endl

				<< " - setNoseAngle(lower, upper [optional])" << endl << endl

				<< " - setChordLen(lower, upper [optional])" << endl << endl

				<< " - setUpperMax(lower, upper [optional])" << endl
				<< " - setUpperMaxLoc(lower, upper [optional])" << endl
				<< " - setUpperNoseTight(lower, upper [optional])" << endl
				<< " - setUpperMaxNose(lower, upper [optional])" << endl
				<< " - setUpperTrailAngle(lower, upper [optional])" << endl
				<< " - setUpperMaxVel(lower, upper [optional])" << endl
				<< " - setUpperTrailAngle(lower, upper [optional])" << endl << endl

				<< " - setLowerMax(lower, upper [optional])" << endl
				<< " - setLowerMaxLoc(lower, upper [optional])" << endl
				<< " - setLowerNoseTight(lower, upper [optional])" << endl
				<< " - setLowerMaxNose(lower, upper [optional])" << endl
				<< " - setLowerTrailAngle(lower, upper [optional])" << endl
				<< " - setLowerMaxVel(lower, upper [optional])" << endl
				<< " - setLowerTrailAngle(lower, upper [optional])" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbShapeFitAirfoilGlobalCurveT1"));
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