#include <Aft2d_tRegionPlaneSurfaceUniMetric.hxx>

#include <Aft2d_tPlnWireSurfaceUniMetric.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>
#include <Cad_tPlnGapCurveUniMetric.hxx>
#include <TModel_ParaWire.hxx>

template<>
template<>
std::shared_ptr<tnbLib::Aft2d_tPlnWireSurfaceUniMetric>
tnbLib::Aft2d_tRegionPlaneSurfaceUniMetric::MakeMeshWire<tnbLib::TModel_ParaWire>
(
	const TModel_ParaWire& theWire
	)
{
	auto curves_ptr =
		std::make_shared<std::vector<std::shared_ptr<Aft2d_tPlnCurveSurfaceUniMetric>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbCurves());

	Standard_Integer K = 0;
	for (const auto& x : theWire.Curves())
	{
		Debug_Null_Pointer(x);
		if (x->IsGap())
		{
			auto curve = std::make_shared<Cad_tPlnGapCurveUniMetric>(x);
			curves.push_back(std::move(curve));
		}
		else
		{
			auto curve = std::make_shared<Aft2d_tPlnCurveSurfaceUniMetric>(x);
			curves.push_back(std::move(curve));
		}
	}
	auto wire =
		std::make_shared<Aft2d_tPlnWireSurfaceUniMetric>(std::move(curves));

	return std::move(wire);
}