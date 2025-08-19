#include <HydStatic_DisContinuBonjean.hxx>

#include <HydStatic_BnjCurve.hxx>
#include <HydStatic_BonjeanGraph.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_LocalInterpl.hxx>
#include <Cad2d_InterpUbarMap_Centripetal.hxx>
#include <Cad2d_InterpUbarMap_ChordLen.hxx>
#include <Cad2d_InterpUbarMap_Uniform.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

tnbLib::HydStatic_DisContinuBonjean::Clip::Clip
(
	span && theSpan,
	std::shared_ptr<HydStatic_BnjCurve> && theCurve
)
	: theSpan_(std::move(theSpan))
	, theCurve_(std::move(theCurve))
{
	// empty body [5/31/2021 Amir]
}

tnbLib::Pnt2d 
tnbLib::HydStatic_DisContinuBonjean::Clip::FirstValue() const
{
	auto pt = Curve()->FirstCoord();
	return std::move(pt);
}

tnbLib::Pnt2d 
tnbLib::HydStatic_DisContinuBonjean::Clip::LastValue() const
{
	auto pt = Curve()->LastCoord();
	return std::move(pt);
}

std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::Clip>
tnbLib::HydStatic_DisContinuBonjean::Clip::Copy() const
{
	auto geom = Handle(Geom2d_Curve)::DownCast(Curve()->Geometry()->Copy());
	auto clip = std::make_shared<Clip>();
	Debug_Null_Pointer(clip);

	auto bonj = std::make_shared<HydStatic_BnjCurve>(std::move(geom));
	clip->SetCurve(std::move(bonj));
	clip->SetSpan(Span());

	return std::move(clip);
}

namespace tnbLib
{
	auto MakeInfo
	(
		const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo,
		const Standard_Real d
	)
	{
		auto info = std::make_shared<Geo_ApprxCurve_Info>();
		info->SetMinSize(theInfo->MinSize()*d);
		info->SetApprox(theInfo->Approx()*d);
		info->SetAngle(theInfo->Angle());
		info->SetNbSamples(theInfo->NbSamples());
		info->SetInitNbSubdivision(theInfo->InitNbSubdivision());
		info->SetMaxNbSubdivision(theInfo->MaxNbSubdivision());

		return std::move(info);
	}

	auto Approx
	(
		const Handle(Geom2d_Curve)& c,
		const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
	)
	{
		auto b = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(c));
		auto d = b.Diameter();

		auto info = MakeInfo(theInfo, d);
		auto alg = std::make_shared<Geo2d_ApprxCurve>(c, c->FirstParameter(), c->LastParameter(), info);
		alg->Perform();
		return alg->Chain();
	}
}

void tnbLib::HydStatic_DisContinuBonjean::Clip::Scale
(
	const Standard_Real coeff
)
{
	const auto c = 1.0 / coeff;
	auto poly = Approx(Curve()->Geometry(), curveApproxInfo);
	for (auto& x : poly->Points())
	{
		x.X() *= c;
	}

	auto curve = Pln_CurveTools::Interpolation(poly->Points());

	auto bonj = std::make_shared<HydStatic_BnjCurve>(std::move(curve));
	theCurve_ = std::move(bonj);
}

tnbLib::HydStatic_DisContinuBonjean::SectionClips::SectionClips
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	const std::vector<std::shared_ptr<Clip>>& theClips
)
	: theSection_(theSection)
	, theClips_(theClips)
{
	// empty body [5/31/2021 Amir]
}

std::vector<std::shared_ptr<tnbLib::HydStatic_BnjCurve>> 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::RetrieveBonjeanCurves() const
{
	std::vector<std::shared_ptr<HydStatic_BnjCurve>> curves;
	curves.reserve(NbClips());
	for (const auto& x : Clips())
	{
		Debug_Null_Pointer(x);
		curves.push_back(x->Curve());
	}
	return std::move(curves);
}

