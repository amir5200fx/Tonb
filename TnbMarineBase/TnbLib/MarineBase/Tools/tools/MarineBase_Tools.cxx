#include <MarineBase_Tools.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_CurveTools.hxx>

#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity2d_Triangle.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Geo_Interval.hxx>
#include <Geo_xDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CmptLib.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Cad2d_Plane.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <Marine_Section.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_xCmpSection.hxx>
#include <Marine_zCmpSection.hxx>
#include <Marine_WaterCurve.hxx>
#include <Marine_Sections.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_SectTools.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <UnitSystem.hxx>
#include <TecPlot.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif

#include <gp_Pln.hxx>
#include <gp_Trsf2d.hxx>
#include <gp_Ax22d.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>
#include <Bnd_Box2d.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <StdFail_NotDone.hxx>

#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

tnbLib::Pnt3d 
tnbLib::MarineBase_Tools::CalcOxyz
(
	const Entity3d_Box & theDomain
)
{
	const auto& p0 = theDomain.P0();
	const auto& p1 = theDomain.P1();

	const auto xo = p0.X();
	const auto yo = MEAN(p0.Y(), p1.Y());
	const auto zo = p0.Z();
	Pnt3d Oxyz(xo, yo, zo);
	return std::move(Oxyz);
}

tnbLib::marineLib::Pressure 
tnbLib::MarineBase_Tools::CalcWindPressure
(
	const marineLib::coeff::Cw & theAeroResisCoeff,
	const marineLib::Density & theRho, 
	const marineLib::Velocity & theVel
)
{
	marineLib::Pressure press(0.5*theAeroResisCoeff()*theRho()*theVel()*theVel());
	return std::move(press);
}

std::vector<Standard_Real> 
tnbLib::MarineBase_Tools::Tessellate
(
	const std::vector<Standard_Real>& x,
	const unsigned int theCriterion
)
{
	std::vector<Standard_Real> X;
	X.reserve(2 * x.size() - 1);
	X.push_back(x[0]);
	for (size_t i = 1; i < x.size(); i++)
	{
		auto xm = MEAN(x[i - 1], x[i]);
		X.push_back(xm);
		X.push_back(x[i]);
	}
	if (X.size() >= theCriterion)
	{
		return std::move(X);
	}
	else
	{
		auto xs = Tessellate(X, theCriterion);
		return std::move(xs);
	}
}

namespace tnbLib
{

	unsigned int MarineBase_Tools::MIN_NB_POINTS_INTERPOLATION = 25;

	/*std::vector<Standard_Real> TessellateX(const std::vector<Standard_Real>& x)
	{
		std::vector<Standard_Real> X;
		X.reserve(2 * x.size() - 1);
		X.push_back(x[0]);
		for (size_t i = 1; i < x.size(); i++)
		{
			auto xm = MEAN(x[i - 1], x[i]);
			X.push_back(xm);
			X.push_back(x[i]);
		}
		if (X.size() >= MIN_NB_POINTS_INTERPOLATION)
		{
			return std::move(X);
		}
		else
		{
			auto xs = TessellateX(X);
			return std::move(xs);
		}
	}*/

	std::vector<Standard_Real> TessellateX(const double* x, size_t n)
	{
		std::vector<Standard_Real> xt;
		xt.reserve(n);
		for (size_t i = 0; i < n; i++)
		{
			xt.push_back(x[i]);
		}
		auto xs = MarineBase_Tools::Tessellate(xt, MarineBase_Tools::MIN_NB_POINTS_INTERPOLATION);
		return std::move(xs);
	}
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::SteffenTessellation
(
	const std::vector<marineLib::xSectionParam>& theQ
)
{
	if (theQ.size() <= 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "no enough data points are provided!" << endl
			<< abort(FatalError);
	}

	if (theQ.size() < 5)
	{
		std::vector<Pnt2d> Qs;
		Qs.reserve(theQ.size() * 2 - 1);
		for (const auto& x : theQ)
		{
			auto pt = marineLib::point(x);
			Qs.push_back(std::move(pt));
		}

		const auto n = Qs.size();
		for (int i = n - 2; i >= 0; i--)
		{
			const auto& pt = Qs[i];
			auto ptp = pt.Mirrored(Qs[n - 1]);
			Qs.push_back(std::move(ptp));
		}

		auto x = new double[Qs.size()];
		auto y = new double[Qs.size()];
		for (size_t i = 0; i < Qs.size(); i++)
		{
			x[i] = Qs[i].X();
			y[i] = Qs[i].Y();
		}

		gsl_interp_accel *acc = gsl_interp_accel_alloc();
		gsl_spline *spline_steffen = gsl_spline_alloc(gsl_interp_steffen, Qs.size());
		gsl_spline_init(spline_steffen, x, y, Qs.size());

		auto xt = TessellateX(x, theQ.size());
		std::vector<marineLib::xSectionParam> Q;
		Q.reserve(xt.size());
		for (auto xi : xt)
		{
			double yi_steffen = gsl_spline_eval(spline_steffen, xi, acc);
			auto p = marineLib::xSectionParam{ xi,yi_steffen };
			Q.push_back(p);
		}
		return std::move(Q);
	}
	else
	{
		auto x = new double[theQ.size()];
		auto y = new double[theQ.size()];

		for (size_t i = 0; i < theQ.size(); i++)
		{
			x[i] = theQ[i].x;
			y[i] = theQ[i].value;
		}

		gsl_interp_accel *acc = gsl_interp_accel_alloc();
		gsl_spline *spline_steffen = gsl_spline_alloc(gsl_interp_steffen, theQ.size());
		gsl_spline_init(spline_steffen, x, y, theQ.size());

		auto xt = TessellateX(x, theQ.size());
		std::vector<marineLib::xSectionParam> Q;
		Q.reserve(xt.size());
		for (auto xi : xt)
		{
			double yi_steffen = gsl_spline_eval(spline_steffen, xi, acc);
			auto p = marineLib::xSectionParam{ xi,yi_steffen };
			Q.push_back(p);
		}
		return std::move(Q);
	}
}

tnbLib::Entity2d_Box
tnbLib::MarineBase_Tools::CalcBoundingBox2D
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
#ifdef _DEBUG
	Check_xCmptSections(theSections);
#endif // _DEBUG

	Debug_If_Condition(theSections.empty());
	auto iter = theSections.begin();
	auto b = (*iter)->BoundingBox();
	iter++;
	while (iter NOT_EQUAL theSections.end())
	{
		b = Entity2d_Box::Union(b, (*iter)->BoundingBox());
		iter++;
	}
	return std::move(b);
}

tnbLib::Entity3d_Box 
tnbLib::MarineBase_Tools::CalcBoundingBox
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	Debug_If_Condition(theSections.empty());
	auto box2 = CalcBoundingBox2D(theSections);

	const auto y0 = box2.P0().X();
	const auto y1 = box2.P1().X();
	const auto z0 = box2.P0().Y();
	const auto z1 = box2.P1().Y();

	Debug_Null_Pointer(theSections[0]);
	const auto x0 = theSections[0]->X();

	Debug_Null_Pointer(theSections[theSections.size() - 1]);
	const auto x1 = theSections[theSections.size() - 1]->X();

	Entity3d_Box b3(Pnt3d(x0, y0, z0), Pnt3d(x1, y1, z1));
	return std::move(b3);
}

Handle(Geom2d_Curve)
tnbLib::MarineBase_Tools::Curve
(
	const std::vector<marineLib::xSectionParam>& theQ,
	const Standard_Boolean tessellation,
	const Standard_Real tol
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn
		(
			"Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)"
		)
			<< "Not enough points"
			<< abort(FatalError);
	}

	if (theQ.size() IS_EQUAL 2)
	{
		const auto& Q0 = theQ[0];
		const auto& Q1 = theQ[1];

		if (marineLib::distance(Q0, Q1) <= tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid data for interpolating points have been detected!" << endl
				<< abort(FatalError);
		}

		auto curve = Pln_CurveTools::MakeSegment(marineLib::point(Q0), marineLib::point(Q1));
		return std::move(curve);
	}
	else
	{
		std::vector<marineLib::xSectionParam> Q;
		if (theQ.size() < MIN_NB_POINTS_INTERPOLATION AND tessellation)
		{
			Q = SteffenTessellation(theQ);
		}
		else
		{
			Q = theQ;
		}

		Handle(TColgp_HArray1OfPnt2d) PtsPtr =
			new TColgp_HArray1OfPnt2d(1, (Standard_Integer)Q.size());
		auto& Pts = *PtsPtr;

		Standard_Integer K = 0;
		for (const auto& x : Q)
		{
			Pts.SetValue(++K, marineLib::point(x));
		}

		try
		{
			Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, tol);
			Interpolation.Perform();

			if (!Interpolation.IsDone())
			{
				FatalErrorIn
				(
					"Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)"
				)
					<< "Failed to interpolation!"
					<< abort(FatalError);
			}

			return Interpolation.Curve();
		}
		catch (StdFail_NotDone&)
		{
			return nullptr;
		}
	}
}

