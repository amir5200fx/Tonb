#include <Cad_gSingularityBase.hxx>

#include <Cad_PoleSingularCurve.hxx>
#include <Cad_LineSingularCurve.hxx>
#include <GModel_ParaCurve.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::shared_ptr<tnbLib::GModel_ParaCurve> 
tnbLib::Cad_gSingularityBase::ParametricCurve_Pole
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1
)
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	Debug_Null_Pointer(geom);

	auto Pm = MEAN(theP0, theP1);
	auto curve = std::make_shared<Cad_PoleSingularCurve<GModel_ParaCurve>>(std::move(geom), std::move(Pm));
	return std::move(curve);
}

template<>
std::shared_ptr<tnbLib::GModel_ParaCurve>
tnbLib::Cad_gSingularityBase::ParametricCurve_Line
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
)
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	Debug_Null_Pointer(geom);

	auto curve = std::make_shared<Cad_LineSingularCurve<GModel_ParaCurve>>(std::move(geom));
	return std::move(curve);
}