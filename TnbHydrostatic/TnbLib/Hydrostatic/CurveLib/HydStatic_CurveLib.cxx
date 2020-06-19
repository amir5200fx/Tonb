#include <HydStatic_CurveLib.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_WireFrameModel.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_CmptLib.hxx>
#include <Marine_DisctLib.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_System.hxx>
#include <MarineBase_Tools.hxx>
#include <HydStatic_HydGphCurves.hxx>

namespace tnbLib
{
	const Standard_Real HydStatic_CurveLib::DEFAULT_MAX_TOL(1.0E-3);
	const Standard_Real HydStatic_CurveLib::DEFAULT_MIN_TOL(1.0E-6);

	Standard_Real HydStatic_CurveLib::theMaxTol_(DEFAULT_MAX_TOL);
	Standard_Real HydStatic_CurveLib::theMinTol_(DEFAULT_MIN_TOL);
}

Standard_Real 
tnbLib::HydStatic_CurveLib::MinTol()
{
	return theMinTol_;
}

Standard_Real 
tnbLib::HydStatic_CurveLib::MaxTol()
{
	return theMaxTol_;
}

void tnbLib::HydStatic_CurveLib::SetMinTol
(
	const Standard_Real theTol
)
{
	theMinTol_ = theTol;
}

void tnbLib::HydStatic_CurveLib::SetMaxTol
(
	const Standard_Real theTol
)
{
	theMaxTol_ = theTol;
}

