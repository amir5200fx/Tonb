#include <Airfoil_Naca.hxx>

#include <Airfoil_NacaMidline.hxx>
#include <Airfoil_NacaThickness.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_xDistb.hxx>
#include <Pnt2d.hxx>
#include <Vec2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

#include <cmath>

const tnbLib::word tnbLib::Airfoil_Naca::ioData::extension = ".nacapts";

std::vector<Standard_Real> 
tnbLib::Airfoil_Naca::CalcCamber
(
	const std::vector<Standard_Real>& theXc
) const
{
	std::vector<Standard_Real> vc;
	vc.reserve(theXc.size());
	for (auto x : theXc)
	{
		if (x <= gp::Resolution())
		{
			vc.push_back(0.0);
			continue;
		}
		if (std::abs(1.0 - x) <= gp::Resolution())
		{
			vc.push_back(0.0);
			continue;
		}
		auto y = MidLine()->CalcY(x);
		vc.push_back(y);
	}
	return std::move(vc);
}

std::vector<Standard_Real> 
tnbLib::Airfoil_Naca::CalcThickness
(
	const std::vector<Standard_Real>& theXc
) const
{
	std::vector<Standard_Real> vc;
	vc.reserve(theXc.size());
	for (auto x : theXc)
	{
		auto yt = Thickness()->CalcYt(x);
		vc.push_back(yt);
	}
	return std::move(vc);
}

std::pair<std::vector<Standard_Real>, Handle(Geom2d_Curve)>
tnbLib::Airfoil_Naca::CalcTangents
(
	const std::vector<Standard_Real>& theXc,
	const std::vector<Standard_Real>& theYc
) const
{
	std::vector<Pnt2d> Qs;
	Qs.reserve(theXc.size());
	for (size_t i = 0; i < theXc.size(); i++)
	{
		auto x = theXc.at(i);
		auto y = theYc.at(i);

		Pnt2d pt(x, y);
		Qs.push_back(std::move(pt));
	}
	auto curve = Pln_CurveTools::Interpolation(Qs);
	std::vector<Standard_Real> xs;
	xs.reserve(theXc.size());
	gp_Dir2d dir(0, 1);
	gp_Vec2d ax(1, 0);
	for (auto x : theXc)
	{
		Handle(Geom2d_Line) lx = new Geom2d_Line(Pnt2d(x, 0), dir);
		Geom2dAPI_InterCurveCurve alg(lx, curve);

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been occurred." << endl
				<< abort(FatalError);
		}
		auto p = alg.Intersector().Point(1).ParamOnSecond();

		gp_Pnt2d pt;
		gp_Vec2d vec;
		curve->D1(p, pt, vec);

		auto theta = ax.Angle(vec);

		xs.push_back(theta);
	}
	auto t = std::make_pair(std::move(xs), std::move(curve));
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real>
tnbLib::Airfoil_Naca::CalcTangent
(
	const Standard_Real x, 
	const Handle(Geom2d_Curve)& theCurve
)
{
	static gp_Dir2d dir(0, 1);
	static gp_Vec2d ax(1, 0);

	Handle(Geom2d_Line) lx = new Geom2d_Line(Pnt2d(x, 0), dir);
	Geom2dAPI_InterCurveCurve alg(lx, theCurve);

	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been occurred." << endl
			<< abort(FatalError);
	}
	auto p = alg.Intersector().Point(1).ParamOnSecond();

	gp_Pnt2d pt;
	gp_Vec2d vec;
	theCurve->D1(p, pt, vec);

	auto theta = ax.Angle(vec);
	auto t = std::make_pair(theta, pt.Y());
	return std::move(t);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::Airfoil_Naca::CalcThicknessOffsets
(
	const std::vector<Standard_Real>& theXc, 
	const std::vector<Standard_Real>& theYt
) const
{
	std::vector<Pnt2d> pts;
	pts.reserve(theXc.size());
	for (size_t i = 0; i < theXc.size(); i++)
	{
		Pnt2d p(theXc.at(i)*Chord(), theYt.at(i)*MaxThickness());
		pts.push_back(std::move(p));
	}
	return std::move(pts);
}

