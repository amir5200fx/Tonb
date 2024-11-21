#include <Cad_SubdivideHorizonTools.hxx>

#include <Pnt2d.hxx>
#include <Pln_Tools.hxx>

#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/Geom2dAPI_InterCurveCurve.hxx>

std::pair<Standard_Real, Standard_Real> 
tnbLib::Cad_SubdivideHorizonTools::RetrieveParams
(
	const Handle(Geom2d_Curve)& theGeom
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theGeom))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	auto t = std::make_pair(theGeom->FirstParameter(), theGeom->LastParameter());
	return std::move(t);
}

tnbLib::Cad_SubdivideHorizonTools::Params 
tnbLib::Cad_SubdivideHorizonTools::MakePair
(
	const Standard_Real x0,
	const Standard_Real x1
)
{
	auto paired = Params{ x0,x1 };
	return std::move(paired);
}

std::pair<std::vector<Standard_Real>, std::vector<Standard_Real>>
tnbLib::Cad_SubdivideHorizonTools::RetrieveParams
(
	const std::vector<Params>& thePars
)
{
	std::vector<Standard_Real> xs0, xs1;
	xs0.reserve(thePars.size());
	xs1.reserve(thePars.size());
	for (const auto& x : thePars)
	{
		xs0.push_back(x.ParOnC0);
		xs1.push_back(x.ParOnC1);
	}
	auto t = std::make_pair(std::move(xs0), std::move(xs1));
	return std::move(t);
}

std::pair<std::vector<tnbLib::Cad_SubdivideHorizonTools::Params>, Standard_Boolean>
tnbLib::Cad_SubdivideHorizonTools::CalcIntersections
(
	const Handle(Geom2d_Curve)& theC0, 
	const Handle(Geom2d_Curve)& theC1
)
{
#ifdef _DEBUG
	if (NOT Pln_Tools::IsBounded(theC0))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve, c0, is not bounded!" << endl
			<< abort(FatalError);
	}

	if (NOT Pln_Tools::IsBounded(theC1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve, c1, is not bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Geom2dAPI_InterCurveCurve alg;
	alg.Init(theC0, theC1);

	std::vector<Params> pars;
	if (alg.NbSegments())
	{
		for (Standard_Integer i = 1; i <= alg.NbSegments(); i++)
		{
			Handle(Geom2d_Curve) sub0, sub1;
			alg.Segment(i, sub0, sub1);

			{
				auto[p0, p1] = RetrieveParams(sub0);
				auto pars0 = MakePair(p0, p1);
				pars.push_back(std::move(pars0));
			}

			{
				auto[p0, p1] = RetrieveParams(sub1);
				auto pars0 = MakePair(p0, p1);
				pars.push_back(std::move(pars0));
			}
		}
	}

	if (alg.NbPoints())
	{
		for (Standard_Integer i = 1; i <= alg.NbPoints(); i++)
		{
			auto p0 = alg.Intersector().Point(i).ParamOnFirst();
			auto p1 = alg.Intersector().Point(i).ParamOnSecond();

			auto paired = MakePair(p0, p1);
			pars.push_back(std::move(paired));
		}
	}

	if (pars.size())
	{
		auto t = std::make_pair(std::move(pars), Standard_True);
		return std::move(t);
	}
	else
	{
		auto t = std::make_pair(std::move(pars), Standard_False);
		return std::move(t);
	}
}