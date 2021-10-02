#include <HydStatic_Tools.hxx>

#include <Merge2d_Pnt.hxx>
#include <Cad2d_CmptLib.hxx>
#include <MarineBase_Tools.hxx>
#include <HydStatic_CmptLib.hxx>
#include <HydStatic_GzQ.hxx>
#include <HydStatic_GzQP.hxx>
#include <HydStatic_rAuCurve.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <HydStatic_hArmCurve.hxx>
#include <HydStatic_hAuCurve.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_CrsCurveQ.hxx>
#include <HydStatic_CurveQMaker.hxx>
#include <HydStatic_rArmCurve_Body.hxx>
#include <HydStatic_rArmCurve_FSLq.hxx>
#include <HydStatic_rArmCurve_LDT.hxx>
#include <HydStatic_rArmCurve_LDV.hxx>
#include <HydStatic_rArmCurve_Eff.hxx>
#include <HydStatic_ArmCurveCreator.hxx>
#include <HydStatic_UniformSpacing.hxx>
#include <HydStatic_CustomSpacing.hxx>
#include <HydStatic_rArmCurves.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geo_Tools.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <StdFail_NotDone.hxx>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

Standard_Real 
tnbLib::HydStatic_Tools::CalcWindHeelingArm
(
	const marineLib::Pressure & theWindPrss,
	const marineLib::Av & theAv,
	const marineLib::Hv & theHv,
	const marineLib::T & theDraft, 
	const marineLib::Gravity & theG, 
	const marineLib::DISPM & theDispl,
	const marineLib::HEELANG & theAngl
)
{
	const auto cosPhi = std::cos(theAngl());
	return theWindPrss()*theAv()*(theHv() + 0.5*theDraft())*cosPhi*cosPhi / (theG()*theDispl());
}

Standard_Real 
tnbLib::HydStatic_Tools::CalcTurningHeelingArm
(
	const marineLib::coeff::CD & theCd,
	const marineLib::Velocity & theVel,
	const marineLib::Gravity & theG,
	const marineLib::LPP & theLpp,
	const marineLib::KG & theKg, 
	const marineLib::T & theDraft, 
	const marineLib::HEELANG & theAngl
)
{
	const auto vel2 = theVel()*theVel();
	return theCd()*vel2*(theKg() - 0.5*theDraft())*std::cos(theAngl()) / (theG()*theLpp());
}

namespace tnbLib
{
	std::vector<Standard_Real> HydTessellateX(const double* x, size_t n, const unsigned int nbPts)
	{
		std::vector<Standard_Real> xt;
		xt.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			xt.push_back(x[i]);
		}
		auto xs = MarineBase_Tools::Tessellate(xt, nbPts);
		return std::move(xs);
	}
}

std::vector<tnbLib::hydStcGphLib::xDraft> 
tnbLib::HydStatic_Tools::SteffenTessellation
(
	const std::vector<hydStcGphLib::xDraft>& theQ, 
	const unsigned int nbPts
)
{
	auto x = new double[theQ.size()];
	auto y = new double[theQ.size()];

	for (size_t i = 0; i < theQ.size(); i++)
	{
		x[i] = theQ[i].T;
		y[i] = theQ[i].value;
	}

	gsl_interp_accel *acc = gsl_interp_accel_alloc();
	gsl_spline *spline_steffen = gsl_spline_alloc(gsl_interp_steffen, theQ.size());
	gsl_spline_init(spline_steffen, x, y, theQ.size());

	auto xt = HydTessellateX(x, theQ.size(), nbPts);
	std::vector<hydStcGphLib::xDraft> Q;
	Q.reserve(xt.size());
	for (auto xi : xt)
	{
		double yi_steffen = gsl_spline_eval(spline_steffen, xi, acc);
		auto p = hydStcGphLib::xDraft{ xi,yi_steffen };
		Q.push_back(p);
	}
	return std::move(Q);
}

std::shared_ptr<tnbLib::HydStatic_Spacing> 
tnbLib::HydStatic_Tools::UniformSpacing
(
	const Standard_Integer n, 
	const Standard_Real u0,
	const Standard_Real u1
)
{
	auto spacing = std::make_shared<HydStatic_UniformSpacing>(n);
	spacing->SetLower(u0);
	spacing->SetUpper(u1);
	return std::move(spacing);
}

