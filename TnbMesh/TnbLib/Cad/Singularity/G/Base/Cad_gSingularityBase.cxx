#include <Cad_gSingularityBase.hxx>

#include <Cad_gPoleSingularCurve.hxx>
#include <Cad_gLineSingularCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
tnbLib::Cad_gSingularityBase::ParametricCurve_Pole
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1
)
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	Debug_Null_Pointer(geom);

	auto plnCurve = std::make_shared<GModel_ParaCurve>(std::move(geom));
	Debug_Null_Pointer(plnCurve);

	auto Pm = MEAN(theP0, theP1);
	auto curve = std::make_shared<Cad_gPoleSingularCurve>(std::move(plnCurve), std::move(Pm));
	return std::move(curve);
}

template<>
std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>
tnbLib::Cad_gSingularityBase::ParametricCurve_Line
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
)
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	Debug_Null_Pointer(geom);

	auto plnCurve = std::make_shared<GModel_ParaCurve>(std::move(geom));
	Debug_Null_Pointer(plnCurve);

	auto curve = std::make_shared<Cad_gLineSingularCurve>(std::move(plnCurve));
	return std::move(curve);
}