#include <Cad2d_QuadraticArc.hxx>

#include <Vec2d.hxx>
#include <Geo_Tools.hxx>

#include <Geom2d_BSplineCurve.hxx>

void tnbLib::Cad2d_QuadraticArc::Perform()
{
	if (Dir0().IsParallel(Dir2(), Tolerance()))
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data have been detected: the two directions are in parallel" << endl
			<< abort(FatalError);
	}

	const auto v02 = Vec2d(P0(), P2());

	const auto p1 = Geo_Tools::IntersectionTwoLines(P0(), Dir0(), P2(), Dir2(), 0.001*Tolerance());
	const auto v1p = Vec2d(p1, PtOnCrv());

	Standard_Real alf0, alf2;
	Geo_Tools::IntersectTwoLines(p1, v1p, P0(), v02, alf0, alf2, 0.001*Tolerance());

	const auto a = (Standard_Real)std::sqrt(alf2 / (1.0 - alf2));
	const auto u = a / (1.0 + a);

	const auto num = 
		(1.0 - u)*(1.0 - u)*DotProduct(PtOnCrv() - P0(), p1 - PtOnCrv()) 
		+ u * u*DotProduct(PtOnCrv() - P2(), p1 - PtOnCrv());

	const auto den = 2.0*u*(1.0 - u)*DotProduct(p1 - PtOnCrv(), p1 - PtOnCrv());
	if (std::abs(den) <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "divided by zero has been detected!" << endl
			<< abort(FatalError);
	}
	const auto w1 = num / den;

	TColgp_Array1OfPnt2d poles(1, 3);
	poles.SetValue(1, P0());
	poles.SetValue(2, p1);
	poles.SetValue(3, P2());

	TColStd_Array1OfReal weights(1, 3);
	weights.SetValue(1, 1.0);
	weights.SetValue(2, w1);
	weights.SetValue(3, 1.0);

	TColStd_Array1OfReal knots(1, 2);
	knots.SetValue(1, 0.0);
	knots.SetValue(2, 1.0);

	TColStd_Array1OfInteger mults(1, 2);
	mults.SetValue(1, 3);
	mults.SetValue(2, 3);

	static const Standard_Integer deg = 2;

	try
	{
		theGeom_ = new Geom2d_BSplineCurve(poles, weights, knots, mults, deg);
	}
	catch (const Standard_Failure& x)
	{
		Info << x.GetMessageString() << endl
			<< abort(FatalError);
	}

	Change_IsDone() = Standard_True;
}