Standard_Real
tnbLib::MarineBase_Tools::CalcBWL
(
	const Marine_CmpSection & theSection
)
{
	const auto b = theSection.BoundingBox();
	const auto[dx, dy] = b.Length();
	return dx;
}

std::vector<Standard_Real> 
tnbLib::MarineBase_Tools::CalcDx
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	std::vector<Standard_Real> Dx(theSections.size(), 0);
	for (size_t i = 1; i < theSections.size() - 1; i++)
	{
		auto dx0 = theSections[i]->X() - theSections[i - 1]->X();
		auto dx1 = theSections[i + 1]->X() - theSections[i]->X();

		auto dx = MEAN(dx0, dx1);

		Dx[i] = dx;
	}

	Dx[0] = theSections[1]->X() - theSections[0]->X();
	Dx[Dx.size() - 1] = theSections[theSections.size() - 1]->X() - theSections[theSections.size() - 2]->X();
	return std::move(Dx);
}

tnbLib::Geo_Interval<Standard_Real> 
tnbLib::MarineBase_Tools::CalcLateralProjArea
(
	const std::shared_ptr<Marine_Section>& theSection
)
{
	Debug_Null_Pointer(theSection);
	const auto b = theSection->BoundingBox();
	return Geo_Interval<Standard_Real>(b.P0().Y(), b.P1().Y());
}

std::vector<tnbLib::Geo_Interval<Standard_Real>> 
tnbLib::MarineBase_Tools::CalcLateralAreaIntervals
(
	const std::shared_ptr<Marine_CmpSection>& theSection
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "it's not a x-section!" << endl
			<< abort(FatalError);
	}
	std::vector<Geo_Interval<Standard_Real>> intervals;
	intervals.reserve(theSection->NbSections());
	for (const auto& x : theSection->Sections())
	{
		Debug_Null_Pointer(x);
		auto interval = CalcLateralProjArea(x);
		intervals.push_back(std::move(interval));
	}

	std::sort
	(
		intervals.begin(),
		intervals.end(),
		[](
			const Geo_Interval<Standard_Real>& v0,
			const Geo_Interval<Standard_Real>& v1
			)-> bool
	{
		return MEAN(v0.X0(), v0.X1()) <= MEAN(v1.X0(), v1.X1());
	}
	);
	return std::move(intervals);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcLateralProjArea
(
	const std::shared_ptr<Marine_CmpSection>& theSection
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "it's not a x-section!" << endl
			<< abort(FatalError);
	}
	auto intervals = CalcLateralAreaIntervals(theSection);

	auto merged = MergeIntervals(intervals);
	
	Standard_Real sumArea = 0;
	Standard_Real sumNumer = 0;
	for (const auto& x : merged)
	{
		auto area = x.Length();
		auto zbar = MEAN(x.X0(), x.X1());

		sumArea += area;
		sumNumer += (zbar*area);
	}
	auto t = std::make_pair(sumArea, sumNumer / sumArea);
	return std::move(t);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcLateralProjArea
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	std::vector<marineLib::xSectionParam> Qs;
	Qs.reserve(theSections.size());
	
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		auto area = CalcLateralProjArea(x);

		marineLib::xSectionParam p{ x->X(),area.first };
		Qs.push_back(std::move(p));
	}
	return std::move(Qs);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcLateralZbar
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real z0
)
{
	std::vector<marineLib::xSectionParam> Qs;
	Qs.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		auto interval = CalcLateralProjArea(x);
		auto zBar = interval.second - z0;

		marineLib::xSectionParam p{ x->X(),zBar };
		Qs.push_back(std::move(p));
	}
	return std::move(Qs);
}

