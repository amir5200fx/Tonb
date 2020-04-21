#include <HydStatic_CmptLib.hxx>

#include <Entity2d_Box.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Marine_Body.hxx>
#include <Marine_CmpSection.hxx>
#include <MarineBase_Tools.hxx>
#include <HydStatic_CrsCurve.hxx>
#include <HydStatic_Bonjean.hxx>
#include <HydStatic_BnjCurve.hxx>
#include <HydStatic_GzQ.hxx>
#include <HydStatic_GzQP.hxx>
#include <HydStatic_GzQP2.hxx>
#include <HydStatic_EqQ.hxx>
#include <HydStatic_StEqQ.hxx>
#include <HydStatic_UnEqQ.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <HydStatic_ArmCurve.hxx>
#include <HydStatic_rArmCurve.hxx>
#include <HydStatic_hArmCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Line.hxx>
#include <IntRes2d_IntersectionPoint.hxx>
#include <IntRes2d_IntersectionSegment.hxx>
#include <Geom2dAPI_ExtremaCurveCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <GCE2d_MakeSegment.hxx>

Standard_Real 
tnbLib::HydStatic_CmptLib::CalcArea
(
	const HydStatic_ArmCurve & theCurve, 
	const Standard_Real y0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto& geom = theCurve.Geometry();
	Debug_Null_Pointer(geom);

	const auto area = Cad2d_CmptLib::AreaUnderCurve(geom, y0, theInfo);
	return area;
}

Standard_Real 
tnbLib::HydStatic_CmptLib::Draft
(
	const Standard_Real x, 
	const Standard_Real theTa, 
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	if (xTf <= xTa)
	{
		FatalErrorIn("Standard_Real Draft(Args...)")
			<< "Invalid data: " << endl
			<< " xTA = " << xTa << endl
			<< " xTF = " << xTf << endl
			<< abort(FatalError);
	}

	const auto m = (theTf - theTa) / (xTf - xTa);
	const auto d = m * (x - xTa) + theTa;
	return d;
}

Standard_Real 
tnbLib::HydStatic_CmptLib::Draft
(
	const Marine_CmpSection & theSect, 
	const Standard_Real theTa,
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	const auto x = theSect.X();
	return Draft(x, theTa, xTa, theTf, xTf);
}

std::vector<Standard_Real> 
tnbLib::HydStatic_CmptLib::RetrieveDrafts
(
	const Marine_Body & theBody,
	const Standard_Real theTa,
	const Standard_Real xTa, 
	const Standard_Real theTf,
	const Standard_Real xTf
)
{
	std::vector<Standard_Real> drafts;
	drafts.reserve(theBody.NbSections());

	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);

		auto d = Draft(*x, theTa, xTa, theTf, xTf);
		drafts.push_back(d);
	}
	return std::move(drafts);
}

