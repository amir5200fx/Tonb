#include <Airfoil_Naca.hxx>
#include <Airfoil_NacaMidline.hxx>
#include <Airfoil_NacaThickness.hxx>
#include <Airfoil_NacaThickness_Profile.hxx>
#include <Airfoil_NacaThickOffsets_N65A010.hxx>
#include <Airfoil_trapzNacaMidline.hxx>
#include <Airfoil_uniformNacaMidline.hxx>
#include <Airfoil_OffsetProfile_Steffen.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TecPlot.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static auto airfoil = std::make_shared<Airfoil_Naca>();
	static std::shared_ptr<Geo_xDistb> myDistb;

	static std::shared_ptr<Airfoil_NacaMidline> myCamberProfile;
	static std::shared_ptr<Airfoil_NacaThickness> myThickProfile;

	static auto myChord = 0.;
	static auto myThickness = 0.;
	static auto myCli = 0.0;
	static auto myMaxPressLoc = 0.0;
	//static auto nbSegments = 10;

	static std::shared_ptr<Airfoil_Naca::ioData> myData;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void saveTo(const word& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myData, name + Airfoil_Naca::ioData::extension, verbose);
	}

	void exportToPlt(const word& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		OFstream myFile(name + ".plt");

		Io::ExportCurve(myData->upper, myFile);
		Io::ExportCurve(myData->lower, myFile);
	}

	void setChord(double x)
	{
		myChord = x;
		if (verbose)
		{
			Info << endl
				<< " - the chord is set to: " << myChord << endl;
		}
	}

	void setThickness(double x)
	{
		myThickness = x;
		if (verbose)
		{
			Info << endl
				<< " - the thickness is set to: " << myThickness << endl;
		}
	}

	void setCli(double x)
	{
		myCli = x;
		if (verbose)
		{
			Info << endl
				<< " - the Cli is set to: " << myCli << endl;
		}
	}

	void setMaxPressLoc(double x)
	{
		myMaxPressLoc = x;
		if (verbose)
		{
			Info << endl
				<< " - the location of the max. pressure is set to: " << myMaxPressLoc << endl;
		}
	}

	auto createCamber(const word& theName)
	{
		if (theName IS_EQUAL "uniform")
		{
			auto camber = std::make_shared<Airfoil_uniformNacaMidline>();
			camber->SetCli(myCli);
			std::shared_ptr<Airfoil_NacaMidline> mid = camber;
			return std::move(mid);
		}
		else if (theName IS_EQUAL "trapezoidal")
		{
			auto camber = std::make_shared<Airfoil_trapzNacaMidline>();
			camber->SetA(myMaxPressLoc);
			camber->SetChord(myChord);
			camber->SetCli(myCli);
			std::shared_ptr<Airfoil_NacaMidline> mid = camber;
			return std::move(mid);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such a distribution of the camber is found." << endl
				<< abort(FatalError);
			std::shared_ptr<Airfoil_NacaMidline> mid;
			return std::move(mid);
		}
	}

	auto interpolteProfile(const word& name, const std::vector<std::pair<double, double>>& Qs)
	{
		if (name IS_EQUAL "steffen")
		{
			std::shared_ptr<Airfoil_OffsetProfile> qs = std::make_shared<Airfoil_OffsetProfile_Steffen>();
			qs->SetQs(Qs);
			qs->Perform();
			return std::move(qs);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such an interpolation method is found." << endl
				<< abort(FatalError);
			std::shared_ptr<Airfoil_OffsetProfile> qs;
			return std::move(qs);
		}
	}

	auto createThicknessOffsetProfile(const std::shared_ptr<Airfoil_OffsetProfile>& p)
	{
		auto tp = std::make_shared<Airfoil_NacaThickness_Profile>();
		tp->SetProfile(p);
		std::shared_ptr<Airfoil_NacaThickness> thickness = tp;
		return std::move(thickness);
	}

	auto createThicknessOffsets(const word& theName)
	{
		if (theName IS_EQUAL "A65A010")
		{
			auto thickOffsets = std::make_shared<Airfoil_NacaThickOffsets_N65A010>();
			auto qs = thickOffsets->Values(1.0);
			return std::move(qs);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such profile thickness is found." << endl
				<< abort(FatalError);
			std::vector<std::pair<double, double>> qs;
			return std::move(qs);
		}
	}

	auto createDistb(const word& name, int nbSegments, double x0, double x1)
	{
		if (name IS_EQUAL "cosine")
		{
			auto cosineDistb = std::make_shared<Geo_CosineDistb>(nbSegments);
			cosineDistb->SetLower(x0);
			cosineDistb->SetUpper(x1);
			cosineDistb->Perform();
			std::shared_ptr<Geo_xDistb> xDistb = cosineDistb;
			return std::move(xDistb);
		}
		else if (name IS_EQUAL "uniform")
		{
			auto cosineDistb = std::make_shared<Geo_UniDistb>(nbSegments);
			cosineDistb->SetLower(x0);
			cosineDistb->SetUpper(x1);
			cosineDistb->Perform();
			std::shared_ptr<Geo_xDistb> xDistb = cosineDistb;
			return std::move(xDistb);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "no such a profile is found." << endl
				<< abort(FatalError);
			std::shared_ptr<Geo_xDistb> xDistb;
			return std::move(xDistb);
		}
	}

	void SetCamberProfile(const std::shared_ptr<Airfoil_NacaMidline>& profile)
	{
		myCamberProfile = profile;
	}

	void SetThicknessProfile(const std::shared_ptr<Airfoil_NacaThickness>& profile)
	{
		myThickProfile = profile;
	}

	void SetDistb(const std::shared_ptr<Geo_xDistb>& d)
	{
		myDistb = d;
	}

	Handle(Geom2d_Curve) NurbsInterpolation(const std::vector<Pnt2d>& theCoords)
	{
		return Pln_CurveTools::Interpolation(theCoords);
	}

	auto CalcNoseRadius(const Handle(Geom2d_Curve)& t)
	{
		Pnt2d pt;
		Vec2d v1, v2;
		
		t->D2(t->FirstParameter(), pt, v1, v2);

		const auto D1 = v1.Magnitude();
		const auto D2 = v2.Magnitude();

		auto paired = std::make_pair(std::move(pt), (D1*D1*D1) / D2);
		return std::move(paired);
	}

	auto CalcTailTangent(const Handle(Geom2d_Curve)& t)
	{
		Pnt2d pt;
		Vec2d v1;

		t->D1(t->FirstParameter(), pt, v1);

		auto paired = std::make_pair(std::move(pt), std::move(v1));
		return std::move(paired);
	}

	auto CalcThickOffsets(const std::shared_ptr<Airfoil_NacaThickness>& profile, const std::shared_ptr<Geo_xDistb>& xs, const Standard_Real chord, const Standard_Real yMax)
	{
		std::vector<Pnt2d> pts;
		pts.reserve(xs->Size());
		for (auto x : xs->Values())
		{
			auto y = profile->CalcYt(x);

			Pnt2d pt(x*chord, y*yMax);
			pts.push_back(std::move(pt));
		}
		return std::move(pts);
	}

	void execute()
	{
		/*if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}*/

		airfoil->SetChord(myChord);
		airfoil->SetMaxThickness(myThickness);
		airfoil->SetMidLine(myCamberProfile);
		airfoil->SetThickness(myThickProfile);
		airfoil->SetXc(myDistb);
		airfoil->SetApplyTrim(Standard_True);
		airfoil->SetTrim(0.05);

		airfoil->Perform();
		if (NOT airfoil->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		myData = std::make_shared<Airfoil_Naca::ioData>();
		myData->upper = airfoil->Upper();
		myData->lower = airfoil->Lower();

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/28/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
		//mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/28/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setChord(x); }), "setChord");
		mod->add(chaiscript::fun([](double x)-> void {setThickness(x); }), "setThickness");
		mod->add(chaiscript::fun([](double x)-> void {setMaxPressLoc(x); }), "setMaxPressLoc");
		mod->add(chaiscript::fun([](double x)-> void {setCli(x); }), "setCli");
		mod->add(chaiscript::fun([](const std::shared_ptr<Geo_xDistb>& d)-> void {myDistb = d; }), "setDistb");

		mod->add(chaiscript::fun([](const std::shared_ptr<Airfoil_NacaMidline>& p)-> void {SetCamberProfile(p); }), "setCamberProfile");
		mod->add(chaiscript::fun([](const std::shared_ptr<Airfoil_NacaThickness>& p)-> void {SetThicknessProfile(p); }), "setThicknessProfile");

		// operators [12/28/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {return createCamber(name); }), "createCamberProfile");
		mod->add(chaiscript::fun([](const std::string& name, const std::vector<std::pair<double, double>>& qs)-> auto{return interpolteProfile(name, qs); }), "interpolate");
		mod->add(chaiscript::fun([](const std::string& name)-> auto{return createThicknessOffsets(name); }), "createThicknessOffsets");
		mod->add(chaiscript::fun([](const std::shared_ptr<Airfoil_OffsetProfile>& q)-> auto {return createThicknessOffsetProfile(q); }), "createThicknessProfile");
		mod->add(chaiscript::fun([](const std::string& name, int nbSeg, double x0, double x1)-> auto {return createDistb(name, nbSeg, x0, x1); }), "createDistb");

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
	//FatalConvError.throwExceptions();

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
			Info << " This application is aimed to create a NACA airfoil." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - exportToPlt(name)" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " - setChord(x); " << endl
				<< " - setThickness(x);" << endl
				<< " - setMaxPressLoc(x); " << endl
				<< " - setCli(x); " << endl << endl

				<< " - setCamberProfile(profile); " << endl
				<< " - setThicknessProfile(profile);" << endl
				<< " - setDistb(distb);" << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl << endl

				<< " - [camber profile] createCamberProfile(name);   types: uniform, trapezoidal" << endl
				<< " - [interpolated] interpolate(name, Qs);   name: steffen" << endl
				<< " - [Qs] createThicknessOffsets(name);  types: A65A010" << endl
				<< " - [thickness profile] createThicknessProfile(interpolated);" << endl
				<< " - [distb] createDistb(name, n, x0, x1);   name: uniform, cosine" << endl
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
				fileName myFileName(file::GetSystemFile("tnbAirfoil"));

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