namespace tnbLib
{
	auto NormalizedQs(const std::vector<marineLib::xSectionParam>& theQ)
	{
		auto iter = theQ.begin();
		auto maxValue = iter->value;
		for (const auto& x : theQ)
		{
			if (x.value > maxValue) maxValue = x.value;
		}

		if (maxValue < 1.0)
		{
			maxValue = 1.0;
		}

		auto minX = iter->x;
		auto maxX = minX;
		for (const auto& x : theQ)
		{
			if (x.x > maxX) maxX = x.x;
			if (x.x < minX) minX = x.x;
		}

		auto dx = maxX - minX;
		auto Qs = theQ;
		for (auto& x : Qs)
		{
			x.value *= (1.0 / maxValue);
			x.x -= minX;
			x.x *= (1.0 / dx);
		}
		auto t = std::make_tuple(dx, maxValue, std::move(Qs));
		return std::move(t);
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcArea
(
	const std::vector<marineLib::xSectionParam>& theQ,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (theQ.size() < 2)
	{
		FatalErrorIn
		(
			"Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)"
		)
			<< "Not enough points"
			<< abort(FatalError);
	}

	if (theQ.size() IS_EQUAL 2)
	{
		const auto& q0 = theQ[0];
		const auto& q1 = theQ[1];

		return 0.5*(q0.value + q1.value)*(q1.x - q0.x);
	}
	else
	{
		auto[dx, maxValue, Qn] = NormalizedQs(theQ);

		std::vector<marineLib::xSectionParam> Q;
		if (Qn.size() < MIN_NB_POINTS_INTERPOLATION)
		{
			Q = SteffenTessellation(Qn);
		}
		else
		{
			Q = Qn;
		}

		Handle(TColgp_HArray1OfPnt2d) PtsPtr = new TColgp_HArray1OfPnt2d(1, (Standard_Integer)Q.size());
		auto& Pts = *PtsPtr;

		Standard_Integer K = 0;
		for (const auto& x : Q)
		{
			Pts.SetValue(++K, gp_Pnt2d(x.x, x.value));
		}

		Geom2dAPI_Interpolate Interpolation(PtsPtr, Standard_False, 1.0e-6);
		Interpolation.Perform();

		if (!Interpolation.IsDone())
		{
			FatalErrorIn
			(
				"Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)"
			)
				<< "Failed to interpolation!"
				<< abort(FatalError);
		}

		/*OFstream ff("curve.plt");
		auto nn = 50;
		std::vector<Pnt2d> pp;
		pp.reserve(nn+1);
		const auto& cc = Interpolation.Curve();
		auto dx = (cc->LastParameter() - cc->FirstParameter()) / (nn);
		for (size_t i = 0; i <= nn; i++)
		{
			auto x = cc->FirstParameter() + i * dx;
			pp.push_back(cc->Value(x));
		}
		Io::ExportCurve(pp, ff);*/

		try
		{
			auto area0 = Cad2d_CmptLib::AreaUnderCurve(Interpolation.Curve(), 0, theInfo);
			return area0 * (dx*maxValue);
		}
		catch (StdFail_NotDone&)
		{
			FatalErrorIn
			(
				"Standard_Real MarineBase_Tools::CalcArea(const std::vector<marineLib::xSectionParam>& theQ)"
			)
				<< "Failed to interpolation!"
				<< abort(FatalError);

			return 0;
		}
	}
}

Standard_Real
tnbLib::MarineBase_Tools::CalcArea
(
	const std::shared_ptr<Marine_Section> & theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn
		(
			"Standard_Real CalcArea(const Marine_Section& theSection, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)"
		)
			<< "invalid section: null wire" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.size())
	{
		const auto outerArea = Cad2d_CmptLib::Area(*theSection->Wire(), theInfo);
		Debug_If_Condition(outerArea <= 0);
		auto innerArea = (Standard_Real)0;
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			auto area = Cad2d_CmptLib::Area(*theSection->Wire(), theInfo);

			Debug_If_Condition(area >= 0);
			innerArea += area;
		}
		return outerArea + innerArea;
	}
	else
	{
		const auto area = Cad2d_CmptLib::Area(*theSection->Wire(), theInfo);
		Debug_If_Condition(area <= 0);
		return area;
	}	
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcArea
(
	const Marine_CmpSection & theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sumArea = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sumArea += CalcArea(x, theInfo);
	}
	Debug_If_Condition(sumArea <= 0);
	return sumArea;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcIx
(
	const std::shared_ptr<Marine_Section>& theSection,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid section" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.size())
	{
		const auto outerIx = Cad2d_CmptLib::Ix(*theSection->Wire(), y0, theInfo);
		//Debug_If_Condition(outerIx < theInfo->Tolerance());

		auto innerIx = (Standard_Real)0;
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			auto ix = Cad2d_CmptLib::Ix(*x->Wire(), y0, theInfo);

			//Debug_If_Condition(ix > theInfo->Tolerance());
			innerIx += ix;
		}
		return outerIx + innerIx;
	}
	else
	{
		const auto outerIx = Cad2d_CmptLib::Ix(*theSection->Wire(), y0, theInfo);
		//Debug_If_Condition(outerIx < theInfo->Tolerance());
		return outerIx;
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcIx
(
	const Marine_CmpSection & theSection,
	const Standard_Real y0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Standard_Real sum = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sum += CalcIx(x, y0, theInfo);
	}
	return sum;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcIy
(
	const std::shared_ptr<Marine_Section>& theSection,
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid section" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.size())
	{
		const auto outerIy = Cad2d_CmptLib::Iy(*theSection->Wire(), x0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());

		auto innerIy = (Standard_Real)0;
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			auto iy = Cad2d_CmptLib::Iy(*x->Wire(), x0, theInfo);

			//Debug_If_Condition(iy > theInfo->Tolerance());
			innerIy += iy;
		}
		return outerIy + innerIy;
	}
	else
	{
		const auto outerIy = Cad2d_CmptLib::Iy(*theSection->Wire(), x0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());
		return outerIy;
	}
}

Standard_Real
tnbLib::MarineBase_Tools::CalcIy
(
	const Marine_CmpSection & theSection,
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG
	Standard_Real sum = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sum += CalcIy(x, x0, theInfo);
	}
	return sum;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcMx
(
	const std::shared_ptr<Marine_Section>& theSection,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid section" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.size())
	{
		const auto outerMx = Cad2d_CmptLib::Mx(*theSection->Wire(), y0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());

		auto innerMx = (Standard_Real)0;
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			auto iy = Cad2d_CmptLib::Mx(*x->Wire(), y0, theInfo);

			//Debug_If_Condition(iy > theInfo->Tolerance());
			innerMx += iy;
		}
		return outerMx + innerMx;
	}
	else
	{
		const auto outerMx = Cad2d_CmptLib::Mx(*theSection->Wire(), y0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());
		return outerMx;
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcMy
(
	const std::shared_ptr<Marine_Section>& theSection,
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid section" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.size())
	{
		const auto outerMy = Cad2d_CmptLib::My(*theSection->Wire(), x0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());

		auto innerMy = (Standard_Real)0;
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			auto iy = Cad2d_CmptLib::My(*x->Wire(), x0, theInfo);

			//Debug_If_Condition(iy > theInfo->Tolerance());
			innerMy += iy;
		}
		return outerMy + innerMy;
	}
	else
	{
		const auto outerMy = Cad2d_CmptLib::My(*theSection->Wire(), x0, theInfo);
		//Debug_If_Condition(outerIy < theInfo->Tolerance());
		return outerMy;
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcMx
(
	const Marine_CmpSection & theSection,
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG
	Standard_Real sum = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sum += CalcMx(x, x0, theInfo);
	}
	return sum;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcMy
(
	const Marine_CmpSection & theSection,
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG
	Standard_Real sum = 0;
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		sum += CalcMy(x, x0, theInfo);
	}
	return sum;
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcIx
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> sections;
	sections.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam ix;
		ix.x = x->X();
		ix.value = CalcIx(*x, y0, theInfo);

		sections.push_back(std::move(ix));
	}
	return std::move(sections);
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::MarineBase_Tools::CalcIy
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real x0,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> sections;
	sections.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam ix;
		ix.x = x->X();
		ix.value = CalcIy(*x, x0, theInfo);

		sections.push_back(std::move(ix));
	}
	return std::move(sections);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcMx
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const Standard_Real y0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> sections;
	sections.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam iy;
		iy.x = x->X();
		iy.value = CalcMx(*x, y0, theInfo);

		sections.push_back(std::move(iy));
	}
	return std::move(sections);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcMy
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real x0, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> sections;
	sections.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam ix;
		ix.x = x->X();
		ix.value = CalcMy(*x, x0, theInfo);

		sections.push_back(std::move(ix));
	}
	return std::move(sections);
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWettedArea
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		return (Standard_Real)0.0;
	}
	else
	{
		return CalcArea(theSection, theInfo);
	}
}

tnbLib::Pnt2d 
tnbLib::MarineBase_Tools::CalcCentre
(
	const std::shared_ptr<Marine_Section>& theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection);
	if (NOT theSection->Wire())
	{
		FatalErrorIn
		(
			"Pnt2d CalcCentre(const Marine_Section& theSection, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)"
		)
			<< "invalid section: null wire" << endl
			<< abort(FatalError);
	}

	const auto innerSections = Marine_SectTools::RetrieveInners(theSection);
	if (innerSections.empty())
	{
		auto c = Cad2d_CmptLib::Centre(*theSection->Wire(), theInfo);
		return std::move(c);
	}
	else
	{
		auto mx = Cad2d_CmptLib::Mx(*theSection->Wire(), 0, theInfo);
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			mx += Cad2d_CmptLib::Mx(*theSection->Wire(), 0, theInfo);
		}

		auto my = Cad2d_CmptLib::My(*theSection->Wire(), 0, theInfo);
		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);
			my += Cad2d_CmptLib::My(*theSection->Wire(), 0, theInfo);
		}

		auto area = CalcArea(theSection, theInfo);
		Pnt2d c(my / area, mx / area);
		return std::move(c);
		/*auto c0 = Cad2d_CmptLib::Centre(*theSection->Wire(), theInfo);
		auto h0 = Cad2d_CmptLib::Area(*theSection->Wire(), theInfo);

		std::vector<Pnt2d> cs;
		cs.reserve(innerSections.size());

		std::vector<Standard_Real> h;
		h.reserve(innerSections.size());

		for (const auto& x : innerSections)
		{
			Debug_Null_Pointer(x);

			auto area = Cad2d_CmptLib::Area(*x->Wire(), theInfo);
			auto c = Cad2d_CmptLib::Centre(*x->Wire(), theInfo);

			cs.push_back(std::move(c));
			h.push_back(area);
		}

		Pnt2d sum = h0 * c0;
		Standard_Integer K = 0;
		for (const auto& x : cs)
		{
			sum += h[K++] * x;
		}

		Standard_Real sumA = h0;
		for (const auto x : h)
		{
			sumA += x;
		}

		return sum / sumA;*/
	}
}

tnbLib::Pnt2d 
tnbLib::MarineBase_Tools::CalcCentre
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	const auto mx = CalcMx(theSection, 0, theInfo);
	const auto my = CalcMy(theSection, 0, theInfo);
	const auto area = CalcArea(theSection, theInfo);
	Pnt2d c(my / area, mx / area);
	return std::move(c);
	/*std::vector<Pnt2d> cs;
	cs.reserve(theSection.NbSections());

	std::vector<Standard_Real> h;
	h.reserve(theSection.NbSections());

	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);

		auto area = CalcArea(x, theInfo);
		auto c = CalcCentre(x, theInfo);

		cs.push_back(std::move(c));
		h.push_back(area);
	}

	if (cs.size() IS_EQUAL 1)
		return cs[0];

	Pnt2d sum;
	Standard_Integer K = 0;
	for (const auto& x : cs)
	{
		sum += h[K++] * x;
	}

	Standard_Real sumA = 0;
	for (const auto x : h)
	{
		sumA += x;
	}

	return sum / sumA;*/
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcXCentre
(
	const std::shared_ptr<Marine_Section>& theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto ctr = CalcCentre(theSection, theInfo);
	return ctr.X();
}