std::vector<Standard_Real> 
tnbLib::HydStatic_CmptLib::RetrieveXs
(
	const Marine_Body & theBody
)
{
	std::vector<Standard_Real> X;
	X.reserve(theBody.NbSections());

	for (const auto& x : theBody.Sections())
	{
		Debug_Null_Pointer(x);

		X.push_back(x->X());
	}
	return std::move(X);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::HydStatic_CmptLib::RetrieveAreas
(
	const HydStatic_Bonjean & theBonjean,
	const Standard_Real theTa, 
	const Standard_Real xTa, 
	const Standard_Real theTf, 
	const Standard_Real xTf
)
{
	if (NOT theBonjean.IsDone())
	{
		FatalErrorIn("std::vector<marineLib::xSectionParam> RetrieveAreas(Args...)")
			<< "the Bonjean curves is not performed!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(theBonjean.Body());
	const auto& body = *theBonjean.Body();

	const auto bnjCurves = HydStatic_CmptLib::RetrieveBnjCurves(theBonjean);

	const auto Ts = HydStatic_CmptLib::RetrieveDrafts(body, theTa, xTa, theTf, xTf);
	auto As = HydStatic_CmptLib::RetrieveAreas(bnjCurves, Ts);

	return std::move(As);
}

std::vector<tnbLib::HydStatic_GzQ> 
tnbLib::HydStatic_CmptLib::LeverArms
(
	const std::vector<std::shared_ptr<HydStatic_CrossCurves_Entity>>& theCurves,
	const Standard_Real theVol
)
{
	std::vector<HydStatic_GzQ> pairs;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(x->Curve);
		const auto& curve = *x->Curve;

		if (NOT curve.IsIntersect(theVol))
		{
			continue;
		}

		auto value = curve.Value(theVol);

		HydStatic_GzQ p(x->Heel, value);
		pairs.push_back(std::move(p));
	}
	return std::move(pairs);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::HydStatic_CmptLib::GZ
(
	const std::vector<HydStatic_GzQ>& thePairs,
	const Standard_Real theKG
)
{
	std::vector<marineLib::xSectionParam> gzs;
	gzs.reserve(thePairs.size());

	for (const auto& x : thePairs)
	{
		auto heel = x.Heel();
		auto lk = x.LeverArm();

		auto gz = lk - theKG * sin(heel);

		marineLib::xSectionParam p;
		p.x = heel;
		p.value = gz;

		gzs.push_back(std::move(p));
	}
	return std::move(gzs);
}

tnbLib::HydStatic_GzQP
tnbLib::HydStatic_CmptLib::CalcMaxRightingArm
(
	const HydStatic_ArmCurve & theCurve
)
{
	const auto& geom = theCurve.Geometry();
	const Entity2d_Box b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(geom));

	const auto[dx, dy] = b.Length();
	const auto ymax = b.P1().Y() + 0.001*dy;

	const auto p0 = gp_Pnt2d(b.P0().X(), ymax);
	const auto p1 = gp_Pnt2d(b.P1().X(), ymax);

	GCE2d_MakeSegment maker(p0, p1);
	const auto& line = maker.Value();

	Geom2dAPI_ExtremaCurveCurve 
		extrm
		(
			geom, line, 
			geom->FirstParameter(), geom->LastParameter(),
			line->FirstParameter(), line->LastParameter()
		);

	gp_Pnt2d q0, q1;
	extrm.NearestPoints(q0, q1);

	Standard_Real u0, u1;
	extrm.LowerDistanceParameters(u0, u1);

	const auto gzq = HydStatic_GzQP(q0.X(), q0.Y(), u0);
	return std::move(gzq);
}

tnbLib::HydStatic_GzQP
tnbLib::HydStatic_CmptLib::CalcMaxRightingArmPort
(
	const HydStatic_ArmCurve & theCurve
)
{
	const auto& geom = theCurve.Geometry();
	const Entity2d_Box b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(geom));

	const auto[dx, dy] = b.Length();
	const auto ymin = b.P0().Y() - 0.001*dy;

	const auto p0 = gp_Pnt2d(b.P0().X(), ymin);
	const auto p1 = gp_Pnt2d(b.P1().X(), ymin);

	GCE2d_MakeSegment maker(p0, p1);
	const auto& line = maker.Value();

	Geom2dAPI_ExtremaCurveCurve
		extrm
		(
			geom, line,
			geom->FirstParameter(), geom->LastParameter(),
			line->FirstParameter(), line->LastParameter()
		);

	gp_Pnt2d q0, q1;
	extrm.NearestPoints(q0, q1);

	Standard_Real u0, u1;
	extrm.LowerDistanceParameters(u0, u1);

	const auto gzq = HydStatic_GzQP(q0.X(), q0.Y(), u0);
	return std::move(gzq);
}

