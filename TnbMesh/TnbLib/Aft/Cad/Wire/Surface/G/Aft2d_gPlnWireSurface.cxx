#include <Aft2d_gPlnWireSurface.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_ParaWire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
template<>
std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::Aft2d_gPlnWireSurface::MakeOrignWire<tnbLib::GModel_ParaWire>
(
	const std::shared_ptr<Aft2d_gPlnWireSurface>& thePlnWire
	)
{
	Debug_Null_Pointer(thePlnWire);
	const auto& plnCurves = thePlnWire->Curves();

	std::vector<std::shared_ptr<GModel_ParaCurve>> curves;
	curves.reserve(plnCurves.size());
	for (const auto& x : plnCurves)
	{
		Debug_Null_Pointer(x);
		curves.push_back(x->Curve());
	}
	auto wire = std::make_shared<GModel_ParaWire>
		(
			std::make_shared
			<
			std::vector<std::shared_ptr<GModel_ParaCurve>>
			>(std::move(curves))
			);
	return std::move(wire);
}

template<>
tnbLib::Entity2d_Box 
tnbLib::Aft2d_gPlnWireSurface::CalcBoundingBox
(
	const Aft2d_gPlnCurveSurface& theCurve
)
{
	const auto& c = theCurve.Curve();
	Debug_Null_Pointer(c);
	auto b = c->CalcBoundingBox();
	return std::move(b);
}