Standard_Real
tnbLib::MarineBase_Tools::CalcYCentre
(
	const std::shared_ptr<Marine_Section>& theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto ctr = CalcCentre(theSection, theInfo);
	return ctr.Y();
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcXCentre
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto ctr = CalcCentre(theSection, theInfo);
	return ctr.X();
}

Standard_Real
tnbLib::MarineBase_Tools::CalcYCentre
(
	const Marine_CmpSection & theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	auto ctr = CalcCentre(theSection, theInfo);
	return ctr.Y();
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::MarineBase_Tools::CalcVolume
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> params;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xParam;

		xParam.x = x->X();
		xParam.value = CalcArea(*x, theInfo);

		params.push_back(std::move(xParam));
	}

	return std::move(params);
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWaterCurveLength
(
	const marineLib::Section_Wetted& theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	if (theSection.DeepCondition())
	{
		return 0;
	}

	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);
		
		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());
			sum += Pln_Tools::Length(*curve->Geometry(), theInfo);
		}
	}
	return sum;
}

tnbLib::Entity2d_Box 
tnbLib::MarineBase_Tools::RetrieveRectangle
(
	const Marine_WaterCurve & theCurve, 
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	auto p0 = theCurve.FirstCoord();
	auto p1 = theCurve.LastCoord();

	auto y0 = std::min(p0.X(), p1.X());
	auto y1 = std::max(p0.X(), p1.X());

	auto x0 = xs - 0.5*dx;
	auto x1 = xs + 0.5*dx;

	auto box = Entity2d_Box(Pnt2d(x0, y0), Pnt2d(x1, y1));
	return std::move(box);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIx
(
	const Marine_WaterCurve & theCurve, 
	const Standard_Real y0, 
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	auto b = RetrieveRectangle(theCurve, xs, dx);
	auto t = std::make_pair(Geo_CmptLib::Ix(b, y0), Geo_CmptLib::Area(b));
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIy
(
	const Marine_WaterCurve & theCurve, 
	const Standard_Real x0,
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	auto b = RetrieveRectangle(theCurve, xs, dx);
	auto t = std::make_pair(Geo_CmptLib::Iy(b, x0), Geo_CmptLib::Area(b));
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMx
(
	const Marine_WaterCurve & theCurve,
	const Standard_Real y0,
	const Standard_Real xs,
	const Standard_Real dx
)
{
	auto b = RetrieveRectangle(theCurve, xs, dx);
	auto t = std::make_pair(Geo_CmptLib::Mx(b, y0), Geo_CmptLib::Area(b));
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMy
(
	const Marine_WaterCurve & theCurve,
	const Standard_Real x0, 
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	auto b = RetrieveRectangle(theCurve, xs, dx);
	auto t = std::make_pair(Geo_CmptLib::My(b, x0), Geo_CmptLib::Area(b));
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIx
(
	const marineLib::Section_Wetted & theSection,
	const Standard_Real y0,
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	if (theSection.DeepCondition())
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}

	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	Standard_Real sumA = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());

			auto water = std::dynamic_pointer_cast<Marine_WaterCurve>(mCurve);
			Debug_Null_Pointer(water);

			auto t = CalcWaterCurveIx(*water, y0, xs, dx);
			sum += t.first;
			sumA += t.second;
		}
	}
	auto t = std::make_pair(sum, sumA);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIy
(
	const marineLib::Section_Wetted & theSection,
	const Standard_Real x0, 
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	if (theSection.DeepCondition())
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}

	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	Standard_Real sumA = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());

			auto water = std::dynamic_pointer_cast<Marine_WaterCurve>(mCurve);
			Debug_Null_Pointer(water);

			auto t = CalcWaterCurveIy(*water, x0, xs, dx);
			sum += t.first;
			sumA += t.second;
		}
	}
	auto t = std::make_pair(sum, sumA);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMx
(
	const marineLib::Section_Wetted & theSection, 
	const Standard_Real y0, 
	const Standard_Real xs,
	const Standard_Real dx
)
{
	if (theSection.DeepCondition())
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}

	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	Standard_Real sumA = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());

			auto water = std::dynamic_pointer_cast<Marine_WaterCurve>(mCurve);
			Debug_Null_Pointer(water);

			auto t = CalcWaterCurveMx(*water, y0, xs, dx);
			sum += t.first;
			sumA += t.second;
		}
	}
	auto t = std::make_pair(sum, sumA);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMy
(
	const marineLib::Section_Wetted & theSection, 
	const Standard_Real x0, 
	const Standard_Real xs, 
	const Standard_Real dx
)
{
	if (theSection.DeepCondition())
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}

	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	Standard_Real sumA = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());

			auto water = std::dynamic_pointer_cast<Marine_WaterCurve>(mCurve);
			Debug_Null_Pointer(water);

			auto t = CalcWaterCurveMy(*water, x0, xs, dx);
			sum += t.first;
			sumA += t.second;
		}
	}
	auto t = std::make_pair(sum, sumA);
	return std::move(t);
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWaterCurveLength
(
	const Marine_CmpSection & theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		return (Standard_Real)0.;
	}
	else
	{
		Standard_Real len = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			if (NOT wetted->DeepCondition())
			{
				len += CalcWaterCurveLength(*wetted, theInfo);
			}
		}
		return len;
	}	
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIx
(
	const Marine_CmpSection & theSection,
	const Standard_Real xs,
	const Standard_Real y0,
	const Standard_Real dx
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT theSection.IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "the section is not x-section!" << endl
			<< abort(FatalError);
	}

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}
	else
	{
		Standard_Real sum = 0;
		Standard_Real sumA = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			if (NOT wetted->DeepCondition())
			{
				auto t = CalcWaterCurveIx(*wetted, y0, xs, dx);
				sum += t.first;
				sumA += t.second;
			}
		}
		auto t = std::make_pair(sum, sumA);
		return std::move(t);
	}
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveIy
(
	const Marine_CmpSection & theSection,
	const Standard_Real xs,
	const Standard_Real x0, 
	const Standard_Real dx
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT theSection.IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "the section is not x-section!" << endl
			<< abort(FatalError);
	}

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}
	else
	{
		Standard_Real sum = 0;
		Standard_Real sumA = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			if (NOT wetted->DeepCondition())
			{
				auto t = CalcWaterCurveIy(*wetted, x0, xs, dx);
				sum += t.first;
				sumA += t.second;
			}
		}
		auto t = std::make_pair(sum, sumA);
		return std::move(t);
	}
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMx
(
	const Marine_CmpSection & theSection, 
	const Standard_Real xs,
	const Standard_Real y0, 
	const Standard_Real dx
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT theSection.IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "the section is not x-section!" << endl
			<< abort(FatalError);
	}

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}
	else
	{
		Standard_Real sum = 0;
		Standard_Real sumA = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			if (NOT wetted->DeepCondition())
			{
				auto t = CalcWaterCurveMx(*wetted, y0, xs, dx);
				sum += t.first;
				sumA += t.second;
			}
		}
		auto t = std::make_pair(sum, sumA);
		return std::move(t);
	}
}

std::pair<Standard_Real, Standard_Real>
tnbLib::MarineBase_Tools::CalcWaterCurveMy
(
	const Marine_CmpSection & theSection, 
	const Standard_Real xs,
	const Standard_Real x0,
	const Standard_Real dx
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT theSection.IsXsection())
	{
		FatalErrorIn(FunctionSIG)
			<< "the section is not x-section!" << endl
			<< abort(FatalError);
	}

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		auto t = std::make_pair(0, 0);
		return std::move(t);
	}
	else
	{
		Standard_Real sum = 0;
		Standard_Real sumA = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			if (NOT wetted->DeepCondition())
			{
				auto t = CalcWaterCurveMy(*wetted, x0, xs, dx);
				sum += t.first;
				sumA += t.second;
			}
		}
		auto t = std::make_pair(sum, sumA);
		return std::move(t);
	}
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWettedHullCurveLength
(
	const marineLib::Section_Wetted& theSection,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Debug_Null_Pointer(theSection.Wire());
	const auto& wire = *theSection.Wire();

	Standard_Real sum = 0;
	for (const auto& x : wire.Edges())
	{
		Debug_Null_Pointer(x);

		const auto& curve = x->Curve();
		Debug_Null_Pointer(curve);

		if (NOT curve->IsMarine())
		{
			FatalErrorIn("Standard_Real MarineBase_Tools::CalcWaterCurveLength(Args...)")
				<< "the curve is not marine type!" << endl
				<< abort(FatalError);
		}

		auto mCurve = std::dynamic_pointer_cast<Marine_PlnCurve>(curve);
		Debug_Null_Pointer(mCurve);

		if (NOT mCurve->IsOnWater())
		{
			Debug_Null_Pointer(curve->Geometry());
			sum += Pln_Tools::Length(*curve->Geometry(), theInfo);
		}
	}
	return sum;
}

