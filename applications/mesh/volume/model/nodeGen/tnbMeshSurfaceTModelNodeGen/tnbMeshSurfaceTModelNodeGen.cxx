#include <Aft2d_OptNodeSurface_nonIterAdaptive.hxx>
#include <Aft2d_OptNodeSurface_Altr.hxx>
#include <Aft2d_OptNodeSurface_Standard.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_IterAdaptive.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptive.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Standard.hxx>
#include <Aft2d_AltrOptNodeSurface_DE.hxx>
#include <Aft2d_AltrOptNodeSurface_DE_Info.hxx>
#include <Aft2d_AltrOptNodeSurface_MetricCorr.hxx>
#include <Aft2d_AltrOptNodeSurface_NelderMead.hxx>
#include <Aft2d_AltrOptNodeSurface_PerpenDir.hxx>
#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Aft2d_OptNodeSurface_Calculator> myNodeCalculator;
	static std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator> myUniMetricNodeCalculator;

	static unsigned short verbose = 0;


	// Alternative algorithms [3/15/2023 Payvand]

	

	auto createAltrNodeGenDe(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo)
	{
		auto alg = std::make_shared<Aft2d_AltrOptNodeSurface_DE>(theInfo);
		return std::move(alg);
	}

	auto createSizeCorrIterInfo()
	{
		auto theInfo = std::make_shared<Aft_SizeCorr_IterativeInfo>();

	}

	auto createAltrNodeGenDeInfo()
	{
		auto theInfo = std::make_shared<Aft2d_AltrOptNodeSurface_DE_Info>();
		return std::move(theInfo);
	}

	void setGenSize(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, int n)
	{
		theInfo->SetGenSize(n);
		if (verbose)
		{
			Info << endl
				<< " - the generation size is set to: " << n << endl;
		}
	}

	void SetPopSize(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, int n)
	{
		theInfo->SetPopSize(n);
		if (verbose)
		{
			Info << endl
				<< " - the population size is set to: " << n << endl;
		}
	}

	void SetMutWeight(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, double x)
	{
		theInfo->SetMutWeight(x);
		if (verbose)
		{
			Info << endl
				<< " - the mutation weight is set to: " << x << endl;
		}
	}

	void SetMutCross(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, double x)
	{
		theInfo->SetMutCross(x);
		if (verbose)
		{
			Info << endl
				<< " - the mutation cross is set to: " << x << endl;
		}
	}

	void PrintDefaults()
	{
		Info << endl;
		Info << " # Iterative coeff. of size correction: " << endl
			<< endl
			<< " - max. no. of iterations = " << Aft_SizeCorr_IterativeInfo::DEFAULT_MAX_NB_ITERATIONS << endl
			<< " - Tolerance = " << Aft_SizeCorr_IterativeInfo::DEFAULT_TOLERANCE << endl
			<< " - Under relaxation = " << Aft_SizeCorr_IterativeInfo::DEFAULT_UNDER_RELAXATION << endl
			<< " - Ignore non-convergence? TRUE" << endl;


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

		// settings [3/15/2023 Payvand]
		mod->add(chaiscript::fun([](const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, int n)-> void {setGenSize(theInfo, n); }), "setGenSize");
		mod->add(chaiscript::fun([](const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, int n)-> void {SetPopSize(theInfo, n); }), "setPopSize");
		mod->add(chaiscript::fun([](const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, double x)-> void {SetMutWeight(theInfo, x); }), "setMutWeight");
		mod->add(chaiscript::fun([](const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo, double x)-> void {SetMutCross(theInfo, x); }), "setMutCross");

		// operators [3/15/2023 Payvand]
		mod->add(chaiscript::fun([]()->auto {return createAltrNodeGenDeInfo(); }), "createAlterNodeGen_DE_Info");
	}
}