std::vector<tnbLib::HydStatic_GzQP> 
tnbLib::HydStatic_CmptLib::CalcStaticalStabilityPoints
(
	const HydStatic_rArmCurve & theCurve,
	const Standard_Real theMoment
)
{
	const auto& geom = theCurve.Geometry();
	const Entity2d_Box b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(geom));

	std::vector<tnbLib::HydStatic_GzQP> Qs;
	if (NOT INSIDE(theMoment, b.P0().Y(), b.P1().Y()))
	{
		return std::move(Qs);
	}

	Handle(Geom2d_Line) line = new Geom2d_Line(gp_Pnt2d(0, theMoment), gp_Vec2d(1, 0));
	Geom2dAPI_InterCurveCurve inter(geom, line);
	
	auto& intersector = inter.Intersector();
	for (auto i = 1; i <= intersector.NbPoints(); i++)
	{
		const auto& q = intersector.Point(i);
		const auto& pt = q.Value();

		HydStatic_GzQP gzp(pt.X(), pt.Y(), q.ParamOnFirst());
		Qs.push_back(std::move(gzp));
	}

	for (auto i = 1; i <= intersector.NbSegments(); i++)
	{
		Handle(Geom2d_Curve) c1;
		Handle(Geom2d_Curve) c2;
	
		inter.Segment(i, c1, c2);

		const auto p0 = c1->FirstParameter();
		const auto p1 = c1->LastParameter();

		const auto pm = MEAN(p0, p1);
		const auto pt = c1->Value(pm);

		HydStatic_GzQP q(pt.X(), pt.Y(), pm);
		Qs.push_back(std::move(q));
	}

	if (Qs.size() > 1)
	{
		std::sort(Qs.begin(), Qs.end(), &HydStatic_GzQ::IsLess);
	}

	Standard_Integer k = 0;
	for (auto& x : Qs)
	{
		x.Index() = ++k;
	}
	return std::move(Qs);
}

std::vector<tnbLib::HydStatic_GzQP2> 
tnbLib::HydStatic_CmptLib::CalcStaticalStabilityPoints
(
	const HydStatic_rArmCurve & theCurve,
	const HydStatic_hArmCurve & theMoment
)
{
	const auto& geom = theCurve.Geometry();

	std::vector<tnbLib::HydStatic_GzQP2> Qs;

	Geom2dAPI_InterCurveCurve inter(geom, theMoment.Geometry());
	auto& intersector = inter.Intersector();

	for (auto i = 1; i <= intersector.NbPoints(); i++)
	{
		const auto& q = intersector.Point(i);
		const auto& pt = q.Value();

		HydStatic_GzQP2 gzp(pt.X(), pt.Y(), q.ParamOnFirst(), q.ParamOnSecond());
		Qs.push_back(std::move(gzp));
	}

	for (auto i = 1; i <= intersector.NbSegments(); i++)
	{
		Handle(Geom2d_Curve) c1;
		Handle(Geom2d_Curve) c2;

		inter.Segment(i, c1, c2);

		const auto p01 = c1->FirstParameter();
		const auto p11 = c1->LastParameter();

		const auto p02 = c2->FirstParameter();
		const auto p12 = c2->LastParameter();

		const auto pm1 = MEAN(p01, p11);
		const auto pm2 = MEAN(p02, p12);

		const auto pt1 = c1->Value(pm1);

		HydStatic_GzQP2 q(pt1.X(), pt1.Y(), pm1, pm2);
		Qs.push_back(std::move(q));
	}

	if (Qs.size() > 1)
	{
		std::sort(Qs.begin(), Qs.end(), &HydStatic_GzQ::IsLess);
	}

	Standard_Integer k = 0;
	for (auto& x : Qs)
	{
		x.Index() = ++k;
	}
	return std::move(Qs);
}

