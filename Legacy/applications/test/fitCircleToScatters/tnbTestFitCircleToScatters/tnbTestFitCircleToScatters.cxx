#include <Pln_Curve.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <NumAlg_GA.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Circle.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Ax2d.hxx>
#include <Standard_Handle.hxx>

namespace tnbLib
{

	static double myU0 = 0;
	static double myU1 = PI;
	static double minRadius = 0;
	static double maxRadius = 100.0;
	static double minX = -100.0;
	static double maxX = 100.0;
	static double minY = -100.0;
	static double maxY = 100.0;

	static Pnt2d myCentre(0, 0);

	static double myTol = 1.0E-6;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Entity2d_Polygon> myPoly;
	static std::shared_ptr<NumAlg_GA_Base::GA_Info> myGaInfo;

	static auto myMaxNbGens = 20;
	static auto myPopSize = 20;
	static auto myMutation = 0.05;
	static auto mySelection = 0.5;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMaxNbGens(int n)
	{
		myMaxNbGens = n;
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of gens is set to: " << myMaxNbGens << endl;
		}
	}

	void setPopSize(int n)
	{
		myPopSize = n;
		if (verbose)
		{
			Info << endl
				<< " - the pop. size is set to: " << myPopSize << endl;
		}
	}

	void setMutation(double x)
	{
		myMutation = x;
		if (verbose)
		{
			Info << endl
				<< " - the mutation is set to: " << myMutation << endl;
		}
	}

	void setSelection(double x)
	{
		mySelection = x;
		if (verbose)
		{
			Info << endl
				<< " - the selection is set to: " << mySelection << endl;
		}
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setU0(double x)
	{
		myU0 = x;
		if (verbose)
		{
			Info << endl
				<< " - the u0 is set to: " << myU0 << endl;
		}
	}

	void setU1(double x)
	{
		myU1 = x;
		if (verbose)
		{
			Info << endl
				<< " - the u1 is set to: " << myU1 << endl;
		}
	}

	void setMinX(double x)
	{
		minX = x;
		if (verbose)
		{
			Info << endl
				<< " - the min. x is set to: " << minX << endl;
		}
	}

	void setMaxX(double x)
	{
		maxX = x;
		if (verbose)
		{
			Info << endl
				<< " - the max. x is set to: " << maxX << endl;
		}
	}

	void setMinY(double x)
	{
		minY = x;
		if (verbose)
		{
			Info << endl
				<< " - the min. y is set to: " << minY << endl;
		}
	}

	void setMaxY(double x)
	{
		maxY = x;
		if (verbose)
		{
			Info << endl
				<< " - the max. y is set to: " << maxY << endl;
		}
	}

	void setMinRadius(double x)
	{
		minRadius = x;
		if (verbose)
		{
			Info << endl
				<< " - the min. radius is set to: " << minRadius << endl;
		}
	}

	void setMaxRadius(double x)
	{
		maxRadius = x;
		if (verbose)
		{
			Info << endl
				<< " - the max. radius is set to: " << maxRadius << endl;
		}
	}

	void setCentre(const Pnt2d& thePnt)
	{
		myCentre = thePnt;
		if (verbose)
		{
			Info << endl
				<< " - the centre is set to: " << myCentre << endl;
		}
	}

	auto loadGaInfo()
	{
		checkFolder("gaInfo");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\gaInfo)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), NumAlg_GA_Base::GA_Info::extension).string();

		auto myInfo = file::LoadFile<std::shared_ptr<NumAlg_GA_Base::GA_Info>>(name + NumAlg_GA_Base::GA_Info::extension, verbose);

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		return std::move(myInfo);
	}

	auto loadPolygon()
	{
		checkFolder("polygon");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/7/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\polygon)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity2d_Polygon::extension).string();

		auto poly = file::LoadFile<std::shared_ptr<Entity2d_Polygon>>(name + Entity2d_Polygon::extension, verbose);

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		return std::move(poly);
	}

	void loadFiles()
	{
		//myGaInfo = loadGaInfo();
		myPoly = loadPolygon();

		loadTag = true;
	}

	class GA_CostFun
	{

		/*Private Data*/

		double theU0_;
		double theU1_;

		//Pnt2d theCentre_;

		std::shared_ptr<Entity2d_Polygon> thePoly_;

	public:

		// default constructor [2/7/2023 Payvand]

		GA_CostFun()
			: theU0_(0)
			, theU1_(0)
		{}

		// constructors [2/7/2023 Payvand]


		// Public functions and operators [2/7/2023 Payvand]

		auto U0() const
		{
			return theU0_;
		}

		auto U1() const
		{
			return theU1_;
		}

		/*const auto& Centre() const
		{
			return theCentre_;
		}*/

		const auto& Polygon() const
		{
			return thePoly_;
		}

		double CalcError(const double theRadius, const Pnt2d& theCentre);

		void SetU0(const double u)
		{
			theU0_ = u;
		}

		void SetU1(const double u)
		{
			theU1_ = u;
		}

		/*void SetCentre(const Pnt2d& theCoord)
		{
			theCentre_ = theCoord;
		}

		void SetCentre(Pnt2d&& theCoord)
		{
			theCentre_ = std::move(theCoord);
		}*/

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePoly)
		{
			thePoly_ = thePoly;
		}

		static double CalcCost(const std::vector<double>& xs, const std::shared_ptr<GA_CostFun>& theObj)
		{
			Pnt2d pt(xs.at(1), xs.at(2));
			return theObj->CalcError(xs.at(0), pt);
		}
	};

	auto calcError(const Pnt2d& thePt, const Handle(Geom2d_Curve)& theCurve)
	{
		try
		{
			Geom2dAPI_ProjectPointOnCurve proj(thePt, theCurve);
			return proj.LowerDistance();
		}
		catch (const Standard_Failure& x)
		{
			Info << endl
				<< " WARNING! Failed to project the point onto the curve." << endl;
			return 0.0;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded" << endl
				<< abort(FatalError);
		}

		NumAlg_GA_Base::verbose = verbose;

		myGaInfo = std::make_shared<NumAlg_GA_Base::GA_Info>();
		myGaInfo->SetMaxNbGenerations(myMaxNbGens);
		myGaInfo->SetMutation(myMutation);
		myGaInfo->SetNbParameters(3);
		myGaInfo->SetPopSize(myPopSize);
		myGaInfo->SetSelection(mySelection);

		auto costFun = std::make_shared<GA_CostFun>();
		costFun->SetPolygon(myPoly);
		//costFun->SetCentre(myCentre);
		costFun->SetU0(myU0);
		costFun->SetU1(myU1);

		NumAlg_GA<GA_CostFun, true> ga;
		ga.SetGaInfo(myGaInfo);
		ga.PopInfo()->Limits().resize(3);
		ga.PopInfo()->Limits().at(0).SetLower(minRadius);
		ga.PopInfo()->Limits().at(0).SetUpper(maxRadius);

		ga.PopInfo()->Limits().at(1).SetLower(minX);
		ga.PopInfo()->Limits().at(1).SetUpper(maxX);

		ga.PopInfo()->Limits().at(2).SetLower(minY);
		ga.PopInfo()->Limits().at(2).SetUpper(maxY);

		ga.SetFunction(&GA_CostFun::CalcCost);
		ga.SetObject(costFun);

		ga.Perform();

		auto results = *ga.PopInfo()->Population().at(0);

		if (verbose)
		{
			Info << endl
				<< " the application is performed." << endl
				<< " - radius = " << results.at(0) << endl;
		}

		auto cc = gp::OX2d();
		cc.SetLocation(Pnt2d(results.at(1), results.at(2)));
		OFstream myFile("circle.plt");
		Handle(Geom2d_Curve) curve = new Geom2d_Circle(cc, results.at(0));

		auto trimmed = Pln_CurveTools::Trim(curve, curve->FirstParameter(), curve->LastParameter());

		Pln_Curve pCurve(trimmed);
		auto pl = Pln_Curve::Discretize(pCurve, 100);
		pl->ExportToPlt(myFile);

		exeTag = true;
	}
}