Standard_Real 
tnbLib::MarineBase_Tools::CalcWettedHullCurveLength
(
	const Marine_CmpSection & theSection, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
#ifdef _DEBUG
	Marine_SectTools::CheckTypeConsistency(theSection);
#endif // _DEBUG

	if (NOT Marine_SectTools::IsWetted(theSection))
	{
		return (Standard_Real)0.0;
	}
	else
	{
		Standard_Real sum = 0;
		for (const auto& x : theSection.Sections())
		{
			Debug_Null_Pointer(x);

			auto wetted = Marine_SectTools::WettedSection(x);
			Debug_Null_Pointer(wetted);

			sum += CalcWettedHullCurveLength(*wetted, theInfo);
		}
		return sum;
	}
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::MarineBase_Tools::CalcWettedHullSurfaceArea
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();
		p.value = CalcWettedHullCurveLength(*sect, theInfo);

		values.push_back(std::move(p));
	}
	return std::move(values);
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::MarineBase_Tools::CalcWaterPlaneArea
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();
		p.value = CalcWaterCurveLength(*sect, theInfo);

		values.push_back(std::move(p));
	}
	return std::move(values);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcWaterPlaneIx
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const Standard_Real y0
)
{
	if (theSections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body!" << endl
			<< abort(FatalError);
	}

	auto dx = CalcDx(theSections);

	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	size_t k = 0;
	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();

		auto t = CalcWaterCurveIx(*sect, sect->X(), y0, dx[k++]);
		if (t.second <= gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid area value has been detected!" << endl
				<< abort(FatalError);
		}
		p.value = t.first / t.second;

		values.push_back(std::move(p));
	}
	return std::move(values);
}

std::vector<tnbLib::marineLib::xSectionParam>
tnbLib::MarineBase_Tools::CalcWaterPlaneIy
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const Standard_Real x0
)
{
	if (theSections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body!" << endl
			<< abort(FatalError);
	}

	auto dx = CalcDx(theSections);

	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	size_t k = 0;
	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();

		auto t = CalcWaterCurveIy(*sect, sect->X(), x0, dx[k++]);
		if (t.second <= gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid area value has been detected!" << endl
				<< abort(FatalError);
		}
		p.value = t.first / t.second;
		values.push_back(std::move(p));
	}
	return std::move(values);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcWaterPlaneMx
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const Standard_Real y0
)
{
	if (theSections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body!" << endl
			<< abort(FatalError);
	}

	auto dx = CalcDx(theSections);

	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	size_t k = 0;
	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();

		auto t = CalcWaterCurveMx(*sect, sect->X(), y0, dx[k++]);
		if (t.second <= gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid area value has been detected!" << endl
				<< " - area = " << t.second << endl
				<< abort(FatalError);
		}
		p.value = t.first / t.second;

		values.push_back(std::move(p));
	}
	return std::move(values);
}

std::vector<tnbLib::marineLib::xSectionParam> 
tnbLib::MarineBase_Tools::CalcWaterPlaneMy
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	const Standard_Real x0
)
{
	if (theSections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body!" << endl
			<< abort(FatalError);
	}

	auto dx = CalcDx(theSections);

	std::vector<marineLib::xSectionParam> values;
	values.reserve(theSections.size());

	size_t k = 0;
	for (const auto& sect : theSections)
	{
		Debug_Null_Pointer(sect);

		marineLib::xSectionParam p;
		p.x = sect->X();

		auto t = CalcWaterCurveMy(*sect, sect->X(), x0, dx[k++]);
		if (t.second <= gp::Resolution())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid area value has been detected!" << endl
				<< abort(FatalError);
		}
		p.value = t.first / t.second;

		values.push_back(std::move(p));
	}
	return std::move(values);
}

//std::vector<tnbLib::marineLib::xSectionParam> 
//tnbLib::MarineBase_Tools::CalcWaterPlaneIx
//(
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
//	const Standard_Real y0, 
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	return std::vector<marineLib::xSectionParam>();
//}

tnbLib::Pnt3d 
tnbLib::MarineBase_Tools::CalcCentreProductVolume
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	std::vector<Pnt2d> Bx;
	Bx.reserve(theSections.size());

	std::vector<Standard_Real> Ax;
	Ax.reserve(theSections.size());

	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		
		auto bx = CalcCentre(*x, theInfo);

		Bx.push_back(std::move(bx));
		Ax.push_back(CalcArea(*x, theInfo));
	}

	std::vector<marineLib::xSectionParam> xBarQ;
	xBarQ.reserve(theSections.size());

	Standard_Integer K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		
		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Ax[K++] * x->X();

		xBarQ.push_back(std::move(xSect));
	}

	const auto xBarC = Curve(xBarQ);
	if (NOT xBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: xBarC" << endl
			<< abort(FatalError);
	}

	std::vector<marineLib::xSectionParam> yBarQ;
	yBarQ.reserve(theSections.size());

	K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Bx[K].X() * Ax[K];

		K++;

		yBarQ.push_back(std::move(xSect));
	}

	const auto yBarC = Curve(yBarQ);
	if (NOT yBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: yBarC" << endl
			<< abort(FatalError);
	}

	std::vector<marineLib::xSectionParam> zBarQ;
	zBarQ.reserve(theSections.size());

	K = 0;
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);

		marineLib::xSectionParam xSect;
		xSect.x = x->X();
		xSect.value = Bx[K].Y() * Ax[K];

		K++;

		zBarQ.push_back(std::move(xSect));
	}

	const auto zBarC = Curve(zBarQ);
	if (NOT zBarC)
	{
		FatalErrorIn("Pnt3d MarineBase_Tools::CalcCentre(Args...)")
			<< "Unable to interpolate the offset points: zBarC" << endl
			<< abort(FatalError);
	}

	//const auto vol = Cad2d_CmptLib::AreaUnderCurve(xBarC, 0, theInfo);

	const auto xBar = Cad2d_CmptLib::AreaUnderCurve(xBarC, 0, theInfo);
	const auto yBar = Cad2d_CmptLib::AreaUnderCurve(yBarC, 0, theInfo);
	const auto zBar = Cad2d_CmptLib::AreaUnderCurve(zBarC, 0, theInfo);

	return Pnt3d(xBar, yBar, zBar);
}

void tnbLib::MarineBase_Tools::Heel
(
	const std::shared_ptr<Marine_CmpSection>& theSection,
	const gp_Ax2d & theAx
)
{
	const auto& sys = theSection->CoordinateSystem();
	const auto& loc = sys.Location();

	gp_Ax2d O(Pnt2d(loc.X(), loc.Y()), gp_Dir2d(1, 0));

	gp_Trsf2d t;
	t.SetTransformation(theAx, O);

	theSection->Transform(t);

	gp_Trsf2d t1;
	t1.SetTranslation(theAx.Location(), O.Location());

	theSection->Transform(t1);
}

void tnbLib::MarineBase_Tools::Heel
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
	const gp_Ax2d & theAx
)
{
	for (const auto& x : theModel)
	{
		Debug_Null_Pointer(x);
		MarineBase_Tools::Heel(x, theAx);
	}
}

//void tnbLib::MarineBase_Tools::Heel
//(
//	const std::shared_ptr<Marine_Section>& theSection,
//	const gp_Ax2d & theAx
//)
//{
//	const auto& sys = theSection->CoordinateSystem();
//	const auto& loc = sys.Location();
//
//	gp_Ax2d O(Pnt2d(loc.X(), loc.Y()), gp_Dir2d(1, 0));
//
//	gp_Trsf2d t;
//	t.SetTransformation(O, theAx);
//
//	theSection->Transform(t.Inverted());
//
//	
//}