std::shared_ptr<tnbLib::HydStatic_Spacing> 
tnbLib::HydStatic_Tools::CustomSpacing
(
	const std::vector<Standard_Real>& Us, 
	const Standard_Real u0, 
	const Standard_Real u1
)
{
	if (Us.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough points for the spacing vector" << endl
			<< abort(FatalError);
	}
#ifdef _DEBUG
	for (size_t i = 0; i < Us.size() - 1; i++)
	{
		auto u00 = Us[i];
		auto u11 = Us[i + 1];
		if (u00 >= u11)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid heel values has been detected!" << endl
				<< abort(FatalError);
		}
	}
#endif // _DEBUG
	if (u1 <= u0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid limits has been detected!" << endl
			<< abort(FatalError);
	}

	const auto x0 = Us[0];
	const auto x1 = Us[Us.size() - 1];
	const auto dx = x1 - x0;

	std::vector<Standard_Real> xs;
	xs.reserve(Us.size());
	for (auto x : Us)
	{
		auto t = (x - x0) / dx;
		xs.push_back(u0 + t * (u1 - u0));
	}

	auto spacing = std::make_shared<HydStatic_CustomSpacing>(std::move(xs));
	return std::move(spacing);
}

std::shared_ptr<tnbLib::HydStatic_CrsCurveQ> 
tnbLib::HydStatic_Tools::Trim
(
	const std::shared_ptr<HydStatic_CrsCurveQ>& theCurve, 
	const Standard_Real x0,
	const Standard_Real x1,
	const hydStcLib::CurveMakerType t,
	const Standard_Real tol
)
{
	static auto check_boundaries = [](const Standard_Real x, const Standard_Real bnd, const Standard_Real tol)
	{
		return (Standard_Boolean)(std::abs(x - bnd) <= tol);
	};

	Debug_Null_Pointer(theCurve);
	if (x1 <= x0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data have been detected!" << endl
			<< abort(FatalError);
	}

	auto span0 = theCurve->FindSpan(x0);
	auto span1 = theCurve->FindSpan(x1);

	const auto y0 = theCurve->Value(span0, x0);
	const auto y1 = theCurve->Value(span1, x1);

	std::vector<std::pair<Standard_Real, Standard_Real>> Qs;
	if (NOT check_boundaries(x0, theCurve->Lower(), tol))
	{
		auto paired = std::make_pair(x0, y0);
		Qs.push_back(std::move(paired));
	}

	for (const auto& x : theCurve->Qs())
	{
		auto[xvalue, yvalue] = x;
		if (INSIDE(xvalue, x0, x1))
		{
			auto paired = std::make_pair(xvalue, yvalue);
			Qs.push_back(std::move(paired));
		}
	}

	if (NOT check_boundaries(x1, theCurve->Upper(), tol))
	{
		auto paired = std::make_pair(x1, y1);
		Qs.push_back(std::move(paired));
	}
	auto curve = hydStcLib::MakeCurveQ<HydStatic_CrsCurveQ>(std::move(Qs), t);
	return std::move(curve);
}

std::shared_ptr<tnbLib::HydStatic_CrsCurve> 
tnbLib::HydStatic_Tools::CrossCurve
(
	const Handle(Geom2d_Curve)& theGeom, 
	const hydStcLib::CurveMakerType t
)
{
	auto c = hydStcLib::MakeCurve<HydStatic_CrsCurve>(theGeom, t);
	return std::move(c);
}

std::shared_ptr<tnbLib::HydStatic_CrsCurve>
tnbLib::HydStatic_Tools::CrossCurve
(
	Handle(Geom2d_Curve)&& theGeom,
	const hydStcLib::CurveMakerType t
)
{
	auto c = hydStcLib::MakeCurve<HydStatic_CrsCurve>(std::move(theGeom), t);
	return std::move(c);
}