void tnbLib::HydStatic_DisContinuBonjean::SectionClips::SetSection
(
	const std::shared_ptr<Marine_CmpSection>& theSection
)
{
	theSection_ = theSection;
}

void tnbLib::HydStatic_DisContinuBonjean::SectionClips::SetClips
(
	std::vector<std::shared_ptr<Clip>>&& theClips
)
{
	theClips_ = std::move(theClips);
}

namespace tnbLib
{
	std::shared_ptr<Geo_ApprxCurve_Info> HydStatic_DisContinuBonjean::curveApproxInfo = 
		std::make_shared<Geo_ApprxCurve_Info>();

	class ApproxCurveInfoRunTime
	{
		/*Private Data*/

	public:

		ApproxCurveInfoRunTime()
		{
			Config();
		}

		static void Config();
	};
}

void tnbLib::ApproxCurveInfoRunTime::Config()
{
	const auto& info = HydStatic_DisContinuBonjean::curveApproxInfo;
	info->SetAngle(Geo_Tools::DegToRadian(5.0));
	info->SetApprox(1.0E-3);
	info->SetInitNbSubdivision(3);
	info->SetMaxNbSubdivision(7);
	info->SetMinSize(1.0E-4);
	info->SetNbSamples(5);
}

static tnbLib::ApproxCurveInfoRunTime myRunTimeConfigObject;

namespace tnbLib
{
	Standard_Boolean
		hasIntersection
		(
			const HydStatic_DisContinuBonjean::span & s0, 
			const HydStatic_DisContinuBonjean::span & s1
		)
	{
		return s0.IsIntersect(s1);
	}

	Standard_Real
		X
		(
			const Handle(Geom2d_Curve)& curve,
			const Standard_Real y
		)
	{
		Handle(Geom2d_Line) l =
			new Geom2d_Line(gp_Pnt2d(0, y), gp_Dir2d(1, 0));
		Debug_Null_Pointer(l);

		Geom2dAPI_InterCurveCurve Int(l, curve);
		if (Int.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid data" << endl
				<< abort(FatalError);
		}
		auto value = Int.Point(1);
		return value.X();
	}

	Standard_Real
		Y0(const Handle(Geom2d_Curve)& curve)
	{
		if (NOT Pln_Tools::IsBounded(curve))
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not bounded!" << endl
				<< abort(FatalError);
		}
		auto pt = curve->Value(curve->FirstParameter());
		return pt.Y();
	}

	Standard_Real
		Y1(const Handle(Geom2d_Curve)& curve)
	{
		if (NOT Pln_Tools::IsBounded(curve))
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not bounded!" << endl
				<< abort(FatalError);
		}
		auto pt = curve->Value(curve->LastParameter());
		return pt.Y();
	}

	Standard_Real
		X0(const Handle(Geom2d_Curve)& curve)
	{
		if (NOT Pln_Tools::IsBounded(curve))
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not bounded!" << endl
				<< abort(FatalError);
		}
		auto pt = curve->Value(curve->FirstParameter());
		return pt.X();
	}

	Standard_Real
		X1(const Handle(Geom2d_Curve)& curve)
	{
		if (NOT Pln_Tools::IsBounded(curve))
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not bounded!" << endl
				<< abort(FatalError);
		}
		auto pt = curve->Value(curve->LastParameter());
		return pt.X();
	}

	typename HydStatic_DisContinuBonjean::span
		RetrieveSpan(const Handle(Geom2d_Curve)& curve)
	{
		HydStatic_DisContinuBonjean::span s{ Y0(curve), Y1(curve) };
		return std::move(s);
	}

	std::pair<Standard_Boolean, typename HydStatic_DisContinuBonjean::span>
		Intersect
		(
			const HydStatic_DisContinuBonjean::span & s0,
			const HydStatic_DisContinuBonjean::span & s1
		)
	{
		if (NOT hasIntersection(s0, s1))
		{
			HydStatic_DisContinuBonjean::span s{ 0,0 };
			auto t = std::make_pair(Standard_False, std::move(s));
			return std::move(t);
		}
		else
		{
			auto s = s0.Intersection(s1);
			auto t = std::make_pair(Standard_True, std::move(s));
			return std::move(t);
		}
	}

	std::pair<Standard_Boolean, typename HydStatic_DisContinuBonjean::span>
		Intersect
		(
			const Handle(Geom2d_Curve)& theC0,
			const Handle(Geom2d_Curve)& theC1
		)
	{
		const auto span0 = RetrieveSpan(theC0);
		const auto span1 = RetrieveSpan(theC1);

		auto s = Intersect(span0, span1);
		return std::move(s);
	}
}