void tnbLib::MarineBase_Tools::Heel
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
	const gp_Ax1 & theAx, 
	const Standard_Real theAngle
)
{
	const auto& loc = theAx.Location();

	Pnt2d O(loc.Y(), loc.Z());
	gp_Dir2d dir(cos(theAngle), sin(theAngle));

	gp_Ax2d ax(O, dir);

	for (const auto& x : theModel)
	{
		Debug_Null_Pointer(x);
		Heel(x, ax);
	}
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::MarineBase_Tools::HeelDistb
(
	const Standard_Real theDeg0,
	const Standard_Real theDeg1,
	const Standard_Integer theNbHeels
)
{
	const auto rad0 = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theDeg0;
	const auto rad1 = ConvertUnit(UnitSystem_Angle_deg, UnitSystem_Angle_rad)*theDeg1;

	auto distb = std::make_shared<Geo_UniDistb>(theNbHeels);
	Debug_Null_Pointer(distb);

	distb->SetLower(rad0);
	distb->SetUpper(rad1);

	distb->Perform();

	return std::move(distb);
}

#include <Cad2d_Plane.hxx>
#include <Cad2d_Boolean.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Sections.hxx>
#include <Marine_Wave.hxx>

#include <Standard_Handle.hxx>
#include <gp_Pln.hxx>
#include <Geom_Line.hxx>
#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Plane.hxx>
#include <GeomProjLib.hxx>
#include <Geom_Surface.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Edge.hxx>

//namespace tnbLib
//{
//
//	namespace marineLib
//	{
//
//		static Handle(Geom_Curve)
//			CreateLine
//			(
//				const Pnt3d& theP0,
//				const Pnt3d& theP1
//			)
//		{
//			gp_Vec v(theP0, theP1);
//			Handle(Geom_Curve) c = new Geom_Line(theP0, gp_Dir(v));
//
//			GeomAPI_ProjectPointOnCurve proj;
//			proj.Init(theP0, c);
//
//			const auto u0 = proj.LowerDistanceParameter();
//
//			proj.Init(theP1, c);
//
//			const auto u1 = proj.LowerDistanceParameter();
//
//			auto trimmed = Cad_Tools::ConvertToTrimmed(c, u0, u1);
//			return std::move(trimmed);
//		}
//	}
//}

//std::shared_ptr<tnbLib::Pln_Wire> 
//tnbLib::MarineBase_Tools::WaterSection
//(
//	const Handle(Geom_Curve)& theCurve,
//	const gp_Ax2 & theSystem,
//	const Standard_Real theZmin, 
//	const Standard_Real theMinTol,
//	const Standard_Real theMaxTol
//)
//{
//	Pnt3d leftPt;
//	Pnt3d rightPt;
//
//	auto p0 = theCurve->Value(theCurve->FirstParameter());
//	auto p1 = theCurve->Value(theCurve->LastParameter());
//
//	if (p0.Y() < p1.Y())
//	{
//		leftPt = p0;
//		rightPt = p1;
//	}
//	else
//	{
//		leftPt = p1;
//		rightPt = p0;
//	}
//
//	auto p2 = leftPt + (theZmin - leftPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());
//	auto p3 = rightPt + (theZmin - rightPt.Z()) * Pnt3d(theSystem.YDirection().XYZ());
//
//	auto c0 = marineLib::CreateLine(leftPt, p2);
//	auto c1 = marineLib::CreateLine(p2, p3);
//	auto c2 = marineLib::CreateLine(p3, rightPt);
//
//	gp_Pln plane(theSystem);
//	Handle(Geom_Plane) g = new Geom_Plane(plane);
//
//	auto cprj0 = GeomProjLib::ProjectOnPlane(c0, g, theSystem.Direction(), Standard_True);
//	auto cprj1 = GeomProjLib::ProjectOnPlane(c1, g, theSystem.Direction(), Standard_True);
//	auto cprj2 = GeomProjLib::ProjectOnPlane(c2, g, theSystem.Direction(), Standard_True);
//	auto cprj3 = GeomProjLib::ProjectOnPlane(theCurve, g, theSystem.Direction(), Standard_True);
//
//	auto c2d0 = GeomProjLib::Curve2d(cprj0, g);
//	if (NOT c2d0)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "unable to project the curve on the plane!" << endl
//			<< abort(FatalError);
//	}
//
//	auto c2d1 = GeomProjLib::Curve2d(cprj1, g);
//	if (NOT c2d1)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "unable to project the curve on the plane!" << endl
//			<< abort(FatalError);
//	}
//
//	auto c2d2 = GeomProjLib::Curve2d(cprj2, g);
//	if (NOT c2d2)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "unable to project the curve on the plane!" << endl
//			<< abort(FatalError);
//	}
//
//	auto c2d3 = GeomProjLib::Curve2d(cprj3, g);
//	if (NOT c2d3)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "unable to project the curve on the plane!" << endl
//			<< abort(FatalError);
//	}
//
//	std::vector<std::shared_ptr<Pln_Curve>> curves;
//	curves.push_back(std::make_shared<Marine_WaterCurve>(1, c2d0));
//	curves.push_back(std::make_shared<Marine_WaterCurve>(2, c2d1));
//	curves.push_back(std::make_shared<Marine_WaterCurve>(3, c2d2));
//	curves.push_back(std::make_shared<Marine_WaterCurve>(4, c2d3));
//
//	auto cmpSection =
//		Marine_CmpSection::CreateCmpSection(curves, theSystem, theMinTol, theMaxTol);
//	Debug_Null_Pointer(cmpSection);
//
//	if (cmpSection->NbSections() NOT_EQUAL 1)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "contradictory data" << endl
//			<< abort(FatalError);
//	}
//
//	auto wire = cmpSection->Sections()[0]->Wire();
//	Debug_Null_Pointer(wire);
//
//	return std::move(wire);
//}

namespace tnbLib
{

	namespace marineLib
	{

		/*static std::shared_ptr<Marine_Section>
			CreateWaterSection
			(
				const std::shared_ptr<Pln_Wire>& theSection,
				const std::shared_ptr<Pln_Wire>& theWater
			)
		{
			auto section = Cad2d_Plane::MakePlane(theSection, nullptr);
			Debug_Null_Pointer(section);

			auto water = Cad2d_Plane::MakePlane(theWater, nullptr);
			Debug_Null_Pointer(water);

			auto intsct = Cad2d_Boolean::Intersection(section, water);

			if (intsct)
			{
				if (intsct IS_EQUAL section)
				{
					Debug_Null_Pointer(intsct->OuterWire());

					auto wet = std::make_shared<Marine_WetSection>(intsct->OuterWire());
					Debug_Null_Pointer(wet);

					wet->SetDeep(Standard_True);
					return std::move(wet);
				}
				else
				{
					Debug_Null_Pointer(intsct->OuterWire());

					auto wet = std::make_shared<Marine_WetSection>(intsct->OuterWire());
					Debug_Null_Pointer(wet);

					wet->SetDeep(Standard_False);
					return std::move(wet);
				}
			}
			return nullptr;
		}*/

		/*static Handle(Geom_Curve)
			WaterLine
			(
				const Handle(Geom_Surface)& theSurface,
				const gp_Ax2& theSystem
			)
		{
			gp_Pln plane(theSystem);

			BRepAlgoAPI_Section alg;
			alg.SetRunParallel(Standard_True);
			alg.Init1(plane);
			alg.Init2(theSurface);

			alg.Build();

			if (alg.Shape().IsNull())
			{
				FatalErrorIn(FunctionSIG)
					<< "Failed to calculate intersection" << endl
					<< abort(FatalError);
			}

			auto edges = Marine_CmpSection::RetrieveEdges(alg.Shape());
			if (edges.size() NOT_EQUAL 1)
			{
				FatalErrorIn(FunctionSIG)
					<< "Contradictory data" << endl
					<< abort(FatalError);
			}

			Standard_Real f, l;
			auto curve = BRep_Tool::Curve(edges[0], f, l);
			Debug_Null_Pointer(curve);

			if (NOT Handle(Geom_TrimmedCurve)::DownCast(curve))
			{
				curve = new Geom_TrimmedCurve(curve, f, l);
			}

			return std::move(curve);
		}*/
	}
}

//std::vector<std::shared_ptr<tnbLib::Marine_Section>>
//tnbLib::MarineBase_Tools::WaterSections
//(
//	const Marine_CrossSection& theModel,
//	const Marine_Wave& theWave,
//	const Entity3d_Box& theDomain,
//	const Standard_Real theMinTol,
//	const Standard_Real theMaxTol
//)
//{
//	const auto zmin = theDomain.P0().Z();
//	const auto& waterSurface = theWave.SurfaceGeometry();
//	if (NOT waterSurface)
//	{
//		FatalErrorIn("std::vector<std::shared_ptr<Marine_Section>> MarineBase_Tools::WaterSections(Args...)")
//			<< "no geometry is found for water surface" << endl
//			<< abort(FatalError);
//	}
//
//	std::vector<std::shared_ptr<Marine_Section>> waters;
//	Standard_Integer K = 0;
//	for (const auto& x : theModel.Sections())
//	{
//		Debug_Null_Pointer(x);
//
//		auto wl = marineLib::WaterLine(waterSurface, x->CoordinateSystem());
//		Debug_Null_Pointer(wl);
//
//		auto wa = WaterSection(wl, x->CoordinateSystem(), zmin, theMinTol, theMaxTol);
//		Debug_Null_Pointer(wa);
//
//		auto section = std::make_shared<Marine_Section>(++K, wa);
//		Debug_Null_Pointer(section);
//
//		section->SetCoordinateSystem(x->CoordinateSystem());
//		waters.push_back(std::move(section));
//	}
//	return std::move(waters);
//}

//std::vector<std::shared_ptr<tnbLib::Marine_Section>> 
//tnbLib::MarineBase_Tools::StillWaterSections
//(
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
//	const Standard_Real theZ,
//	const Entity3d_Box & theDomain
//)
//{
//	const auto y0 = theDomain.P0().Z();
//	const auto y1 = theZ;
//
//	const auto x0 = theDomain.P0().Y();
//	const auto x1 = theDomain.P1().Y();
//
//	auto pln = Cad2d_Plane::MakeBox(Pnt2d(x0, y0), Pnt2d(x1, y1));
//	Debug_Null_Pointer(pln);
//
//	const auto& wa = pln->OuterWire();
//	Debug_Null_Pointer(wa);
//
//	std::vector<std::shared_ptr<Marine_Section>> waters;
//	Standard_Integer K = 0;
//	for (const auto& x : theModel)
//	{
//		auto section = std::make_shared<Marine_Section>(++K, wa);
//		Debug_Null_Pointer(section);
//
//		section->SetCoordinateSystem(x->CoordinateSystem());
//		waters.push_back(std::move(section));
//	}
//	return std::move(waters);
//}


//std::vector<tnbLib::marineLib::xSectionParam> 
//tnbLib::MarineBase_Tools::CrossCurve
//(
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
//	const Entity3d_Box& theDomain,
//	const Standard_Real theZmin,
//	const Standard_Real theZmax,
//	const Standard_Integer nbZ, 
//	const gp_Ax1& theK,
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	if (nbZ < 2)
//	{
//		FatalErrorIn("std::vector<marineLib::xSectionParam> MarineBase_Tools::CrossCurve(Args...)")
//			<< "not enough sections for waters" << endl
//			<< abort(FatalError);
//	}
//
//	const auto& keel = theK.Location();
//
//	Pnt2d loc(keel.Y(), keel.Z());
//	gp_Ax2d Ix(loc, gp_Dir2d(0, 1));
//
//	std::vector<marineLib::xSectionParam> curves;
//	curves.reserve(nbZ);
//
//	const auto& p0 = theDomain.P0();
//	const auto& p1 = theDomain.P1();
//
//	const auto dz = (theZmax - theZmin) / (Standard_Real)nbZ;
//	for (auto i = 0; i <= nbZ; i++)
//	{
//		auto z = i * dz + theZmin;
//
//		auto waters = StillWaterSections(theSections, z, theDomain);
//
//		auto v = LeverArm(theSections, waters, Ix, theInfo);
//		curves.push_back(std::move(v));
//	}
//	return std::move(curves);
//}


//std::shared_ptr<tnbLib::Marine_WaterDomain> 
//tnbLib::MarineBase_Tools::RetrieveStillWaterDomain
//(
//	const std::shared_ptr<Marine_Domain>& theDomain,
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
//	const Standard_Real theZ
//)
//{
//	auto domain = std::make_shared<Marine_WaterDomain_Still>(theDomain);
//	Debug_Null_Pointer(domain);
//
//	domain->Perform(theModel, theZ);
//	Debug_If_Condition_Message(NOT domain->IsDone(), "the algorithm is not performed!");
//
//	return std::move(domain);
//}

//std::vector<std::shared_ptr<tnbLib::Marine_WaterDomain>> 
//tnbLib::MarineBase_Tools::RetrieveStillWaterDomains
//(
//	const std::shared_ptr<Marine_Domain>& theDomain,
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel,
//	const Standard_Real theZmin, 
//	const Standard_Real theZmax, 
//	const Standard_Integer nbZ
//)
//{
//	std::vector<std::shared_ptr<Marine_WaterDomain>> waters;
//	waters.reserve(nbZ + 1);
//	const auto dz = (theZmax - theZmin) / (Standard_Real)nbZ;
//
//	for (auto i = 0; i <= nbZ; i++)
//	{
//		auto z = theZmin + i * dz;
//		auto domain = RetrieveStillWaterDomain(theDomain, theModel, z);
//		Debug_Null_Pointer(domain);
//
//		waters.push_back(std::move(domain));
//	}
//	return std::move(waters);
//}

//std::vector<std::shared_ptr<tnbLib::Marine_WaterDomain>> 
//tnbLib::MarineBase_Tools::RetrieveStillWaterDomains
//(
//	const std::shared_ptr<Marine_Domain>& theDomain, 
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theModel, 
//	const Geo_xDistb & theZ
//)
//{
//	std::vector<std::shared_ptr<Marine_WaterDomain>> waters;
//	waters.reserve(theZ.Size() + 1);
//	for (auto z : theZ.Values())
//	{
//		auto domain = RetrieveStillWaterDomain(theDomain, theModel, z);
//		Debug_Null_Pointer(domain);
//
//		waters.push_back(std::move(domain));
//	}
//	return std::move(waters);
//}

//Standard_Real 
//tnbLib::MarineBase_Tools::CalcWetVolume
//(
//	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections, 
//	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
//)
//{
//	std::vector<marineLib::xSectionParam> params;
//	for (const auto& x : theSections)
//	{
//		Debug_Null_Pointer(x);
//
//		marineLib::xSectionParam xParam;
//
//		xParam.x = x->X();
//		xParam.value = CalcWettedArea(*x, theInfo);
//
//		params.push_back(std::move(xParam));
//	}
//
//	return CalcArea(params, theInfo);
//}

//#include <TModel_Surface.hxx>
//#include <Cad3d_TModel.hxx>
//#include <Marine_CmpSection.hxx>
//
//#include <BRepAlgoAPI_Section.hxx>
//#include <BRepBuilderAPI_MakeFace.hxx>
//#include <TopTools_ListOfShape.hxx>
//
//namespace tnbLib
//{
//
//	
//
//	
//
//
//}
//
//std::shared_ptr<tnbLib::Marine_CmpSection> 
//tnbLib::MarineBase_Tools::CreateSection
//(
//	const Cad3d_TModel & theModel,
//	const gp_Pln & thePlane,
//	const Standard_Boolean ParallelFalg
//)
//{
//	const auto& surfaces = theModel.RetrieveFaces();
//
//	std::map<Standard_Integer, std::shared_ptr<TModel_Surface>>
//		allSurfaces, meetSurface;
//	for (const auto& x : surfaces)
//	{
//		Debug_Null_Pointer(x);
//
//		auto insert = allSurfaces.insert(std::make_pair(x->Index(), x));
//		if (NOT insert.second)
//		{
//			FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> MarineBase_Tools::CreateSection()")
//				<< "duplicate data: cannot insert the face into the map: " << x->Index() << endl
//				<< abort(FatalError);
//		}
//	}
//
//	auto builder = BRepBuilderAPI_MakeFace(thePlane);
//	auto plane = builder.Face();
//
//	for (const auto& x : surfaces)
//	{
//		Debug_Null_Pointer(x);
//
//		auto iter = meetSurface.find(x->Index());
//		if (iter IS_EQUAL meetSurface.end())
//		{
//			auto insert = meetSurface.insert(std::make_pair(x->Index(), x));
//			if (NOT insert.second)
//			{
//				FatalErrorIn("std::shared_ptr<tnbLib::Marine_CmpSection> MarineBase_Tools::CreateSection()")
//					<< "duplicate data: cannot insert the face into the map: " << x->Index() << endl
//					<< abort(FatalError);
//			}
//
//			auto intShape =
//				CrossSection(plane, x->Face(), ParallelFalg);
//
//			if (NOT intShape.IsNull())
//			{
//
//			}
//		}
//	}
//
//	
//}

std::shared_ptr<tnbLib::Marine_Graph> 
tnbLib::MarineBase_Tools::CreateGraph(const Handle(Geom2d_Curve)& theCurve)
{
	auto box = Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(theCurve));

	auto g = std::make_shared<Marine_Graph>();
	Debug_Null_Pointer(g);

	g->X().SetLower(box.P0().X());
	g->X().SetUpper(box.P1().X());

	g->Y().SetLower(box.P0().Y());
	g->Y().SetUpper(box.P1().Y());

	auto& curves = g->ChangeCurves();
	curves.reserve(1);

	auto c = std::make_shared<Marine_GraphCurve>(1, theCurve);
	Debug_Null_Pointer(c);

	c->SetPattern(Marine_GraphLinePattern::Solid);

	curves.push_back(std::move(c));

	return std::move(g);
}

