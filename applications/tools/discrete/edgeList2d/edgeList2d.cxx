#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Geo_ApprxCurve_System.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Global_Timer.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <Geom2d_Curve.hxx>

#include <vector>

namespace tnbLib
{

	auto& appxInfo = sysLib::gl_approx_curve2d_info;

	typedef std::shared_ptr<Pln_Curve> curve_t;
	typedef std::shared_ptr<Pln_Edge> edge_t;
	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), true>> randAppx_t;
	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), false>> uniAppx_t;

	typedef std::shared_ptr<Entity2d_Polygon> poly_t;

	static std::vector<edge_t> myCurves;
	//static std::vector<edge_t> myEdges;
	static std::vector<poly_t> myPolygons;
	static double d;
	static bool randPnt = true;
	static bool verbose = false;

	static randAppx_t myRandAppx;
	static uniAppx_t myUniAppx;

	void setTarget(double x)
	{
		appxInfo->SetApprox(x*d);
	}

	void setAngle(double x)
	{
		appxInfo->SetAngle(x);
	}

	void setMinSize(double x)
	{
		appxInfo->SetMinSize(x*d);
	}

	void setMaxNbSubdivision(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetMaxNbSubdivision(n);
	}

	void setInitNbSubdivision(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetInitNbSubdivision(n);
	}

	void setNbSamples(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetNbSamples(n);
	}

	void printInfo()
	{
		Info << " - nb. of samples: " << appxInfo->NbSamples() << endl;
		Info << " - nb. of initial subdivisions: " << appxInfo->InitNbSubdivision() << endl;
		Info << " - max. nb. of subdivisions: " << appxInfo->MaxNbSubdivision() << endl;
		Info << " - target size: " << appxInfo->Approx() << endl;
		Info << " - min. size: " << appxInfo->MinSize() << endl;
		Info << " - angle: " << appxInfo->Angle() << endl;

		Info << " - diameter: " << d << endl;
	}

	void execute(const curve_t& myCurve)
	{
		if (randPnt)
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myRandAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), true>>
				(
					myCurve->Geometry(),
					myCurve->FirstParameter(),
					myCurve->LastParameter(),
					appxInfo
					);
			myRandAppx->Perform();
			myUniAppx = nullptr;

			//myPolygons.push_back(myRandAppx->Chain());
		}
		else
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myUniAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), false>>
				(
					myCurve->Geometry(),
					myCurve->FirstParameter(),
					myCurve->LastParameter(),
					appxInfo
					);
			myUniAppx->Perform();
			myRandAppx = nullptr;

			//myPolygons.push_back(myUniAppx->Chain());
		}
		if (verbose)
		{
			Info << endl;
			Info << " - time estimation: " << global_time_duration << " ms" << endl;
			Info << endl;

			if (myRandAppx)
			{
				Info << " - nb. of points: " << myRandAppx->Chain()->NbPoints() << endl;
			}
			if (myUniAppx)
			{
				Info << " - nb. of points: " << myUniAppx->Chain()->NbPoints() << endl;
			}
		}
	}

	void execute()
	{
		if (verbose)
		{
			printInfo();
		}
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		for (const auto& x : myCurves)
		{
			Debug_Null_Pointer(x);
			execute(x->Curve());

			if (myRandAppx)
			{
				x->Mesh() = myRandAppx->Chain();
			}

			if (myUniAppx)
			{
				x->Mesh() = myUniAppx->Chain();
			}
			
		}
		if (verbose)
		{
			Info << endl;
			Info << " - total time estimation: " << global_time_duration << " ms" << endl;
			Info << endl;
		}
	}

	void estimateD()
	{
		auto iter = myCurves.begin();
		auto box = (*iter)->BoundingBox(0);
		iter++;
		while (iter NOT_EQUAL myCurves.end())
		{
			box = Entity2d_Box::Union(box, (*iter)->BoundingBox(0));
			iter++;
		}
		d = box.Diameter();
	}

	void loadEdges(const std::string& name)
	{
		fileName fn(name);
		std::fstream file;
		file.open(fn, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		TNB_iARCH_FILE_TYPE ia(file);

		ia >> myCurves;
		if (NOT myCurves.size())
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is null" << endl
				<< abort(FatalError);
		}
		for (const auto& x : myCurves)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null edge has been detected!" << endl
					<< abort(FatalError);
			}
		}
		estimateD();
	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);

		oa << myCurves;
		if (verbose)
		{
			Info << " curves are saved in: " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setTarget(x); }), "setTarget");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "setMinSize");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbSubdivision(n); }), "setMaxNbSubdivision");
		mod->add(chaiscript::fun([](int n)-> void {setInitNbSubdivision(n); }), "setInitNbSubdivision");
		mod->add(chaiscript::fun([](int n)-> void {setNbSamples(n); }), "setNbSamples");

		mod->add(chaiscript::fun([](bool v)-> void {verbose = v; }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadEdges(name); }), "loadEdges");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		//mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
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
	FatalError.throwExceptions();

	//Cad2d_RemoveNonManifold::verbose = 1;

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

			fileName myFileName("TnbEdgesDiscretizer2d");

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