namespace tnbLib
{

	auto Sum
	(
		const Handle(Geom2d_Curve)& c,
		const std::shared_ptr<Entity2d_Polygon>& poly
	)
	{
		const auto y0 = Y0(c);
		const auto y1 = Y1(c);

		std::vector<Pnt2d> pts;
		pts.reserve(poly->Points().size());
		for (const auto& x : poly->Points())
		{
			auto y = x.Y();
			auto x0 = X(c, y);
			auto xs = x.X() + x0;

			auto pt = Pnt2d(xs, y);
			pts.push_back(std::move(pt));
		}

		auto curve = Pln_CurveTools::Interpolation(pts);
		return std::move(curve);
	}

	auto Subtract
	(
		const HydStatic_DisContinuBonjean::span & theS0,
		const HydStatic_DisContinuBonjean::span & theIntersect
	)
	{
		HydStatic_DisContinuBonjean::span s0{ theS0.X0(),theIntersect.X0() };
		HydStatic_DisContinuBonjean::span s1{ theIntersect.X1(),theS0.X1() };

		if (NOT s0.IsNull())
		{
			if (NOT s1.IsNull())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid operation has been detected!" << endl
					<< abort(FatalError);
			}
			return std::move(s0);
		}
		else
		{
			if (NOT s0.IsNull())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid operation has been detected!" << endl
					<< abort(FatalError);
			}
			return std::move(s1);
		}
	}

	auto Sum
	(
		const HydStatic_DisContinuBonjean::span & theS0,
		const HydStatic_DisContinuBonjean::span & theS1
	)
	{
		auto[intersect, s] = Intersect(theS0, theS1);

		std::vector<HydStatic_DisContinuBonjean::span> spans;
		if (intersect)
		{
			auto s0 = Subtract(theS0, s);
			auto s1 = Subtract(theS1, s);

			spans.push_back(std::move(s0));
			spans.push_back(std::move(s));
			spans.push_back(std::move(s1));
			return std::move(spans);
		}
		else
		{
			spans.push_back(theS0);
			spans.push_back(theS1);
			return std::move(spans);
		}
	}
}

Handle(Geom2d_Curve)
tnbLib::HydStatic_DisContinuBonjean::MakeSegment(const span & s, const Standard_Real x)
{
	Pnt2d p0(x, s.X0());
	Pnt2d p1(x, s.X1());

	auto curve = Pln_CurveTools::MakeSegment(p0, p1);
	return std::move(curve);
}

Handle(Geom2d_Curve) 
tnbLib::HydStatic_DisContinuBonjean::MakeClip
(
	const Handle(Geom2d_Curve)& c,
	const span & s
)
{
	auto curve = Pln_CurveTools::Trim(c, s.X0(), s.X1());
	return std::move(curve);
}

