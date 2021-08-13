#include <Cad2d_LocalInterpl.hxx>
#include <Cad2d_InterpUbarMaps.hxx>
#include <Pln_Curve.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::vector<Pnt2d> myCoords;
	static std::string myUbarMap = "chordLen";
	static std::string myContinuityType = "G1";
	static std::string myNeighborType = "fivePoint";

	static unsigned short verbose(0);

	static double myTol = 1.0E-6;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto createPoint(double x, double y)
	{
		auto pt = Pnt2d(x, y);
		return std::move(pt);
	}

	void insertTo(const Pnt2d& p)
	{
		myCoords.push_back(p);
	}

	void setUbarMap(const std::string& name)
	{
		myUbarMap = name;
		if (verbose)
		{
			Info << endl
				<< " - the uBar map is set to: " << myUbarMap << endl;
		}
	}

	void setContinuityType(const std::string& name)
	{
		myContinuityType = name;
		if (verbose)
		{
			Info << endl
				<< " - the continuity type id set to: " << myContinuityType << endl;
		}
	}

	void setNeighborType(const std::string& name)
	{
		myNeighborType = name;
		if (verbose)
		{
			Info << endl
				<< " - the neighbor type is set to: " << myNeighborType << endl;
		}
	}

	void setTolerance(double t)
	{
		myTol = t;
		if (verbose)
		{
			Info << endl
				<< " - the tol is set to: " << myTol << endl;
		}
	}

	auto calcMerged(const std::vector<Pnt2d>& coords, double tol)
	{
		std::vector<Pnt2d> pts;
		pts.reserve(coords.size());
		pts.push_back(coords[0]);
		for (size_t k = 1; k < coords.size(); k++)
		{
			const auto& p0 = coords[k - 1];
			const auto& p1 = coords[k];

			if (p0.Distance(p1) <= tol)
			{
				// do nothing [8/10/2021 Amir]
			}
			else
			{
				pts.push_back(coords[k]);
			}
		}
		return std::move(pts);
	}

	void saveTo(const std::string& name)
	{
		const auto tol = Geo_BoxTools::GetBox(myCoords, 0).Diameter()*myTol;
		const auto pts = calcMerged(myCoords, tol);

		std::shared_ptr<Cad2d_InterpUbarMap> uBarMap;
		if (myUbarMap IS_EQUAL "uniform")
		{
			uBarMap = std::make_shared<Cad2d_InterpUbarMap_Uniform>();
		}
		else if (myUbarMap IS_EQUAL "chordLen")
		{
			uBarMap = std::make_shared<Cad2d_InterpUbarMap_ChordLen>();
		}
		else if (myUbarMap IS_EQUAL "centripetal")
		{
			uBarMap = std::make_shared<Cad2d_InterpUbarMap_Centripetal>();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of uBar distributor has been detected!" << endl
				<< " - types of uBar: uniform, chordLen and centripetal" << endl
				<< abort(FatalError);
		}

		auto alg = std::make_shared<Cad2d_LocalInterpl>(pts, uBarMap);

		if (myContinuityType IS_EQUAL "G1")
		{
			alg->SetContinuity(Cad2d_LocalInterpl::continuity::G1);
		}
		else if (myContinuityType IS_EQUAL "C1")
		{
			alg->SetContinuity(Cad2d_LocalInterpl::continuity::C1);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of continuity has been detected!" << endl
				<< " - types of continuity: G1 and C1" << endl
				<< abort(FatalError);
		}

		if (myNeighborType IS_EQUAL "threePoint")
		{
			alg->SetType(Cad2d_LocalInterpl::neighborType::threePoint);
		}
		else if (myNeighborType IS_EQUAL "fivePoint")
		{
			alg->SetType(Cad2d_LocalInterpl::neighborType::fivePoint);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of neighbor has been detected!" << endl
				<< " - types of continuity: threePoint and fivePoint" << endl
				<< abort(FatalError);
		}

		alg->Perform();

		auto myCurve = std::make_shared<Pln_Curve>(0, alg->Curve());

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myCurve;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](double x, double y)-> auto {auto p = createPoint(x, y); return std::move(p); }), "makePoint");
		mod->add(chaiscript::fun([](const Pnt2d& p)-> void {insertTo(p); }), "insertTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setUbarMap(name); }), "setUbarContrib");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setContinuityType(name); }), "setContinType");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setNeighborType(name); }), "setNeighType");
		mod->add(chaiscript::fun([](double t)->void {setTolerance(t); }), "setTolerance");

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

int main(int argc, char *argv[])
{
	FatalError.dontThrowExceptions();

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
			Info << " This application is aimed to interpolate a curve through offset points." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - makePoint(double, double); " << endl
				<< " - insertTo(Point); " << endl
				<< " - setTolerance(double);" << endl
				<< " - setUbarContrib(string);      - types: uniform, chordLen and centripetal" << endl
				<< " - setContinType(string);       - types: G1 and C1" << endl
				<< " - setNeighType(string);        - types: threePoint and fivePoint "
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("localInterpl");

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

}