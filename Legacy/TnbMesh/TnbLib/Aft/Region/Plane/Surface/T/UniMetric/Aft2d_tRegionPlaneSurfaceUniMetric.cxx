#include <Aft2d_tRegionPlaneSurfaceUniMetric.hxx>

#include <Aft2d_tPlnWireSurfaceUniMetric.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetric.hxx>
#include <Cad_tPlnGapCurveUniMetric.hxx>
#include <TModel_ParaWire.hxx>
#include <TModel_Plane.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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

template<>
std::shared_ptr<tnbLib::Aft2d_tRegionPlaneSurfaceUniMetric>
tnbLib::Aft2d_tRegionPlaneSurfaceUniMetric::MakePlane
(
	const std::shared_ptr<TModel_Plane>& thePlane
)
{
	Debug_Null_Pointer(thePlane);
	if (NOT thePlane->OuterWire())
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid surface : has no outer wire" << endl
			<< abort(FatalError);
	}

	const auto& Outer = *thePlane->OuterWire();
	const auto& Inners = *thePlane->InnerWires();
	//std::cout << "NB OF CURVES: " << Outer.NbCurves() << std::endl;
	auto outer_wire =
		MakeMeshWire(Outer);

	std::shared_ptr<std::vector<std::shared_ptr<Aft2d_tPlnWireSurfaceUniMetric>>>
		inner_wires;
	if (thePlane->InnerWires())
	{
		inner_wires =
			std::make_shared<std::vector<std::shared_ptr<Aft2d_tPlnWireSurfaceUniMetric>>>();
		inner_wires->reserve(Inners.size());

		for (const auto& x : Inners)
		{
			Debug_Null_Pointer(x);

			auto wire = MakeMeshWire(*x);
			inner_wires->push_back(wire);
		}
	}

	auto plane =
		std::make_shared<Aft2d_tRegionPlaneSurfaceUniMetric>
		(
			thePlane, outer_wire,
			inner_wires);
	return std::move(plane);
}