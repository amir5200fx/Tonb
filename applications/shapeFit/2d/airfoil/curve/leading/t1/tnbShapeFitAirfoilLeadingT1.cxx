#include <PtdShapeFit2d_AirfoilLeading_t1.hxx>
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

	static auto upperMax = std::make_pair(1.0, 1.0);
	static auto upperMaxLoc = std::make_pair(10.0, 10.0);
	static auto upperMaxAngle = std::make_pair(0.0, 0.0);
	static auto upperTight = std::make_pair(0.5, 0.5);
	static auto upperWeight0 = std::make_pair(1.0, 1.0);
	static auto upperWeight1 = std::make_pair(1.0, 1.0);
	static auto upperWeight2 = std::make_pair(1.0, 1.0);

	static auto lowerMax = std::make_pair(1.0, 1.0);
	static auto lowerMaxLoc = std::make_pair(10.0, 10.0);
	static auto lowerMaxAngle = std::make_pair(0.0, 0.0);
	static auto lowerTight = std::make_pair(0.5, 0.5);
	static auto lowerWeight0 = std::make_pair(1.0, 1.0);
	static auto lowerWeight1 = std::make_pair(1.0, 1.0);
	static auto lowerWeight2 = std::make_pair(1.0, 1.0);

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

	void setUpperMaxAngle(double lower, double upper)
	{
		upperMaxAngle = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the upperMaxAngle is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperTight(double lower, double upper)
	{
		upperTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upperTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperWeight0(double lower, double upper)
	{
		upperWeight0 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight0 is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperWeight1(double lower, double upper)
	{
		upperWeight1 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight1 is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setUpperWeight2(double lower, double upper)
	{
		upperWeight2 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the upper weight2 is set to: " << endl
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

	void setLowerMaxAngle(double lower, double upper)
	{
		lowerMaxAngle = std::make_pair(Geo_Tools::DegToRadian(lower), Geo_Tools::DegToRadian(upper));
		if (verbose)
		{
			Info << endl
				<< " - the lowerMaxAngle is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerTight(double lower, double upper)
	{
		lowerTight = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lowerTight is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerWeight0(double lower, double upper)
	{
		lowerWeight0 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight0 is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerWeight1(double lower, double upper)
	{
		lowerWeight1 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight1 is set to: " << endl
				<< " lower: " << lower << ", upper: " << upper << endl;
		}
	}

	void setLowerWeight2(double lower, double upper)
	{
		lowerWeight2 = std::make_pair(lower, upper);
		if (verbose)
		{
			Info << endl
				<< " - the lower weight2 is set to: " << endl
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
		auto myXo = curveLib::airfoilLib::Leading_t1::CreateXo(xo.first, xo.second);
		auto myYo = curveLib::airfoilLib::Leading_t1::CreateYo(yo.first, yo.second);

		auto myNoseAngle = curveLib::airfoilLib::Leading_t1::CreateNoseAngle(noseAngle.first, noseAngle.second);

		auto myUpperMax = curveLib::airfoilLib::Leading_t1::CreateUpperMax(upperMax.first, upperMax.second);
		auto myUpperMaxLoc = curveLib::airfoilLib::Leading_t1::CreateUpperMaxLoc(upperMaxLoc.first, upperMaxLoc.second);
		auto myUpperMaxAngle = curveLib::airfoilLib::Leading_t1::CreateUpperMaxAngle(upperMaxAngle.first, upperMaxAngle.second);
		auto myUpperTight = curveLib::airfoilLib::Leading_t1::CreateUpperTight(upperTight.first, upperTight.second);
		auto myUpperWeight0 = curveLib::airfoilLib::Leading_t1::CreateUpperWeight0(upperWeight0.first, upperWeight0.second);
		auto myUpperWeight1 = curveLib::airfoilLib::Leading_t1::CreateUpperWeight1(upperWeight1.first, upperWeight1.second);
		auto myUpperWeight2 = curveLib::airfoilLib::Leading_t1::CreateUpperWeight2(upperWeight2.first, upperWeight2.second);

		auto myLowerMax = curveLib::airfoilLib::Leading_t1::CreateLowerMax(lowerMax.first, lowerMax.second);
		auto myLowerMaxLoc = curveLib::airfoilLib::Leading_t1::CreateLowerMaxLoc(lowerMaxLoc.first, lowerMaxLoc.second);
		auto myLowerMaxAngle = curveLib::airfoilLib::Leading_t1::CreateLowerMaxAngle(lowerMaxAngle.first, lowerMaxAngle.second);
		auto myLowerTight = curveLib::airfoilLib::Leading_t1::CreateLowerTight(lowerTight.first, lowerTight.second);
		auto myLowerWeight0 = curveLib::airfoilLib::Leading_t1::CreateLowerWeight0(lowerWeight0.first, lowerWeight0.second);
		auto myLowerWeight1 = curveLib::airfoilLib::Leading_t1::CreateLowerWeight1(lowerWeight1.first, lowerWeight1.second);
		auto myLowerWeight2 = curveLib::airfoilLib::Leading_t1::CreateLowerWeight2(lowerWeight2.first, lowerWeight2.second);

		auto sect = std::make_shared<curveLib::airfoilLib::Leading_t1>();

		sect->SetDir(myDir);

		sect->SetXo(myXo);
		sect->SetYo(myYo);

		sect->SetNoseAngle(myNoseAngle);

		sect->SetUpperMax(myUpperMax);
		sect->SetUpperMaxLoc(myUpperMaxLoc);
		sect->SetUpperMaxAngle(myUpperMaxAngle);
		sect->SetUpperTight(myUpperTight);
		sect->SetUpperWeight0(myUpperWeight0);
		sect->SetUpperWeight1(myUpperWeight1);
		sect->SetUpperWeight2(myUpperWeight2);

		sect->SetLowerMax(myLowerMax);
		sect->SetLowerMaxLoc(myLowerMaxLoc);
		sect->SetLowerMaxAngle(myLowerMaxAngle);
		sect->SetLowerTight(myLowerTight);
		sect->SetLowerWeight0(myLowerWeight0);
		sect->SetLowerWeight1(myLowerWeight1);
		sect->SetLowerWeight2(myLowerWeight2);

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

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMax(lower, upper); }), "setUpperMax");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMax(x, x); }), "setUpperMax");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMaxLoc(lower, upper); }), "setUpperMaxLoc");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMaxAngle(x, x); }), "setUpperMaxAngle");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperMaxAngle(lower, upper); }), "setUpperMaxAngle");
		mod->add(chaiscript::fun([](double x)-> void {setUpperMaxLoc(x, x); }), "setUpperMaxLoc");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperTight(lower, upper); }), "setUpperTight");
		mod->add(chaiscript::fun([](double x)-> void {setUpperTight(x, x); }), "setUpperTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperWeight0(lower, upper); }), "setUpperWeight0");
		mod->add(chaiscript::fun([](double x)-> void {setUpperWeight0(x, x); }), "setUpperWeight0");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperWeight1(lower, upper); }), "setUpperWeight1");
		mod->add(chaiscript::fun([](double x)-> void {setUpperWeight1(x, x); }), "setUpperWeight1");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setUpperWeight2(lower, upper); }), "setUpperWeight2");
		mod->add(chaiscript::fun([](double x)-> void {setUpperWeight2(x, x); }), "setUpperWeight2");

		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMax(lower, upper); }), "setLowerMax");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMax(x, x); }), "setLowerMax");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMaxLoc(lower, upper); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMaxLoc(x, x); }), "setLowerMaxLoc");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerMaxAngle(lower, upper); }), "setLowerMaxAngle");
		mod->add(chaiscript::fun([](double x)-> void {setLowerMaxAngle(x, x); }), "setLowerMaxAngle");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerTight(lower, upper); }), "setLowerTight");
		mod->add(chaiscript::fun([](double x)-> void {setLowerTight(x, x); }), "setLowerTight");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerWeight0(lower, upper); }), "setLowerWeight0");
		mod->add(chaiscript::fun([](double x)-> void {setLowerWeight0(x, x); }), "setLowerWeight0");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerWeight1(lower, upper); }), "setLowerWeight1");
		mod->add(chaiscript::fun([](double x)-> void {setLowerWeight1(x, x); }), "setLowerWeight1");
		mod->add(chaiscript::fun([](double lower, double upper)-> void {setLowerWeight2(lower, upper); }), "setLowerWeight2");
		mod->add(chaiscript::fun([](double x)-> void {setLowerWeight2(x, x); }), "setLowerWeight2");

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
			Info << " This application is aimed to create a parametric airfoil nose curve for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl
				<< " - printTypes()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setDir(u, v)" << endl << endl

				<< " - setXo(lower, upper [optional])" << endl
				<< " - setYo(lower, upper [optional])" << endl << endl

				<< " - setNoseAngle(lower [deg], upper [deg] [optional])" << endl << endl

				<< " - setUpperMax(lower, upper [optional])" << endl
				<< " - setUpperMaxLoc(lower, upper [optional])" << endl
				<< " - setUpperMaxAngle(lower [deg], upper [deg] [optional])" << endl
				<< " - setUpperNose(lower, upper [optional])" << endl
				<< " - setUpperWeight0(lower, upper [optional])" << endl
				<< " - setUpperWeight1(lower, upper [optional])" << endl
				<< " - setUpperWeight2(lower, upper [optional])" << endl << endl

				<< " - setLowerMax(lower, upper [optional])" << endl
				<< " - setLowerMaxLoc(lower, upper [optional])" << endl
				<< " - setLowerMaxAngle(lower [deg], upper [deg] [optional])" << endl
				<< " - setLowerNose(lower, upper [optional])" << endl
				<< " - setLowerWeight0(lower, upper [optional])" << endl
				<< " - setLowerWeight1(lower, upper [optional])" << endl
				<< " - setLowerWeight2(lower, upper [optional])" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbShapeFitAirfoilCurveT1"));
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