Handle(Geom2d_Curve) 
tnbLib::HydStatic_DisContinuBonjean::Sum
(
	const Handle(Geom2d_Curve)& theC0, 
	const Handle(Geom2d_Curve)& theC1
)
{
	auto [intersect, s] = ::tnbLib::Intersect(theC0, theC1);
	if (intersect)
	{
		auto c0 = MakeClip(theC0, s);
		auto c1 = MakeClip(theC1, s);

		auto poly0 = Approx(c0, curveApproxInfo);
		auto poly1 = Approx(c1, curveApproxInfo);

		if (poly0->NbPoints() > poly1->NbPoints())
		{
			auto s = ::tnbLib::Sum(c1, poly0);
			return std::move(s);
		}
		else
		{
			auto s = ::tnbLib::Sum(c0, poly1);
			return std::move(s);
		}
	}
	return nullptr;
}

Handle(Geom2d_Curve)
tnbLib::HydStatic_DisContinuBonjean::Sum
(
	const Handle(Geom2d_Curve)& c,
	const Standard_Real x
)
{
	auto curve = Handle(Geom2d_Curve)::DownCast(c->Copy());
	Debug_Null_Pointer(curve);

	gp_Trsf2d t;
	t.SetTranslationPart(gp_Vec2d(x, 0));

	curve->Transform(t);
	return std::move(curve);
}

void tnbLib::HydStatic_DisContinuBonjean::SectionClips::Add(const std::shared_ptr<Clip>& theClip)
{
	if (theClips_.empty())
	{
		theClips_.push_back(theClip);
		return;
	}

	const auto& clip0 = theClips_[theClips_.size() - 1];

	const auto& span0 = clip0->Span();
	const auto& curve0 = clip0->Curve();

	const auto& span1 = theClip->Span();
	const auto& curve1 = theClip->Curve();

	auto sum = HydStatic_DisContinuBonjean::Sum(clip0, theClip);
	if (sum.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data has been detected!" << endl
			<< abort(FatalError);
	}

	theClips_[theClips_.size() - 1] = sum[0];
	if (sum.size() > 1)
	{
		for (size_t i = 1; i < sum.size() - 1; i++)
		{
			theClips_.push_back(sum[i]);
		}
	}
}

std::vector<std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::Clip>>
tnbLib::HydStatic_DisContinuBonjean::Sum
(
	const std::shared_ptr<Clip>& theClip0,
	const std::shared_ptr<Clip>& theClip1
)
{
	const auto& span0 = theClip0->Span();
	const auto& curve0 = theClip0->Curve();

	const auto& span1 = theClip1->Span();
	const auto& curve1 = theClip1->Curve();

	std::vector<Handle(Geom2d_Curve)> curves;
	if (hasIntersection(span0, span1))
	{
		auto spans = ::tnbLib::Sum(span0, span1);

		const auto& s0 = spans[0];
		const auto& s1 = spans[1];
		const auto& s2 = spans[2];

		if (NOT s0.IsNull())
		{
			auto c0 = MakeClip(curve0->Geometry(), s0);
			curves.push_back(std::move(c0));
		}

		if (NOT s1.IsNull())
		{
			if (auto curve = Sum(curve0->Geometry(), curve1->Geometry()))
			{
				curves.push_back(std::move(curve));
			}
		}

		if (NOT s2.IsNull())
		{
			auto c2 = MakeClip(curve1->Geometry(), s2);
			if (curves.size())
			{
				const auto& p = curves[curves.size() - 1];
				auto c2m = Sum(c2, X1(p));
				curves.push_back(std::move(c2m));
			}
			else
			{
				curves.push_back(std::move(c2));
			}
		}
	}
	else
	{
		curves.push_back(curve0->Geometry());

		auto c3m = Sum(curve1->Geometry(), X1(curve0->Geometry()));

		const auto p0 = curve0->Geometry()->Value(curve0->Geometry()->LastParameter());
		const auto p1 = c3m->Value(c3m->FirstParameter());

		auto c2 = Pln_CurveTools::MakeSegment(p0, p1);
	
		curves.push_back(std::move(c2));
		curves.push_back(std::move(c3m));
	}

	std::vector<std::shared_ptr<Clip>> clips;
	clips.reserve(curves.size());
	for (auto& x : curves)
	{
		Debug_Null_Pointer(x);
		auto s = RetrieveSpan(x);
		auto bonj = std::make_shared<HydStatic_BnjCurve>(std::move(x));
		auto clip = std::make_shared<Clip>(std::move(s), std::move(bonj));
		Debug_Null_Pointer(clip);

		clips.push_back(std::move(clip));
	}
	return std::move(clips);
}

