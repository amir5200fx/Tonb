#include <Aft2d_tRegionPlaneSurface.hxx>

#include <Aft2d_tPlnWireSurface.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Cad_tPoleSingularCurve.hxx>
#include <Cad_tPlnGapCurve.hxx>
#include <TModel_ParaWire.hxx>
#include <TModel_Plane.hxx>

template<>
template<>
std::shared_ptr<tnbLib::Aft2d_tPlnWireSurface>
tnbLib::Aft2d_tRegionPlaneSurface::MakeMeshWire<tnbLib::TModel_ParaWire>
(
	const TModel_ParaWire& theWire
	)
{
	auto curves_ptr =
		std::make_shared<std::vector<std::shared_ptr<Aft2d_tPlnCurveSurface>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbCurves());

	Standard_Integer K = 0;
	for (const auto& x : theWire.Curves())
	{
		Debug_Null_Pointer(x);
		if (x->IsGap())
		{
			auto curve = std::make_shared<Cad_tPlnGapCurve>(x);
			curves.push_back(std::move(curve));
		}
		else if (x->IsDegenerated())
		{
			auto curve = std::make_shared<Cad_tPoleSingularCurve>(x);
			curves.push_back(std::move(curve));
		}
		else
		{
			auto curve = std::make_shared<Aft2d_tPlnCurveSurface>(x);
			curves.push_back(std::move(curve));
		}
	}
	auto wire =
		std::make_shared<Aft2d_tPlnWireSurface>(std::move(curves));

	return std::move(wire);
}

template<>
template<>
std::shared_ptr<tnbLib::TModel_Plane>
tnbLib::Aft2d_tRegionPlaneSurface::MakeOrignPlane
(
	const std::shared_ptr<Aft2d_tRegionPlaneSurface>& thePlnRegion
)
{
	Debug_Null_Pointer(thePlnRegion);
	Debug_Null_Pointer(thePlnRegion->Outer());
	auto outer =
		Aft2d_tPlnWireSurface::MakeOrignWire<TModel_ParaWire>
		(
			thePlnRegion->Outer()
			);

	std::shared_ptr<std::vector<std::shared_ptr<TModel_ParaWire>>> inners;
	if (thePlnRegion->HasHole())
	{
		inners = std::make_shared<std::vector<std::shared_ptr<TModel_ParaWire>>>();
		Debug_Null_Pointer(thePlnRegion->Inner());
		for (const auto& x : *thePlnRegion->Inner())
		{
			Debug_Null_Pointer(x);
			auto inner =
				Aft2d_tPlnWireSurface::MakeOrignWire<TModel_ParaWire>(x);
			inners->push_back(std::move(inner));
		}
	}
	auto pln = std::make_shared<TModel_Plane>(std::move(outer), std::move(inners));
	return std::move(pln);
}