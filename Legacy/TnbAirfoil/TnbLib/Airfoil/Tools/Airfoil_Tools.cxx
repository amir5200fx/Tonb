#include <Airfoil_Tools.hxx>

#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <Geo_xDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_Line.hxx>

std::vector<Standard_Real> 
tnbLib::Airfoil_Tools::CalcSpans
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
)
{
	auto iter = theCurves.begin();
	auto x0 = (*iter)->FirstCoord().X();
	auto x1 = (*iter)->LastCoord().X();

	std::vector<double> spans;
	spans.reserve(theCurves.size() + 1);
	spans.push_back(x0);
	spans.push_back(x1);

	iter++;
	while (iter NOT_EQUAL theCurves.end())
	{
		auto xi = (*iter)->LastCoord().X();
		spans.push_back(xi);

		iter++;
	}
	return std::move(spans);
}

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Airfoil_Tools::RetrieveCurve
(
	const Standard_Real x, 
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const std::vector<Standard_Real>& theSpans
)
{
	auto s = Geo_Tools::FindSpan(x, theSpans);
	return theCurves.at(std::min(s, theCurves.size() - 1));
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::Airfoil_Tools::xValue
(
	const Standard_Real x, 
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	Debug_Null_Pointer(theCurve);
	const auto& geom = theCurve->Geometry();

	gp_Pnt2d pt(x, 0);
	gp_Vec2d dir(0, 1);

	Handle(Geom2d_Curve) line = new Geom2d_Line(pt, dir);
	Geom2dAPI_InterCurveCurve alg(geom, line);

	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data to construct an airfoil" << endl
			<< abort(FatalError);
	}
	auto t = std::make_pair(alg.Point(1).Y(), alg.Intersector().Point(1).ParamOnFirst());
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::Airfoil_Tools::xValue
(
	const Standard_Real x,
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const std::vector<Standard_Real>& theSpans
)
{
	auto c = RetrieveCurve(x, theCurves, theSpans);
	auto t = xValue(x, c);
	return std::move(t);
}

std::tuple
<
	std::vector<Standard_Real>,
	std::vector<Standard_Real>,
	std::vector<tnbLib::Dir2d>
> tnbLib::Airfoil_Tools::CalcCamberPoints
(
	const Geo_xDistb& theDist,
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const std::vector<Standard_Real>& theSpans
)
{
	std::vector<Standard_Real> xs, ys;
	std::vector<Dir2d> ts;
	xs.reserve(theDist.Size());
	ys.reserve(theDist.Size());
	ts.reserve(theDist.Size());

	gp_Pnt2d pt;
	gp_Vec2d vt;
	for (auto t : theDist.Values())
	{
		const auto curve = RetrieveCurve(t, theCurves, theSpans);
		const auto& geom = curve->Geometry();
		try
		{
			auto p = xValue(t, curve).second;
			geom->D1(p, pt, vt);
		}
		catch (const Standard_Failure&)
		{
			FatalErrorIn(FunctionSIG)
				<< "the continuity of the curve is not C1" << endl
				<< abort(FatalError);
		}
		xs.push_back(pt.X());
		ys.push_back(pt.Y());

		try
		{
			gp_Dir2d dir(vt);
			ts.push_back(std::move(dir));
		}
		catch (const Standard_Failure&)
		{
			FatalErrorIn(FunctionSIG)
				<< "the continuity of the curve is not C1" << endl
				<< abort(FatalError);
		}
	}
	auto t = std::make_tuple(std::move(xs), std::move(ys), std::move(ts));
	return std::move(t);
}

std::vector<Standard_Real>
tnbLib::Airfoil_Tools::CalcThicknessPoints
(
	const Geo_xDistb& theDist,
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
	const std::vector<Standard_Real>& theSpans
)
{
	std::vector<Standard_Real> /*xs,*/ ys;
	//xs.reserve(theDist.Size());
	ys.reserve(theDist.Size());

	gp_Pnt2d pt;
	for (auto t : theDist.Values())
	{
		const auto curve = RetrieveCurve(t, theCurves, theSpans);
		const auto& geom = curve->Geometry();
		try
		{
			auto p = xValue(t, curve).second;
			geom->D0(p, pt);
		}
		catch (const Standard_Failure&)
		{
			FatalErrorIn(FunctionSIG)
				<< "the continuity of the curve is not C1" << endl
				<< abort(FatalError);
		}
		//xs.push_back(pt.X());
		ys.push_back(pt.Y());
	}
	//auto t = std::make_tuple(std::move(xs), std::move(ys));
	//return std::move(t);
	return std::move(ys);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Airfoil_Tools::CalcUpperOffsets
(
	const std::vector<Standard_Real>& xc, 
	const std::vector<Standard_Real>& yc,
	const std::vector<Standard_Real>& uYt, 
	const std::vector<Dir2d>& tc
)
{
	std::vector<Pnt2d> pts;
	pts.reserve(xc.size());

	for (size_t i = 0; i < xc.size(); i++)
	{
		auto yt = uYt.at(i);
		auto cost = tc.at(i).X();
		auto sint = tc.at(i).Y();

		auto xu = xc.at(i) - yt * sint;
		auto yu = yc.at(i) + yt * cost;

		Pnt2d pt(xu, yu);
		pts.push_back(std::move(pt));
	}
	return std::move(pts);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Airfoil_Tools::CalcLowerOffsets
(
	const std::vector<Standard_Real>& xc,
	const std::vector<Standard_Real>& yc,
	const std::vector<Standard_Real>& lYt,
	const std::vector<Dir2d>& tc
)
{
	std::vector<Pnt2d> pts;
	pts.reserve(xc.size());

	for (size_t i = 0; i < xc.size(); i++)
	{
		auto yt = lYt.at(i);
		auto cost = tc.at(i).X();
		auto sint = tc.at(i).Y();

		auto xl = xc.at(i) + yt * sint;
		auto yl = yc.at(i) - yt * cost;

		Pnt2d pt(xl, yl);
		pts.push_back(std::move(pt));
	}
	return std::move(pts);
}