#include <Geo_CosineDistb.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_Sections.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Body.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_WaterTools.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BooleanOps.hxx>
#include <Marine_System.hxx>

#include <StdFail_NotDone.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <Geom2d_BSplineCurve.hxx>

namespace tnbLib
{
	unsigned short HydStatic_DisContinuBonjean::verbose(0);
	const unsigned int HydStatic_DisContinuBonjean::MIN_NB_OF_POINTS(5);
}

tnbLib::HydStatic_DisContinuBonjean::HydStatic_DisContinuBonjean
()
	: theNbLevels_(0)
{}

tnbLib::HydStatic_DisContinuBonjean::HydStatic_DisContinuBonjean
(
	const std::shared_ptr<Marine_Domain>& theDomain, 
	const std::shared_ptr<Marine_Body>& theBody,
	const Standard_Integer nbLevs
)
	: theDomain_(theDomain)
	, theBody_(theBody)
	, theNbLevels_(nbLevs)
{
	// empty body [6/3/2021 Amir]
}

namespace tnbLib
{

	auto WaterSection
	(
		const std::shared_ptr<Marine_Domain>& d,
		const std::shared_ptr<Marine_CmpSection>& cmpSect,
		const Standard_Real z
	)
	{
		const auto& domain = d->Dim();
		Debug_Null_Pointer(domain);

		const auto y0 = domain->P0().Z();
		const auto y1 = z;

		const auto x0 = domain->P0().Y();
		const auto x1 = domain->P1().Y();

		auto wa = Marine_WaterTools::WaterSection(Pnt2d(x0, y0), Pnt2d(x1, y1));
		auto section = Marine_SectTools::SectionCreator
		(
			wa, cmpSect->CoordinateSystem(),
			Marine_SectionType::water
		);
		return std::move(section);
	}

	auto RetrieveZ0Z1(const std::shared_ptr<Marine_Section>& sec)
	{
		auto b = sec->BoundingBox();
		auto z0 = b.P0().Y();
		auto z1 = b.P1().Y();
		auto t = std::make_pair(z0, z1);
		return std::move(t);
	}

	auto CalcSectionArea
	(
		const Entity3d_Box& domain,
		const std::shared_ptr<marineLib::Section_Displacer>& sect, 
		const Standard_Integer nbLevels
	)
	{
		auto[z0, z1] = RetrieveZ0Z1(sect);
		auto dz = z1 - z0;
		Debug_If_Condition(dz < 0);

		auto dist = std::make_shared<Geo_CosineDistb>(nbLevels);
		Debug_Null_Pointer(dist);

		dist->SetLower(z0);
		dist->SetUpper(z1);
		dist->Perform();

		Debug_If_Condition_Message(NOT dist->IsDone(), "the algorithm is not performed");

		const auto y0 = domain.P0().Z();

		const auto x0 = domain.P0().Y();
		const auto x1 = domain.P1().Y();

		std::vector<std::pair<Standard_Real, Standard_Real>> As;
		As.reserve(nbLevels);
		for (auto z : dist->Values())
		{

			if (std::abs(z - z0) <= gp::Resolution())
			{
				auto t = std::make_pair(z0, 0.0);
				As.push_back(std::move(t));
				continue;
			}
			auto y1 = z;

			auto wa = Marine_WaterTools::WaterSection(Pnt2d(x0, y0), Pnt2d(x1, y1));
			Debug_Null_Pointer(wa);

			auto water =
				Marine_SectTools::SectionCreator
				(
					wa,
					Marine_SectionType::water
				);
			Debug_Null_Pointer(water);

			auto wettedSections = Marine_BooleanOps::WettedSection(sect, water);

			Standard_Real sumArea = 0;
			for (const auto& x : wettedSections)
			{
				Debug_Null_Pointer(x);

				auto area = MarineBase_Tools::CalcArea(x, sysLib::gl_marine_integration_info);

				Debug_If_Condition(area < 0);
				sumArea += area;
			}
			auto t = std::make_pair(z, sumArea);
			As.push_back(std::move(t));
		}
		return std::move(As);
	}