std::vector<tnbLib::Geo_Interval<Standard_Real>>
tnbLib::MarineBase_Tools::MergeIntervals
(
	const std::vector<Geo_Interval<Standard_Real>>& intervals
)
{
	if (intervals.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	std::vector<Geo_Interval<Standard_Real>> merged;
	auto v0 = intervals[0];
	for (size_t i = 1; i < intervals.size(); i++)
	{
		if (NOT v0.IsIntersect(intervals[i]))
		{
			merged.push_back(std::move(v0));
			v0 = intervals[i];
		}
		else
		{
			auto& v1 = intervals[i];
			auto x0 = std::min(v0.X0(), v1.X0());
			auto x1 = std::max(v0.X1(), v1.X1());

			Geo_Interval<Standard_Real> v(x0, x1);
			v0 = std::move(v);
		}
	}
	return std::move(merged);
}

tnbLib::Entity2d_Box 
tnbLib::MarineBase_Tools::RetrieveBox
(
	const Geo_Interval<Standard_Real>& theInterval, 
	const Standard_Real xo,
	const Standard_Real dx
)
{
	const auto y0 = theInterval.X0();
	const auto y1 = theInterval.X1();

	const auto x0 = xo - 0.5*dx;
	const auto x1 = xo + 0.5*dx;

	Pnt2d p0(x0, y0);
	Pnt2d p1(x1, y1);

	Entity2d_Box b(std::move(p0), std::move(p1));
	return std::move(b);
}

std::vector<tnbLib::Entity2d_Box>
tnbLib::MarineBase_Tools::RetrieveLateralProjArea
(
	const std::shared_ptr<Marine_CmpSection>& theSection, 
	const Standard_Real dx
)
{
	Debug_Null_Pointer(theSection);

	auto intervals = CalcLateralAreaIntervals(theSection);
	auto merged = MergeIntervals(intervals);

	std::vector<Entity2d_Box> boxes;
	boxes.reserve(merged.size());
	for (const auto& x : merged)
	{
		auto b = RetrieveBox(x, theSection->X(), dx);
		boxes.push_back(std::move(b));
	}
	return std::move(boxes);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::MarineBase_Tools::RetrieveLateralProjArea
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	Check_xCmptSections(theSections);

	if (theSections.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid body!" << endl
			<< abort(FatalError);
	}

	auto dx = CalcDx(theSections);

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	for (size_t i = 0; i < theSections.size() - 1; i++)
	{
		auto boxes = RetrieveLateralProjArea(theSections[i], dx[i]);
		for (const auto& x : boxes)
		{
			auto t = Geo_BoxTools::Triangulate(x);
			Debug_Null_Pointer(t);

			tri->Add(*t);
		}
	}
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::MarineBase_Tools::RetrieveTriangulation
(
	const Marine_Section & theSection
)
{
	const auto& wire = theSection.Wire();
	const auto& edges = wire->Edges();
	auto tris = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tris);
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		const auto& mesh = x->Mesh();
		if (NOT mesh)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not discretized!" << endl
				<< abort(FatalError);
		}
		auto chain = Geo_Tools::RetrieveChain(*mesh);
		auto tri = *Geo_Tools::Triangulation(*chain);
		tris->Add(std::move(tri));
	}
	return std::move(tris);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::MarineBase_Tools::RetrieveTriangulation
