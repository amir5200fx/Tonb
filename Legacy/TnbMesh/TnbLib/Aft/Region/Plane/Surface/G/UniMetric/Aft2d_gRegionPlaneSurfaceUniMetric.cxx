#include <Aft2d_gRegionPlaneSurfaceUniMetric.hxx>

#include <Aft2d_gPlnWireSurfaceUniMetric.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Cad_gPlnGapCurveUniMetric.hxx>
#include <GModel_ParaWire.hxx>

template<>
template<>
std::shared_ptr<tnbLib::Aft2d_gPlnWireSurfaceUniMetric>
tnbLib::Aft2d_gRegionPlaneSurfaceUniMetric::MakeMeshWire<tnbLib::GModel_ParaWire>
(
	const GModel_ParaWire& theWire
	)
{
	auto curves_ptr =
		std::make_shared<std::vector<std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbCurves());

	Standard_Integer K = 0;
	for (const auto& x : theWire.Curves())
	{
		Debug_Null_Pointer(x);
		if (x->IsGap())
		{
			auto curve = std::make_shared<Cad_gPlnGapCurveUniMetric>(x);
			curves.push_back(std::move(curve));
		}
		else
		{
			auto curve = std::make_shared<Aft2d_gPlnCurveSurfaceUniMetric>(x);
			curves.push_back(std::move(curve));
		}
	}
	auto wire =
		std::make_shared<Aft2d_gPlnWireSurfaceUniMetric>(std::move(curves));

	return std::move(wire);
}