double tnbLib::GA_CostFun::CalcError(const double theRadius, const Pnt2d& theCentre)
{
	gp_Dir2d dir(std::sin(theU0_), std::cos(theU0_));
	gp_Ax2d ax(theCentre, dir);
	gp_Circ2d g(ax, theRadius);
	auto curve = Pln_CurveTools::MakeCircArc(g, 0, theU1_ - theU0_);

	double sum = 0;
	for (const auto& x : Polygon()->Points())
	{
		auto di = calcError(x, curve);
		//std::cout <<"x = " << x << ", di = " << di << std::endl;
		auto di2 = di * di;
		sum += di2;
	}
	//PAUSE;
	std::cout << "radius = " << theRadius << ", sum = " << sum << std::endl;
	std::cout << "pt: " << theCentre << std::endl;
	return sum;
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
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbGens(n); }), "setMaxNbGens");
		mod->add(chaiscript::fun([](int n)-> void {setPopSize(n); }), "setPopSize");
		mod->add(chaiscript::fun([](double x)-> void {setMutation(x); }), "setMutation");
		mod->add(chaiscript::fun([](double x)-> void {setSelection(x); }), "setSelection");

		mod->add(chaiscript::fun([](double x)-> void {setMinRadius(x); }), "setMinRadius");
		mod->add(chaiscript::fun([](double x)-> void {setMaxRadius(x); }), "setMaxRadius");
		mod->add(chaiscript::fun([](double u)-> void {setU0(u); }), "setU0");
		mod->add(chaiscript::fun([](double u)-> void {setU1(u); }), "setU1");

		//mod->add(chaiscript::fun([](const Pnt2d& theCoord)-> void {setCentre(theCoord); }), "setCentre");

		mod->add(chaiscript::fun([](double x)-> void {setMinX(x); }), "setMinX");
		mod->add(chaiscript::fun([](double x)-> void {setMaxX(x); }), "setMaxX");
		mod->add(chaiscript::fun([](double x)-> void {setMinY(x); }), "setMinY");
		mod->add(chaiscript::fun([](double x)-> void {setMaxY(x); }), "setMaxY");

		// operators [12/21/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		//mod->add(chaiscript::fun([](double x, double y) -> auto {return Pnt2d(x, y); }), "createPoint");
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
			Info << " This application is aimed to fitting a circle curve to scatter points." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				//<< " - setCentre(Point)" << endl << endl

				<< " - setMinRadius(r)" << endl
				<< " - setMaxRadius(r)" << endl << endl

				<< " - setMinX(x)" << endl
				<< " - setMaxX(x)" << endl
				<< " - setMinY(x)" << endl
				<< " - setMaxY(x)" << endl << endl

				<< " - setU0(u)" << endl
				<< " - setU1(u)" << endl << endl

				<< " - setMaxNbGens(n)" << endl
				<< " - setPopSize(n)" << endl
				<< " - setMutation(x)" << endl
				<< " - setSelection(x)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				//<< " - [Point] createPoint(x, y)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbTestFitCircleToScatters"));

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