std::tuple<tnbLib::HydStatic_EqQ, tnbLib::HydStatic_EqQ> 
tnbLib::HydStatic_CmptLib::CalcStaticalStabilityPoints_Starboard
(
	const std::shared_ptr<HydStatic_rArmCurve> & theCurve,
	const std::shared_ptr<HydStatic_hArmCurve> & theHeeling
)
{
	const auto heel0 = std::max((Standard_Real)0., theCurve->MinHeel());
	const auto clipped =
		std::dynamic_pointer_cast<HydStatic_rArmCurve>
		(HydStatic_rArmCurve::Clip
		(
			theCurve, heel0,
			theCurve->MaxHeel()
		));
	Debug_Null_Pointer(clipped);

	const auto pts = CalcStaticalStabilityPoints(*clipped, *theHeeling);
	if (pts.size() IS_EQUAL 2)
	{
		const auto& p0 = pts[0];
		const auto stQ = HydStatic_StEqQ(p0.Heel(), p0.LeverArm(), p0.Parameter0(), p0.Parameter1());

		const auto& p1 = pts[1];
		const auto unQ = HydStatic_UnEqQ(p1.Heel(), p1.LeverArm(), p1.Parameter0(), p1.Parameter1());

		auto t = std::make_tuple(std::move(stQ), std::move(unQ));
		return std::move(t);
	}

	if (pts.size() IS_EQUAL 1)
	{
		const auto& q = pts[0];

		const auto p0 = q.Parameter0();
		const auto p1 = q.Parameter1();

		Debug_Null_Pointer(theCurve->Geometry());
		Debug_Null_Pointer(theHeeling->Geometry());

		const auto& geom0 = *theCurve->Geometry();
		const auto& geom1 = *theHeeling->Geometry();

		gp_Pnt2d pt0, pt1;
		gp_Vec2d u0, u1;

		geom0.D1(p0, pt0, u0);
		geom1.D1(p1, pt1, u1);

		u0.Normalize();
		u1.Normalize();

		if (u0.Crossed(u1) >= 0)
		{
			const auto unQ = HydStatic_UnEqQ(q.Heel(), q.LeverArm(), q.Parameter0(), q.Parameter1());
			auto t = std::make_tuple(std::move(unQ), HydStatic_EqQ::null);
			return std::move(t);
		}
		else
		{
			const auto StQ = HydStatic_StEqQ(q.Heel(), q.LeverArm(), q.Parameter0(), q.Parameter1());
			auto t = std::make_tuple(std::move(StQ), HydStatic_EqQ::null);
			return std::move(t);
		}
	}

	/*FatalErrorIn("std::tuple<HydStatic_EqQ, HydStatic_EqQ> CalcStaticalStabilityPoints_Starboard(Args...)")
		<< "invalid data" << endl
		<< abort(FatalError);*/

	auto t = std::make_tuple(HydStatic_EqQ::null, HydStatic_EqQ::null);
	return std::move(t);
}

const tnbLib::HydStatic_EqQ&
tnbLib::HydStatic_CmptLib::GetStable
(
	const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
)
{
	const auto&[eq0, eq1] = t;
	
	if (HydStatic_EqQ::IsNull(eq1))
	{
		if (HydStatic_EqQ::IsNull(eq0))
		{
			FatalErrorIn("std::tuple<HydStatic_EqQ, Standard_Boolean> GetStable(Args...)")
				<< "both the eq. points are null!" << endl
				<< abort(FatalError);
		}

		if (eq0.IsStable())
		{
			return eq0;
		}
		else return HydStatic_EqQ::null;
	}
	else
	{
		if (eq0.IsUnStable())
		{
			FatalErrorIn("std::tuple<HydStatic_EqQ, Standard_Boolean> GetStable(Args...)")
				<< "contradictory data: the first stb. point must be the stable one!" << endl
				<< abort(FatalError);
		}
		return eq0;
	}
}

const tnbLib::HydStatic_EqQ&
tnbLib::HydStatic_CmptLib::GetUnStable
(
	const std::tuple<HydStatic_EqQ, HydStatic_EqQ>& t
)
{
	const auto&[eq0, eq1] = t;

	if (HydStatic_EqQ::IsNull(eq1))
	{
		if (HydStatic_EqQ::IsNull(eq0))
		{
			FatalErrorIn("std::tuple<HydStatic_EqQ, Standard_Boolean> GetUnStable(Args...)")
				<< "both the eq. points are null!" << endl
				<< abort(FatalError);
		}

		if (eq0.IsUnStable())
		{
			return eq0;
		}
		else return HydStatic_EqQ::null;
	}
	else
	{
		if (eq1.IsStable())
		{
			FatalErrorIn("std::tuple<HydStatic_EqQ, Standard_Boolean> GetUnStable(Args...)")
				<< "contradictory data: the second stb. point must be the unstable one!" << endl
				<< abort(FatalError);
		}
		return eq1;
	}
}