std::shared_ptr<tnbLib::HydStatic_hArmCurve> 
tnbLib::HydStatic_Tools::HeelingCurve
(
	const std::vector<HydStatic_GzQP>& theQs,
	const hydStcLib::CurveMakerType t
)
{
	const auto offsets = OffsetsFrom(theQs);
	
	auto curve = MarineBase_Tools::Curve(offsets);
	Debug_Null_Pointer(curve);

	auto heeling = hydStcLib::MakeCurve<HydStatic_hArmCurve>(std::move(curve), t);
	Debug_Null_Pointer(heeling);

	heeling->ChangeQs() = theQs;

	HydStatic_CmptLib::CalcParameters(heeling);

	return std::move(heeling);
}

std::shared_ptr<tnbLib::HydStatic_hArmCurve> 
tnbLib::HydStatic_Tools::HeelingCurve
(
	const std::vector<HydStatic_GzQP>&& theQs,
	const hydStcLib::CurveMakerType t
)
{
	auto Qs = std::move(theQs);
	const auto offsets = OffsetsFrom(Qs);

	auto curve = MarineBase_Tools::Curve(offsets);
	Debug_Null_Pointer(curve);

	auto heeling = hydStcLib::MakeCurve<HydStatic_hArmCurve>(std::move(curve), t);
	Debug_Null_Pointer(heeling);

	heeling->SetQs(std::move(Qs));

	HydStatic_CmptLib::CalcParameters(heeling);

	return std::move(heeling);
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_Tools::MirroredByO
(
	const std::vector<HydStatic_GzQ>& theQs
)
{
	const auto O = Pnt2d(0, 0);

	std::vector<HydStatic_GzQ> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto mirroed = x.Mirrored(O);
		Qs.push_back(*mirroed);
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQP>
tnbLib::HydStatic_Tools::MirroredByO
(
	const std::vector<HydStatic_GzQP>& theQs
)
{
	const auto O = Pnt2d(0, 0);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto mirroed = std::dynamic_pointer_cast<HydStatic_GzQP>(x.Mirrored(O));
		Debug_Null_Pointer(mirroed);
		Qs.push_back(*mirroed);
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_Tools::MirroredByOy
(
	const std::vector<HydStatic_GzQ>& theQs
)
{
	const auto ax = gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(0, 1));

	std::vector<HydStatic_GzQ> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto mirroed = x.Mirrored(ax);
		Qs.push_back(*mirroed);
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQP>
tnbLib::HydStatic_Tools::MirroredByOy
(
	const std::vector<HydStatic_GzQP>& theQs
)
{
	const auto ax = gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(0, 1));

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto mirroed = std::dynamic_pointer_cast<HydStatic_GzQP>(x.Mirrored(ax));
		Debug_Null_Pointer(mirroed);
		Qs.push_back(*mirroed);
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_Tools::Merged
(
	const std::vector<HydStatic_GzQ>& theQs
)
{
	std::vector<Pnt2d> pts;
	pts.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto pt = Pnt2d(x.Heel(), x.LeverArm());
		pts.push_back(std::move(pt));
	}

	Merge2d_Pnt alg(pts, 1.0E-3, 1.0E-5);
	alg.Perform();

	Debug_If_Condition_Message(NOT alg.IsDone(), "the merging algorithm is not performed!");

	const auto merged = alg.CompactPoints();
	std::vector<HydStatic_GzQ> Qs;
	for (const auto& x : merged)
	{
		auto q = HydStatic_GzQ(x.X(), x.Y());
		Qs.push_back(std::move(q));
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQP>
tnbLib::HydStatic_Tools::Merged
(
	const std::vector<HydStatic_GzQP>& theQs
)
{
	std::vector<Pnt2d> pts;
	pts.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		auto pt = Pnt2d(x.Heel(), x.LeverArm());
		pts.push_back(std::move(pt));
	}

	Merge2d_Pnt alg(pts, 1.0E-3, 1.0E-5);
	alg.Perform();

	Debug_If_Condition_Message(NOT alg.IsDone(), "the merging algorithm is not performed!");

	const auto merged = alg.CompactPoints();
	std::vector<HydStatic_GzQP> Qs;
	for (const auto& x : merged)
	{
		auto q = HydStatic_GzQP(x.X(), x.Y(), 0);
		Qs.push_back(std::move(q));
	}
	return std::move(Qs);
}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_Body>
tnbLib::HydStatic_Tools::ExpandToPort
(
	const std::shared_ptr<hydStcLib::rArmCurve_Body>& theGZ
)
{
	if (NOT hydStcLib::IsStbHeel(theGZ))
	{
		FatalErrorIn("std::shared_ptr<hydStcLib::rArmCurve_Body> ExpandToPort(const std::shared_ptr<hydStcLib::rArmCurve_Body>& theGZ)")
			<< "for expanding a righting arm to the port, it must be STB!" << endl
			<< abort(FatalError);
	}

	const auto& stQs = theGZ->Qs();
	const auto prtQs = MirroredByO(stQs);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(stQs.size() + prtQs.size());
	for (const auto& x : stQs)
		Qs.push_back(x);
	for (const auto& x : prtQs)
		Qs.push_back(x);

	const auto mQs = Merged(Qs);

	const auto offsets = OffsetsFrom(Qs);

	const auto curve = MarineBase_Tools::Curve(offsets);

	auto rArm = std::make_shared<hydStcLib::CurveMaker_SymmHeel<hydStcLib::rArmCurve_Body>>(std::move(curve));
	Debug_Null_Pointer(rArm);

	HydStatic_CmptLib::CalcParameters(rArm);

	rArm->SetQs(std::move(mQs));
	return std::move(rArm);
}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_FSLq>
tnbLib::HydStatic_Tools::ExpandToPort
(
	const std::shared_ptr<hydStcLib::rArmCurve_FSLq>& theGZ
)
{
	if (NOT hydStcLib::IsStbHeel(theGZ))
	{
		FatalErrorIn("std::shared_ptr<hydStcLib::rArmCurve_FSLq> ExpandToPort(const std::shared_ptr<hydStcLib::rArmCurve_FSLq>& theGz)")
			<< "for expanding a righting arm to the port, it must be STB!" << endl
			<< abort(FatalError);
	}

	const auto& stQs = theGZ->Qs();
	const auto prtQs = MirroredByO(stQs);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(stQs.size() + prtQs.size());
	for (const auto& x : stQs)
		Qs.push_back(x);
	for (const auto& x : prtQs)
		Qs.push_back(x);

	const auto mQs = Merged(Qs);

	const auto offsets = OffsetsFrom(Qs);

	const auto curve = MarineBase_Tools::Curve(offsets);

	auto rArm = std::make_shared<hydStcLib::CurveMaker_SymmHeel<hydStcLib::rArmCurve_FSLq>>(std::move(curve));
	Debug_Null_Pointer(rArm);

	HydStatic_CmptLib::CalcParameters(rArm);

	rArm->SetQs(std::move(mQs));
	return std::move(rArm);
}

//std::shared_ptr<tnbLib::hydStcLib::rArmCurve_Hlds>
//tnbLib::HydStatic_Tools::ExpandToPort
//(
//	const std::shared_ptr<hydStcLib::rArmCurve_Hlds>& theGZ
//)
//{
//	if (NOT hydStcLib::IsStbHeel(theGZ))
//	{
//		FatalErrorIn("std::shared_ptr<hydStcLib::rArmCurve_Hlds> ExpandToPort(const std::shared_ptr<hydStcLib::rArmCurve_Hlds>& theGz)")
//			<< "for expanding a righting arm to the port, it must be STB!" << endl
//			<< abort(FatalError);
//	}
//
//	const auto& stQs = theGZ->Qs();
//	const auto prtQs = MirroredByO(stQs);
//
//	std::vector<HydStatic_GzQP> Qs;
//	Qs.reserve(stQs.size() + prtQs.size());
//	for (const auto& x : stQs)
//		Qs.push_back(x);
//	for (const auto& x : prtQs)
//		Qs.push_back(x);
//
//	const auto mQs = Merged(Qs);
//
//	const auto offsets = OffsetsFrom(Qs);
//
//	const auto curve = MarineBase_Tools::Curve(offsets);
//
//	auto rArm = std::make_shared<hydStcLib::ArmCurveCreator_SymmHeel<hydStcLib::rArmCurve_Hlds>>(curve);
//	Debug_Null_Pointer(rArm);
//
//	HydStatic_CmptLib::CalcParameters(rArm);
//
//	rArm->SetQs(std::move(mQs));
//}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_LDT> 
tnbLib::HydStatic_Tools::ExpandToPort
(
	const std::shared_ptr<hydStcLib::rArmCurve_LDT>& theGZ
)
{
	if (NOT hydStcLib::IsStbHeel(theGZ))
	{
		FatalErrorIn("std::shared_ptr<hydStcLib::rArmCurve_LDT> ExpandToPort(const std::shared_ptr<hydStcLib::rArmCurve_LDT>& theGz)")
			<< "for expanding a righting arm to the port, it must be STB!" << endl
			<< abort(FatalError);
	}

	const auto& stQs = theGZ->Qs();
	const auto prtQs = MirroredByOy(stQs);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(stQs.size() + prtQs.size());
	for (const auto& x : stQs)
		Qs.push_back(x);
	for (const auto& x : prtQs)
		Qs.push_back(x);

	const auto mQs = Merged(Qs);

	const auto offsets = OffsetsFrom(Qs);

	const auto curve = MarineBase_Tools::Curve(offsets);

	auto rArm = std::make_shared<hydStcLib::CurveMaker_SymmHeel<hydStcLib::rArmCurve_LDT>>(std::move(curve));
	Debug_Null_Pointer(rArm);

	rArm->SetD(theGZ->D());
	HydStatic_CmptLib::CalcParameters(rArm);

	rArm->SetQs(std::move(mQs));
	return std::move(rArm);
}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_LDV> 
tnbLib::HydStatic_Tools::ExpandToPort
(
	const std::shared_ptr<hydStcLib::rArmCurve_LDV>& theGZ
)
{
	if (NOT hydStcLib::IsStbHeel(theGZ))
	{
		FatalErrorIn("std::shared_ptr<hydStcLib::rArmCurve_LDV> ExpandToPort(const std::shared_ptr<hydStcLib::rArmCurve_LDV>& theGz)")
			<< "for expanding a righting arm to the port, it must be STB!" << endl
			<< abort(FatalError);
	}

	const auto& stQs = theGZ->Qs();
	const auto prtQs = MirroredByO(stQs);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(stQs.size() + prtQs.size());
	for (const auto& x : stQs)
		Qs.push_back(x);
	for (const auto& x : prtQs)
		Qs.push_back(x);

	const auto mQs = Merged(Qs);

	const auto offsets = OffsetsFrom(Qs);

	const auto curve = MarineBase_Tools::Curve(offsets);

	auto rArm = std::make_shared<hydStcLib::CurveMaker_SymmHeel<hydStcLib::rArmCurve_LDV>>(std::move(curve));
	Debug_Null_Pointer(rArm);

	rArm->SetD(theGZ->D());
	HydStatic_CmptLib::CalcParameters(rArm);

	rArm->SetQs(std::move(mQs));
	return std::move(rArm);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::HydStatic_Tools::OffsetsFrom
(
	const std::vector<HydStatic_GzQ>& theQs
)
{
	std::vector<marineLib::xSectionParam> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		marineLib::xSectionParam par = { x.Heel(),x.LeverArm() };
		Qs.push_back(std::move(par));
	}
	return std::move(Qs);
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::HydStatic_Tools::OffsetsFrom
(
	const std::vector<HydStatic_GzQP>& theQs
)
{
	std::vector<marineLib::xSectionParam> Qs;
	Qs.reserve(theQs.size());
	for (const auto& x : theQs)
	{
		marineLib::xSectionParam par = { x.Heel(),x.LeverArm() };
		Qs.push_back(std::move(par));
	}
	return std::move(Qs);
}

Standard_Boolean 
tnbLib::HydStatic_Tools::IsCoating
(
	const std::shared_ptr<HydStatic_rArmCurve>& theArm, 
	const std::shared_ptr<HydStatic_rArmCurve>& theTarget
)
{
	Debug_Null_Pointer(theArm);
	Debug_Null_Pointer(theTarget);

	auto h0 = theArm->MinHeel();
	auto h1 = theArm->MaxHeel();

	if (NOT INSIDE(theTarget->MinHeel(), h0, h1))
	{
		return Standard_False;
	}
	if (NOT INSIDE(theTarget->MaxHeel(), h0, h1))
	{
		return Standard_False;
	}
	return Standard_True;
}

namespace tnbLib
{
	namespace hydStcTools
	{
		std::vector<HydStatic_GzQ> Union
		(
			const HydStatic_rArmCurve& theC0,
			const HydStatic_rArmCurve& theC1
		)
		{
			std::vector<HydStatic_GzQ> Qs;
			Qs.reserve(theC1.Qs().size());

			for (const auto& x : theC1.Qs())
			{
				auto h = x.Heel();
				auto a1 = x.LeverArm();

				auto a2 = theC0.Value(h);

				HydStatic_GzQ q(h, a1 + a2);
				Qs.push_back(std::move(q));
			}
			return std::move(Qs);
		}

		std::vector<HydStatic_GzQ> Subtract
		(
			const HydStatic_rArmCurve& theC0,
			const HydStatic_rArmCurve& theC1
		)
		{
			std::vector<HydStatic_GzQ> Qs;
			Qs.reserve(theC1.Qs().size());

			for (const auto& x : theC1.Qs())
			{
				auto h = x.Heel();
				auto a1 = x.LeverArm();

				auto a2 = theC0.Value(h);

				HydStatic_GzQ q(h, a1 - a2);
				Qs.push_back(std::move(q));
			}
			return std::move(Qs);
		}
	}
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_Tools::Union
(
	const std::shared_ptr<HydStatic_rArmCurve>& theC0,
	const std::shared_ptr<HydStatic_rArmCurve>& theC1
)
{
	if (IsCoating(theC0, theC1))
	{
		auto Qs = hydStcTools::Union(*theC0, *theC1);
		return std::move(Qs);
	}
	else if (IsCoating(theC1, theC0))
	{
		auto Qs = hydStcTools::Union(*theC1, *theC0);
		return std::move(Qs);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "no coating curve has been detected!" << endl
			<< abort(FatalError);
		std::vector<tnbLib::HydStatic_GzQ> Qs;
		return std::move(Qs);
	}
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_Tools::Subtract
(
	const std::shared_ptr<HydStatic_rArmCurve>& theC0,
	const std::shared_ptr<HydStatic_rArmCurve>& theC1
)
{
	if (IsCoating(theC0, theC1))
	{
		auto Qs = hydStcTools::Subtract(*theC0, *theC1);
		return std::move(Qs);
	}
	else if (IsCoating(theC1, theC0))
	{
		auto Qs = hydStcTools::Subtract(*theC1, *theC0);
		return std::move(Qs);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "no coating curve has been detected!" << endl
			<< abort(FatalError);
		std::vector<tnbLib::HydStatic_GzQ> Qs;
		return std::move(Qs);
	}
}

std::shared_ptr<tnbLib::HydStatic_hArmCurve> 
tnbLib::HydStatic_Tools::MakeHeelCurve
(
	const std::vector<marineLib::xSectionParam>& theQs
)
{
	const auto curve = MarineBase_Tools::Curve(theQs);

	const auto rArm = 
		hydStcLib::MakeCurve<HydStatic_hArmCurve>
		(
			std::move(curve), 
			hydStcLib::CurveMakerType::arbitrary
			);

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(theQs.size());

	for (const auto& x : theQs)
	{
		HydStatic_GzQP par(x.x, x.value, 0);
		Qs.push_back(std::move(par));
	}

	rArm->SetQs(std::move(Qs));
	return std::move(rArm);
}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_Eff> 
tnbLib::HydStatic_Tools::MakeEffRightCurve
(
	const std::vector<marineLib::xSectionParam>& theQs
)
{
	const auto curve = MarineBase_Tools::Curve(theQs);

	const auto rArm = std::make_shared<hydStcLib::rArmCurve_Eff>(std::move(curve));

	std::vector<HydStatic_GzQP> Qs;
	Qs.reserve(theQs.size());

	for (const auto& x : theQs)
	{
		HydStatic_GzQP par(x.x, x.value, 0);
		Qs.push_back(std::move(par));
	}

	rArm->SetQs(std::move(Qs));
	return std::move(rArm);
}

std::shared_ptr<tnbLib::hydStcLib::rArmCurve_Tanks> 
tnbLib::HydStatic_Tools::MakeTanksRightCurve
(
	std::shared_ptr<hydStcLib::rArmCurve_Cmpt<hydStcLib::rArmCurve_FSLq>>&& theCmpt
)
{
	Debug_Null_Pointer(theCmpt);
	const auto& curves = theCmpt->Curves();
	if (curves.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the curves list is empty!" << endl
			<< abort(FatalError);
	}

	const auto t = hydStcLib::RetrieveType(theCmpt);
	auto iter = curves.begin();
	auto c0 = *iter;
	iter++;

	while (iter NOT_EQUAL curves.end())
	{
		auto c1 = *iter;

		auto Qs = HydStatic_Tools::Union(c0, c1);
		c0 = MakeRightCurve<hydStcLib::rArmCurve_FSLq>(HydStatic_Tools::OffsetsFrom(Qs), t);

		iter++;
	}
	
	auto curve = std::make_shared<hydStcLib::rArmCurve_Tanks>(c0->Geometry(), std::move(theCmpt));
	Debug_Null_Pointer(curve);

	curve->SetName("tanks righting-arm curve");
	auto& Qs = curve->ChangeQs();
	Qs.reserve(c0->Qs().size());

	for (const auto& x : c0->Qs())
	{
		HydStatic_GzQP par(x.Heel(), x.LeverArm(), 0);
		Qs.push_back(std::move(par));
	}
	return std::move(curve);
}

//std::shared_ptr<tnbLib::HydStatic_rArmCurve> 
//tnbLib::HydStatic_Tools::ExpandRigthingArmToPort
//(
//	const HydStatic_rArmCurve & theCurve,
//	const marineLib::KG & theKG
//)
//{
//	Debug_Null_Pointer(theCurve.AuCurve());
//	const auto& AuC = *theCurve.AuCurve();
//
//	const auto& old_Qs = AuC.Qs();
//	Debug_If_Condition(old_Qs.empty());
//
//	if (old_Qs[0].Heel() < 0)
//	{
//		FatalErrorIn("std::shared_ptr<HydStatic_rArmCurve> HydStatic_Tools::ExpandRigthingArmToPort(Args...)")
//			<< "unable to expand the arm-curve: the curve must be starboard only" << endl
//			<< abort(FatalError);
//	}
//
//	const auto kg = theKG();
//
//	std::vector<HydStatic_GzQ> Qs;
//	Qs.reserve(old_Qs.size() * 2 - 1);
//	
//	auto iter = old_Qs.end();
//	iter--;
//	while (iter NOT_EQUAL old_Qs.begin())
//	{
//		const auto& x = *iter;
//
//		auto lk = x.LeverArm() + kg * sin(Geo_Tools::DegToRadian(x.Heel()));
//		HydStatic_GzQ q(-x.Heel())
//	}
//}

void tnbLib::HydStatic_Tools::AuCurve
(
	const std::shared_ptr<hydStcLib::rArmCurve_Eff>& theCurve,
	const hydStcLib::CurveMakerType t,
	const Standard_Real y0,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theCurve);

	const auto Qs = HydStatic_CmptLib::CalcAuCurve(*theCurve, y0, theInfo);
	const auto rAu = HydStatic_rAuCurve::AuCurve(Qs, t);
	Debug_Null_Pointer(rAu);

	theCurve->SetAuCurve(std::move(rAu));
}

void tnbLib::HydStatic_Tools::AuCurve
(
	const std::shared_ptr<HydStatic_hArmCurve>& theCurve,
	const hydStcLib::CurveMakerType t,
	const Standard_Real y0,
	const std::shared_ptr<info>& theInfo
)
{
	Debug_Null_Pointer(theCurve);

	const auto Qs = HydStatic_CmptLib::CalcAuCurve(*theCurve, y0, theInfo);
	const auto hAu = HydStatic_hAuCurve::AuCurve(Qs, t);
	Debug_Null_Pointer(hAu);

	theCurve->SetAuCurve(std::move(hAu));
}