	auto MakeCurveGlobal(const std::vector<std::pair<Standard_Real, Standard_Real>>& Qs)
	{
		Handle(TColgp_HArray1OfPnt2d) offsets = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)Qs.size());
		auto& offsetsRef = *offsets;

		Standard_Integer k = 0;
		for (const auto& x : Qs)
		{
			offsetsRef.SetValue(++k, gp_Pnt2d(x.second, x.first));
		}

		try
		{
			Geom2dAPI_Interpolate Interpolation(offsets, Standard_False, 1.0e-6);
			Interpolation.Perform();

			if (!Interpolation.IsDone())
			{
				FatalErrorIn
				(
					FunctionSIG
				)
					<< "Failed to interpolation!"
					<< abort(FatalError);
			}

			return Interpolation.Curve();
		}
		catch (StdFail_NotDone&)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to interpolate the offset points!" << endl
				<< abort(FatalError);
		}
		Handle(Geom2d_BSplineCurve) curve;
		return curve;
	}

	auto MakeCurveLocal
	(
		const std::vector<std::pair<Standard_Real, Standard_Real>>& Qs,
		const HydStatic_DisContinuBonjean::localInfo& theInfo
	)
	{
		std::vector<Pnt2d> pts;
		pts.reserve(Qs.size());

		for (const auto& x : Qs)
		{
			auto pt = Pnt2d(x.first, x.second);
			pts.push_back(std::move(pt));
		}

		std::shared_ptr<Cad2d_InterpUbarMap> ubarMap;
		switch (theInfo.KnotsType)
		{
		case HydStatic_DisContinuBonjean::localInfo::knotsType::uniform:
		{
			ubarMap = std::make_shared<Cad2d_InterpUbarMap_Uniform>();
			break;
		}
		case HydStatic_DisContinuBonjean::localInfo::knotsType::chordLen:
		{
			ubarMap = std::make_shared<Cad2d_InterpUbarMap_ChordLen>();
			break;
		}
		case HydStatic_DisContinuBonjean::localInfo::knotsType::centripetal:
		{
			ubarMap = std::make_shared<Cad2d_InterpUbarMap_Centripetal>();
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of knots vector calculator has been detected!" << endl
				<< abort(FatalError);
			break;
		}

		Cad2d_LocalInterpl interpolation(pts);
		
		switch (theInfo.NeighborType)
		{
		case HydStatic_DisContinuBonjean::localInfo::neighborType::threePoint:
		{
			interpolation.SetType(Cad2d_LocalInterpl::neighborType::threePoint);
			break;
		}
		case HydStatic_DisContinuBonjean::localInfo::neighborType::fivePoint:
		{
			interpolation.SetType(Cad2d_LocalInterpl::neighborType::fivePoint);
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of neighbor has been detected!" << endl
				<< abort(FatalError);
			break;
		}

		switch (theInfo.ContinuityType)
		{
		case HydStatic_DisContinuBonjean::localInfo::continuityType::C1:
		{
			interpolation.SetContinuity(Cad2d_LocalInterpl::continuity::C1);
			break;
		}
		case HydStatic_DisContinuBonjean::localInfo::continuityType::G1:
		{
			interpolation.SetContinuity(Cad2d_LocalInterpl::continuity::G1);
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of continuity has been detected!" << endl
				<< abort(FatalError);
			break;
		}

		interpolation.SetTolerance(theInfo.Tolerance);

		interpolation.Perform();
		auto curve = interpolation.Curve();
		return std::move(curve);
	}
}

void tnbLib::HydStatic_DisContinuBonjean::Perform()
{
	if (verbose)
	{
		Info << endl;
		Info << "******* Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Body())
	{
		FatalErrorIn(FunctionSIG)
			<< " no body has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NbLevels() < MIN_NB_OF_POINTS)
	{
		FatalErrorIn(FunctionSIG)
			<< "nb. of levels is insufficient" << endl
			<< "- the acceptable nb of levels is " << MIN_NB_OF_POINTS << " or more." << endl
			<< "- current nb of levels:" << NbLevels() << endl
			<< abort(FatalError);
	}

	const auto& body = Body();
	if (verbose)
	{
		Info << " Body's name: " << body->Name() << endl;
		Info << " nb. of sections: " << body->NbSections() << endl;
	}

	const auto& sections = body->Sections();
	if (sections.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been found in the body!" << endl
			<< abort(FatalError);
	}

	const auto& domain = Domain();

	std::vector<std::shared_ptr<SectionClips>> sectionClips;
	sectionClips.reserve(body->NbSections());

	for (const auto& sect : body->Sections())
	{
		Debug_Null_Pointer(sect);

		auto clips = std::make_shared<SectionClips>();
		Debug_Null_Pointer(clips);

		clips->SetSection(sect);

		if (verbose)
		{
			Info << " - section nb. " << sect->Index() << endl;
		}
		for (const auto& x : sect->Sections())
		{
			auto displacer = Marine_SectTools::DisplacerSection(x);
			Debug_Null_Pointer(displacer);

			auto Qs = CalcSectionArea(*domain->Dim(), displacer, NbLevels());

			Handle(Geom2d_Curve) geom;
			switch (theInterplScheme_)
			{
			case tnbLib::HydStatic_DisContinuBonjean::interplScheme::Global:
				geom = (Handle(Geom2d_Curve))MakeCurveGlobal(Qs);
				break;
			case tnbLib::HydStatic_DisContinuBonjean::interplScheme::Local:
				geom = MakeCurveLocal(Qs, LocalInterplInfo());
				break;
			default:
				FatalErrorIn(FunctionSIG)
					<< "unspecified type of interpolation has been detected!" << endl
					<< abort(FatalError);
				break;
			}
			auto bonj = std::make_shared<HydStatic_BnjCurve>(std::move(geom));

			auto s = RetrieveSpan(bonj->Geometry());
			auto clip = std::make_shared<Clip>(std::move(s), std::move(bonj));
			Debug_Null_Pointer(clip);

			clips->Add(clip);
		}

		sectionClips.push_back(std::move(clips));
	}
	
	auto gragh = std::make_shared<HydStatic_BonjeanGraph>();
	theSections_ = std::move(sectionClips);

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		Info << endl;
		Info << "******* End of the Calculating Bonjean Curves ********" << endl;
		Info << endl;
	}
}

std::shared_ptr<tnbLib::HydStatic_BonjeanGraph> 
tnbLib::HydStatic_DisContinuBonjean::RetrieveGraph
(
	const std::vector<std::shared_ptr<SectionClips>>& theSections
)
{
	std::vector<std::shared_ptr<HydStatic_BonjeanGraph::GraphSect>> sections;
	sections.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		auto bonjs = x->RetrieveBonjeanCurves();

		auto graphSect = std::make_shared<HydStatic_BonjeanGraph::GraphSect>(x->Section(), std::move(bonjs));
		sections.push_back(std::move(graphSect));
	}
	auto graph = std::make_shared<HydStatic_BonjeanGraph>(std::move(sections));
	return std::move(graph);
}