std::vector<tnbLib::hydStcGphLib::xDraft>
tnbLib::HydStatic_CurveLib::CalcLCB
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies, 
	const std::vector<Standard_Real>& theTs,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto lcb = Marine_CmptLib::CalcLCB(*x, 0, theInfo);
		
		auto p = hydStcGphLib::xDraft{ theTs[k++], lcb() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft>
tnbLib::HydStatic_CurveLib::CalcLCB
(
	const Marine_WireFrameModel & theModel,
	const Geo_xDistb & theDistb, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto lcb = Marine_CmptLib::CalcLCB(*wbody, 0, theInfo);

		auto p = hydStcGphLib::xDraft{ h, lcb() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcLCF
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies, 
	const std::vector<Standard_Real>& theTs,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto lcf = Marine_CmptLib::CalcLCF(*x, 0, theInfo);

		auto p = hydStcGphLib::xDraft{ theTs[k++], lcf() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcLCF
(
	const Marine_WireFrameModel & theModel,
	const Geo_xDistb & theDistb, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto lcf = Marine_CmptLib::CalcLCF(*wbody, 0, theInfo);

		auto p = hydStcGphLib::xDraft{ h, lcf() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcAW
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
	const std::vector<Standard_Real>& theTs,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->WL());

		auto aw = Marine_CmptLib::CalcAW(*x->WL(), theInfo);

		auto p = hydStcGphLib::xDraft{ theTs[k++], aw() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcAW
(
	const Marine_WireFrameModel & theModel,
	const Geo_xDistb & theDistb,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto aw = Marine_CmptLib::CalcAW(*wbody->WL(), theInfo);

		auto p = hydStcGphLib::xDraft{ h, aw() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcDISPV
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
	const std::vector<Standard_Real>& theTs,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto d = Marine_CmptLib::CalcDISPV(*x, theInfo);

		auto p = hydStcGphLib::xDraft{ theTs[k++], d() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft>
tnbLib::HydStatic_CurveLib::CalcDISPV
(
	const Marine_WireFrameModel & theModel,
	const Geo_xDistb & theDistb, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto d = Marine_CmptLib::CalcDISPV(*wbody, theInfo);

		auto p = hydStcGphLib::xDraft{ h, d() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcMCT
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
	const std::vector<hydStcGphLib::xDraft>& theVolume,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto app = Marine_CmptLib::CalcAPP(*x);
		auto fpp = Marine_CmptLib::CalcFPP(*x);

		const auto& h = theVolume[k++];

		auto vol = marineLib::DISPV(h.value);
		auto t = h.T;

		auto bml = Marine_CmptLib::CalcBML(*x->WL(), 0, vol, theInfo);
		auto mct = Marine_CmptLib::CalcMCT(bml, vol, Marine_CmptLib::CalcLPP(app, fpp));

		auto p = hydStcGphLib::xDraft{ t, mct() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcMCT
(
	const Marine_WireFrameModel & theModel, 
	const Geo_xDistb & theDistb, 
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto dispv = Marine_CmptLib::CalcDISPV(*wbody, theInfo);

		auto app = Marine_CmptLib::CalcAPP(*wbody);
		auto fpp = Marine_CmptLib::CalcFPP(*wbody);

		auto bml = Marine_CmptLib::CalcBML(*wbody->WL(), 0, dispv, theInfo);
		auto mct = Marine_CmptLib::CalcMCT(bml, dispv, Marine_CmptLib::CalcLPP(app, fpp));

		auto p = hydStcGphLib::xDraft{ h, mct() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcKB
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
	const Marine_BaseLine & theBase, 
	const std::vector<Standard_Real>& theTs,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto kb = Marine_CmptLib::CalcKB(*x, theBase, theInfo);

		auto p = hydStcGphLib::xDraft{ theTs[k++], kb() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcKB
(
	const Marine_WireFrameModel & theModel,
	const Marine_BaseLine & theBase,
	const Geo_xDistb & theDistb,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto kb = Marine_CmptLib::CalcKB(*wbody, theBase, theInfo);

		auto p = hydStcGphLib::xDraft{ h, kb() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcBM
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies,
	const std::vector<hydStcGphLib::xDraft>& theVolume,
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto vol = marineLib::DISPV(theVolume[k].value);

		auto bm = Marine_CmptLib::CalcBM(*x->WL(), 0, vol, theInfo);

		auto p = hydStcGphLib::xDraft{ theVolume[k++].T, bm() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcBM
(
	const Marine_WireFrameModel & theModel, 
	const Geo_xDistb & theDistb,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto vol = Marine_CmptLib::CalcDISPV(*wbody, theInfo);

		auto bm = Marine_CmptLib::CalcBM(*wbody->WL(), 0, vol, theInfo);

		auto p = hydStcGphLib::xDraft{ h, bm() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcBML
(
	const std::vector<std::shared_ptr<marineLib::Body_Wetted>>& theBodies, 
	const std::vector<hydStcGphLib::xDraft>& theVolume, 
	const std::shared_ptr<info>& theInfo
)
{
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(theBodies.size());

	size_t k = 0;
	for (const auto& x : theBodies)
	{
		Debug_Null_Pointer(x);

		auto vol = marineLib::DISPV(theVolume[k].value);

		auto bml = Marine_CmptLib::CalcBML(*x->WL(), 0, vol, theInfo);

		auto p = hydStcGphLib::xDraft{ theVolume[k++].T, bml() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_CurveLib::CalcBML
(
	const Marine_WireFrameModel & theModel,
	const Geo_xDistb & theDistb,
	const std::shared_ptr<Marine_Domain>& theDomain,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theModel.Body());
	const auto& body = theModel.Body();

	std::vector<hydStcGphLib::xDraft> Q;
	for (const auto h : theDistb.Values())
	{
		auto water = Marine_WaterLib::StillWaterDomain(body, theDomain, h);
		Debug_Null_Pointer(water);

		auto wbody = Marine_DisctLib::WettedBody(theModel, *water, MinTol(), MaxTol());
		Debug_Null_Pointer(wbody);

		auto vol = Marine_CmptLib::CalcDISPV(*wbody, theInfo);

		auto bml = Marine_CmptLib::CalcBML(*wbody->WL(), 0, vol, theInfo);

		auto p = hydStcGphLib::xDraft{ h, bml() };
		Q.push_back(std::move(p));
	}
	return std::move(Q);
}