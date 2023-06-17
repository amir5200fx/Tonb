#include <AirfoilPx.hxx>
#include <AirfoilPx_PxCamberProfile_t1.hxx>
#include <AirfoilPx_PxThickProfile_t1.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_ApprxCurve_System.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <Geom2d_Curve.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{
	static auto myInfo = std::make_shared<Geo_ApprxCurve_Info>();

	static auto myCamber = std::make_shared<profileLib::CamberProfile_t1>();
	static auto myThick = std::make_shared<profileLib::PxThick_t1>();
	

	static auto nbPoints = 40;
	static auto myChordLen = 1.0;
	static auto myDistb = std::make_shared<Geo_CosineDistb>(nbPoints);

	auto myAirfoil = std::make_shared<AirfoilPx>();

	static unsigned short verbose = 0;
	static auto exeTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setNbPoints(int n)
	{
		nbPoints = n;
		if (verbose)
		{
			Info << endl
				<< " - the no. of points is set to: " << nbPoints << endl;
		}
	}

	void setChordLen(double x)
	{
		myChordLen = x;
		if (verbose)
		{
			Info << endl
				<< " - the chord length is set to: " << myChordLen << endl;
		}
	}

	void setMaxCamb(double x)
	{
		myCamber->SetMax(x);
		if (verbose)
		{
			Info << endl
				<< " - the max. camb. is set to: " << x << endl;
		}
	}

	void setMaxCambLoc(double x)
	{
		myCamber->SetMaxLoc(x);
		if (verbose)
		{
			Info << endl
				<< " - the max. camb. loc. is set to: " << x << endl;
		}
	}

	void setLeadCambSteep(double x)
	{
		myCamber->SetLeadSteep(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading camb. steep is set to: " << x << endl;
		}
	}

	void setLeadCambSteepTight(double x)
	{
		myCamber->SetLeadSteepTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading camb. steep tightness is set to: " << x << endl;
		}
	}

	void setLeadCambSteepWeight(double x)
	{
		myCamber->SetLeadSteepWeight(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading camb. steep weight is set to: " << x << endl;
		}
	}

	void setTrailCambSteep(double x)
	{
		myCamber->SetTrailSteep(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing camb. steep is set to: " << x << endl;
		}
	}

	void setTrailCambSteepTight(double x)
	{
		myCamber->SetTrailSteepTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing camb. steep tightness is set to: " << x << endl;
		}
	}

	void setTrailCambSteepWeight(double x)
	{
		myCamber->SetTrailSteepWeight(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing camb. steep weight is set to: " << x << endl;
		}
	}

	void setMaxThick(double x)
	{
		myThick->SetMax(x);
		if (verbose)
		{
			Info << endl
				<< " - the max. camb. is set to: " << x << endl;
		}
	}

	void setMaxThickLoc(double x)
	{
		myThick->SetMaxLoc(x);
		if (verbose)
		{
			Info << endl
				<< " - the max. thick. loc. is set to: " << x << endl;
		}
	}

	void setLeadThickSteep(double x)
	{
		myThick->SetLeadSteep(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading thick. steep is set to: " << x << endl;
		}
	}

	void setLeadThickSteepTight(double x)
	{
		myThick->SetLeadSteepTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading thick. steep tightness is set to: " << x << endl;
		}
	}

	void setLeadThickSteepWeight(double x)
	{
		myThick->SetLeadSteepWeight(x);
		if (verbose)
		{
			Info << endl
				<< " - the leading thick. steep weight is set to: " << x << endl;
		}
	}

	void setTrailThickSteep(double x)
	{
		myThick->SetTrailSteep(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thick. steep is set to: " << x << endl;
		}
	}

	void setTrailThickSteepTight(double x)
	{
		myThick->SetTrailSteepTight(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thick. steep tightness is set to: " << x << endl;
		}
	}

	void setTrailThickSteepWeight(double x)
	{
		myThick->SetTrailSteepWeight(x);
		if (verbose)
		{
			Info << endl
				<< " - the trailing thick. steep weight is set to: " << x << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		auto current = fs::current_path().string();
		std::string address = current + "\\results";
		fs::path dir(address);
		if (NOT fs::is_directory(dir))
		{
			fs::create_directory(dir);
		}
		else
		{
			file::RemoveDirectory(dir);
			fs::create_directory(dir);
		}

		fs::current_path(dir);

		std::vector<std::shared_ptr<Pln_Curve>> curves;
		curves.push_back(myAirfoil->UpperSurface());
		curves.push_back(myAirfoil->LowerSurface());

		auto myEdges = Pln_Tools::RetrieveEdges(curves);

		size_t i = 0;
		for (const auto& x : myEdges)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + Pln_Edge::extension, verbose);

			fs::current_path(dir);

			++i;
		}
		fs::current_path(current);
	}

	void saveTo()
	{
		saveTo("");
	}

	auto discreteCurve(const std::shared_ptr<Pln_Curve>& curve)
	{
		//return Pln_Curve::Discretize(*curve, 100);
		const auto& geom = curve->Geometry();
		auto alg = 
			std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), true>>
			(
				geom,
				curve->FirstParameter(),
				curve->LastParameter(), 
				myInfo
				);
		alg->Perform();
		return alg->Chain();
	}

	void exportToPlt(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}
		OFstream myFile(name);
		discreteCurve(myAirfoil->UpperSurface())->ExportToPlt(myFile);
		discreteCurve(myAirfoil->LowerSurface())->ExportToPlt(myFile);
	}

	void execute()
	{
		myInfo->SetInitNbSubdivision(5);
		myInfo->SetAngle(2.0);
		myInfo->SetApprox(myChordLen * 1.0E-2);
		myInfo->SetMinSize(myChordLen * 1.0E-4);
		myInfo->SetNbSamples(6);

		myDistb->SetLower(0);
		myDistb->SetUpper(myChordLen);
		myDistb->Perform();

		
		myAirfoil->SetCamberProfile(myCamber);
		myAirfoil->SetThickProfile(myThick);
		myAirfoil->SetXs(myDistb);

		myAirfoil->Perform();
		
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
		//mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setChordLen(x); }), "setChord");

		mod->add(chaiscript::fun([](double x)-> void {setMaxCamb(x); }), "setMaxCamb");
		mod->add(chaiscript::fun([](double x)-> void {setMaxCambLoc(x); }), "setMaxCambLoc");

		mod->add(chaiscript::fun([](double x)-> void {setLeadCambSteep(x); }), "setLeadCambSteep");
		mod->add(chaiscript::fun([](double x)-> void {setLeadCambSteepTight(x); }), "setLeadCambSteepTight");
		mod->add(chaiscript::fun([](double x)-> void {setLeadCambSteepWeight(x); }), "setLeadCambSteepWeight");

		mod->add(chaiscript::fun([](double x)-> void {setTrailCambSteep(x); }), "setTrailCambSteep");
		mod->add(chaiscript::fun([](double x)-> void {setTrailCambSteepTight(x); }), "setTrailCambSteepTight");
		mod->add(chaiscript::fun([](double x)-> void {setTrailCambSteepWeight(x); }), "setTrailCambSteepWeight");

		mod->add(chaiscript::fun([](double x)-> void {setMaxThick(x); }), "setMaxThick");
		mod->add(chaiscript::fun([](double x)-> void {setMaxThickLoc(x); }), "setMaxThickLoc");

		mod->add(chaiscript::fun([](double x)-> void {setLeadThickSteep(x); }), "setLeadThickSteep");
		mod->add(chaiscript::fun([](double x)-> void {setLeadThickSteepTight(x); }), "setLeadThickSteepTight");
		mod->add(chaiscript::fun([](double x)-> void {setLeadThickSteepWeight(x); }), "setLeadThickSteepWeight");

		mod->add(chaiscript::fun([](double x)-> void {setTrailThickSteep(x); }), "setTrailThickSteep");
		mod->add(chaiscript::fun([](double x)-> void {setTrailThickSteepTight(x); }), "setTrailThickSteepTight");
		mod->add(chaiscript::fun([](double x)-> void {setTrailThickSteepWeight(x); }), "setTrailThickSteepWeight");
		//mod->add(chaiscript::fun([](double x)-> void {setTol(x); }), "setTolerance");

		// operators [12/21/2021 Amir]
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
			Info << " This application is aimed to create a parametric airfoil." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - exportToPlt(name [optional])" << endl
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

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbAirfoilPx"));

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
	return 1;
}