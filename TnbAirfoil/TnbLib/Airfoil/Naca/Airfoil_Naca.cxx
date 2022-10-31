#include <Airfoil_Naca.hxx>

#include <Airfoil_NacaMidline.hxx>
#include <Airfoil_NacaThickness.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_xDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Lin2d.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

#include <cmath>

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

std::vector<Standard_Real> 
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
	gp_Vec2d hor(1, 0);
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

		auto theta = vec.Angle(hor);
		xs.push_back(theta);
	}
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

	const auto& xc = Xc()->Values();

	const auto yc = CalcCamber(xc);
	const auto yt = CalcThickness(xc);
	const auto ypc = CalcTangents(xc, yc);

	const auto chord = Chord();

	auto& upper = UpperRef();
	auto& lower = LowerRef();

	for (size_t i = 0; i < xc.size(); i++)
	{
		const auto angl = std::atan(ypc.at(i));
		const auto cs = cos(angl);
		const auto sn = sin(angl);

		const auto xu = xc.at(i) - yt.at(i)*sn;
		const auto yu = yc.at(i) + yt.at(i)*cs;

		const auto xl = xc.at(i) + yt.at(i)*sn;
		const auto yl = yc.at(i) - yt.at(i)*cs;

		auto Pu = Pnt2d(xu*chord, yu*chord);
		auto Pl = Pnt2d(xl*chord, yl*chord);

		upper.push_back(std::move(Pu));
		lower.push_back(std::move(Pl));
	}

	Change_IsDone() = Standard_True;
}