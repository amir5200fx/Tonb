#include <Pln_Curve.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_FieldFuns.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_GeoMap.hxx>
#include <SectPx_Pars.hxx>
#include <SectPx_Datums.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_FrameTuner.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_CurveQ.hxx>
#include <SectPx_Pole.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>
#include <TecPlot.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <frameMaker.hxx>
#include <frameTuner.hxx>

#include <Geom2d_BSplineCurve.hxx>

#include <map>

namespace tnbLib
{

	static appl::tuner_t myTuner;

	static bool verbose = false;
	static bool loaded = false;
	static int degree = 3;

	static std::shared_ptr<maker::CurveQ> myCurveMaker;
	static std::map<int, std::shared_ptr<Pln_Curve>> myCurveMap;

	//- globals

	void checkFrame()
	{
		if (NOT loaded)
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded" << endl
				<< abort(FatalError);
		}
	}

	const auto& getFrameRegistry()
	{
		checkFrame();
		return myTuner->FrameRegistry();
	}

	const auto& getScatterReg()
	{
		checkFrame();
		return myTuner->FrameRegistry()->Scatter();
	}

	void loadTuner(const std::string& name)
	{

		fileName fn(name);
		std::ifstream f(fn);

		boost::archive::polymorphic_text_iarchive ia(f);

		ia >> myTuner;

		if (verbose)
		{
			Info << " the tuner has been loaded successfully!" << endl;
		}

		if (NOT myTuner)
		{
			FatalErrorIn(FunctionSIG)
				<< "no tuner has been detected" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->FrameRegistry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no registry has been detected for the frame" << endl
				<< abort(FatalError);
		}
		if (NOT myTuner->IsFrameLoaded())
		{
			FatalErrorIn(FunctionSIG)
				<< "no frame has been loaded into the tuner!" << endl
				<< abort(FatalError);
		}

		myCurveMaker = std::make_shared<maker::CurveQ>(myTuner->FrameRegistry());
		loaded = true;
	}

	void printPoles()
	{
		const auto& poles = getScatterReg()->ScatterMap(SectPx_RegObjType::pole);
		Info << " nb. of poles: " << poles.size() << endl;
		Info << " the list of the poles: " << endl;
		for (const auto& x : poles)
		{
			auto p = std::dynamic_pointer_cast<SectPx_Pole>(x.second.lock());
			Debug_Null_Pointer(p);

			Info << " - " << "index: " 
				<< p->Index() << ", " 
				<< p->Name() << ", value: " 
				<< p->Coord() << endl;
		}
	}

	void printCurves()
	{
		const auto& curves = getScatterReg()->ScatterMap(SectPx_RegObjType::curveQ);
		Info << " nb. of curves: " << curves.size() << endl;
		Info << " the list of the curves: " << endl;
		for (const auto& x : curves)
		{
			auto c = std::dynamic_pointer_cast<SectPx_CurveQ>(x.second.lock());
			Debug_Null_Pointer(c);

			Info << " - " << "index: " << c->Index() << ", " << c->Name() << endl;
			Info << "   from pole: " 
				<< c->Pole0()->Index() 
				<< ", to pole: " << c->Pole1()->Index() 
				<< endl;
		}
	}
}