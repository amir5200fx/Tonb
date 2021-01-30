#include <Pnt2d.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <StbGMaker_Model.hxx>
#include <HydStatic_GZ.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <algorithm>
#include <vector>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	static const unsigned int DEFAULT_NB_DIVISIONS_LOW = 15;
	static const unsigned int DEFAULT_NB_DIVISIONS_MEDIUM = 25;
	static const unsigned int DEFAULT_NB_DIVISIONS_HIGH = 60;

	static const auto myGz = std::make_shared<HydStatic_GZ>();
	static bool verbose = false;
	static auto nPnts = DEFAULT_NB_DIVISIONS_LOW;

	typedef std::shared_ptr<StbGMaker_Model> model_t;
	static model_t myModel;

	void setTessellation(const word& t)
	{
		if (t IS_EQUAL "low")
		{
			nPnts = DEFAULT_NB_DIVISIONS_LOW;
		}
		else if (t IS_EQUAL "medium")
		{
			nPnts = DEFAULT_NB_DIVISIONS_MEDIUM;
		}
		else if (t IS_EQUAL "high")
		{
			nPnts = DEFAULT_NB_DIVISIONS_HIGH;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined tessellation type" << endl
				<< abort(FatalError);
		}
	}

	void loadCrossCurves(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		std::shared_ptr<HydStatic_CrossCurves> curves;
		ar >> curves;
		if (NOT curves)
		{
			FatalErrorIn(FunctionSIG)
				<< "cross-curves graph is null" << endl
				<< abort(FatalError);
		}
		myGz->LoadCrossCurves(curves);

		ar >> myModel;
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "stability model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the cross-curves are loaded, successfully" << endl;
			Info << endl;
		}
	}

	void setVerbose(bool v)
	{
		HydStatic_GZ::verbose = v;
		verbose = v;
	}

	/*void setKG(double x)
	{
		marineLib::KG kg(x);
		myGz->SetKG(std::move(kg));
	}*/

	void checkModel()
	{
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}
	}

	void setVcg(double x)
	{
		checkModel();
		const auto& body = myModel->Hull()->Body();
		myModel->LightWeight().Vcg().Value() = body->BaseLine().BaseLine().Location().Z() + x;
	}

	void setTcg(double x)
	{
		checkModel();
		const auto& body = myModel->Hull()->Body();
		myModel->LightWeight().Tcg().Value() = body->BaseLine().BaseLine().Location().Y() + x;
	}

	void setDispv(double x)
	{
		marineLib::DISPV d(x);
		myGz->SetDispv(std::move(d));
	}

	void execute()
	{
		if (NOT myModel->LightWeight().Vcg().IsSpecified())
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'VCG' is specified for the model" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " - VCG: " << myModel->LightWeight().Vcg()() << endl;
			if (myModel->LightWeight().Tcg().IsSpecified()) Info << " - TCG: " << myModel->LightWeight().Tcg()() << endl;
		}
		const auto& body = myModel->Hull()->Body();
		const auto kg = myModel->LightWeight().Vcg()() - body->BaseLine().BaseLine().Location().Z();
		myGz->SetKG(marineLib::KG(kg));

		myGz->Perform();
	}

	auto getPoints(const Handle(Geom2d_Curve)& theCurve)
	{
		const auto u1 = theCurve->LastParameter();
		const auto u0 = theCurve->FirstParameter();

		const auto du = (u1 - u0) / (Standard_Real)(nPnts - 1);
		std::vector<Pnt2d> pnts;
		pnts.reserve(nPnts);
		for (size_t i = 0; i <= nPnts; i++)
		{
			auto pt = theCurve->Value(u0 + i * du);
			pnts.push_back(std::move(pt));
		}
		return std::move(pnts);
	}

	void exportToPlt(const std::string& name)
	{
		if (NOT myGz->IsDone())
		{
			FatalErrorIn(FunctionSIG)
				<< " the algorithm is not performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		OFstream f(fn);

		const auto& curve = myGz->RightingArm();
		auto pnts = getPoints(curve->Geometry());
		Io::ExportCurve(pnts, f);
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
		mod->add(chaiscript::fun([](bool v)->void {setVerbose(v); }), "setVerbose");
		//mod->add(chaiscript::fun([](double x)->void {setKG(x); }), "setKG");
		mod->add(chaiscript::fun([](double x)->void {setDispv(x); }), "setDispv");
		mod->add(chaiscript::fun([](double x)->void {setVcg(x); }), "setVcg");
		mod->add(chaiscript::fun([](double x)->void {setTcg(x); }), "setTcg");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

		mod->add(chaiscript::fun([](const std::string& t)-> void {setTessellation(t); }), "setTessellation");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCrossCurves(name); }), "loadCrossCurves");

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

			fileName myFileName("Gz");

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