std::tuple<tnbLib::Pnt2d, Standard_Real, Standard_Real>
tnbLib::Airfoil_Naca::CalcRadius
(
	const std::vector<Pnt2d>& theCoords
) const
{
	auto curve = Pln_CurveTools::Interpolation(theCoords);

	const auto tx = Trim()*Chord();
	std::cout << "xt= " << tx << std::endl;
	// Finding the normal on the trimmed location [11/19/2022 Amir]
	gp_Dir2d dir(0, 1);
	Handle(Geom2d_Line) lx = new Geom2d_Line(Pnt2d(tx, 0), dir);

	Geom2dAPI_InterCurveCurve alg(lx, curve);

	if (alg.NbPoints() NOT_EQUAL 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been occurred." << endl
			<< abort(FatalError);
	}

	auto p = alg.Intersector().Point(1).ParamOnSecond();

	Pnt2d pt;
	Vec2d v1;

	// calculating the normal on the trimmed location [11/19/2022 Amir]
	curve->D1(p, pt, v1);

	v1.Rotate(PI*0.5);

	const auto m = std::atan(v1.Y() / v1.X());
	const auto ot = pt.X() + pt.Y() / std::abs(m);
	std::cout << "ot = " << ot << std::endl;
	const auto radius = Pnt2d(ot, 0).Distance(pt);

	auto paired = std::make_tuple(std::move(pt), ot, radius);
	return std::move(paired);
}

std::vector<Standard_Real> 
tnbLib::Airfoil_Naca::CalcXs() const
{
	std::vector<Standard_Real> xs;
	xs.reserve(Xc()->Size() + 2);
	xs.push_back(0.0);
	for (auto x : Xc()->Values())
	{
		xs.push_back(x);
	}
	xs.push_back(1.0);
	return std::move(xs);
}

void tnbLib::Airfoil_Naca::Perform()
{
	if (NOT MidLine())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mid line profile has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Thickness())
	{
		FatalErrorIn(FunctionSIG)
			<< "no thickness profile has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Xc())
	{
		FatalErrorIn(FunctionSIG)
			<< "no x distribution profile has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Chord())
	{
		FatalErrorIn(FunctionSIG)
			<< "no chord length has been assigned." << endl
			<< abort(FatalError);
	}

	auto xc = CalcXs();

	const auto yc = CalcCamber(xc);
	const auto yt = CalcThickness(xc);
	auto[ypc, tanCurve] = CalcTangents(xc, yc);

	const auto chord = Chord();

	auto& upper = UpperRef();
	auto& lower = LowerRef();

	Standard_Real xt = 0;
	if (ApplyTrim())
	{
		const auto thickOffsets = CalcThicknessOffsets(xc, yt);
		const auto[p1, Ox, radius] = CalcRadius(thickOffsets);

		xt = p1.X();
		static const Standard_Integer nbTrims = 5;
		const auto nbSegs = nbTrims - 1;
		const auto x0 = Ox - radius;
		const auto du = (xt - x0) / (Standard_Real)(nbSegs);

		for (size_t i = 0; i <= nbSegs; i++)
		{
			auto x = x0 + i * du;
			auto dx = x - Ox;
			auto yt = std::sqrt(radius*radius - dx * dx);

			auto[angl, yc] = CalcTangent(x, tanCurve);
			const auto cs = cos(angl);
			const auto sn = sin(angl);

			const auto xu = x - yt*sn;
			const auto yu = yc + yt*cs;

			auto Pu = Pnt2d(xu, yu);

			const auto xl = x + yt*sn;
			const auto yl = yc - yt*cs;

			auto Pl = Pnt2d(xl, yl);

			upper.push_back(std::move(Pu));
			lower.push_back(std::move(Pl));
		}
	}

	for (size_t i = 0; i < xc.size(); i++)
	{
		if (ApplyTrim() AND xc.at(i)*Chord() <= xt)
		{
			continue;
		}

		const auto angl = ypc.at(i);
		const auto cs = cos(angl);
		const auto sn = sin(angl);

		const auto xu = xc.at(i)*Chord() - yt.at(i)*sn*MaxThickness();
		const auto yu = yc.at(i) + yt.at(i)*cs*MaxThickness();

		const auto xl = xc.at(i)*Chord() + yt.at(i)*sn*MaxThickness();
		const auto yl = yc.at(i) - yt.at(i)*cs*MaxThickness();

		auto Pu = Pnt2d(xu, yu);
		auto Pl = Pnt2d(xl, yl);

		upper.push_back(std::move(Pu));
		lower.push_back(std::move(Pl));
	}

	Change_IsDone() = Standard_True;
}