(
	const Marine_CmpSection & theSection
)
{
	auto tris = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tris);
	for (const auto& x : theSection.Sections())
	{
		Debug_Null_Pointer(x);
		auto tri = *RetrieveTriangulation(*x);
		tris->Add(std::move(tri));
	}
	return std::move(tris);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Triangulation>> 
tnbLib::MarineBase_Tools::RetrieveTriangulations2d
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	std::vector<std::shared_ptr<Entity2d_Triangulation>> tris;
	tris.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		auto tri = RetrieveTriangulation(*x);
		tris.push_back(std::move(tri));
	}
	return std::move(tris);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Triangulation>>
tnbLib::MarineBase_Tools::RetrieveTriangulations2d
(
	const std::vector<std::shared_ptr<Marine_Section>>& theSections
)
{
	std::vector<std::shared_ptr<Entity2d_Triangulation>> tris;
	tris.reserve(theSections.size());
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		auto tri = RetrieveTriangulation(*x);
		tris.push_back(std::move(tri));
	}
	return std::move(tris);
}

namespace tnbLib
{

	auto RetrieveTriangulation3d(const Standard_Real xcoord, const std::shared_ptr<Entity2d_Triangulation>& tri2d)
	{
		auto pts2d = std::move(tri2d->Points());
		auto indices = std::move(tri2d->Connectivity());
		std::vector<Pnt3d> pts;
		pts.reserve(pts2d.size());
		for (const auto& x : pts2d)
		{
			Pnt3d pt(xcoord, x.X(), x.Y());
			pts.push_back(std::move(pt));
		}

		auto tri = std::make_shared<Entity3d_Triangulation>();
		Debug_Null_Pointer(tri);
		tri->Points() = std::move(pts);
		tri->Connectivity() = std::move(indices);
		return std::move(tri);
	}
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::MarineBase_Tools::RetrieveTriangulation
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	auto tris2d = RetrieveTriangulations2d(theSections);
	size_t i = 0;
	auto tris = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tris);
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(tris2d[i]);
		auto xcoord = x->X();
		auto tri = *RetrieveTriangulation3d(xcoord, tris2d[i]);
		tris->Add(std::move(tri));
		i++;
	}
	return std::move(tris);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation>
tnbLib::MarineBase_Tools::RetrieveTriangulation
(
	const std::vector<std::shared_ptr<Marine_Section>>& theSections
)
{
	auto tris2d = RetrieveTriangulations2d(theSections);
	size_t i = 0;
	auto tris = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(tris);
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(tris2d[i]);
		auto xcoord = Marine_Section::GetXcoord(x);
		auto tri = *RetrieveTriangulation3d(xcoord, tris2d[i]);
		tris->Add(std::move(tri));
		i++;
	}
	return std::move(tris);
}

void tnbLib::MarineBase_Tools::Check_xCmptSections
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
)
{
	for (const auto& x : theSections)
	{
		Debug_Null_Pointer(x);
		if (NOT std::dynamic_pointer_cast<Marine_xCmpSection>(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the section is no xSection" << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::MarineBase_Tools::ExportToPlt
(
	const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections,
	OFstream & theFile
)
{
	auto tri = RetrieveTriangulation(theSections);
	Debug_Null_Pointer(tri);

	tri->ExportToPlt(theFile);
}

void tnbLib::MarineBase_Tools::ExportToPlt
(
	const std::vector<std::shared_ptr<Marine_Section>>& theSections,
	OFstream & theFile
)
{
	auto tri = RetrieveTriangulation(theSections);
	Debug_Null_Pointer(tri);

	tri->ExportToPlt(theFile);
}