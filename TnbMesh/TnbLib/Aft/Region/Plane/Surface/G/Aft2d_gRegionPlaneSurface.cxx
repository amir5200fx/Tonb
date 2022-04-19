#include <Aft2d_gRegionPlaneSurface.hxx>

#include <Aft2d_gPlnWireSurface.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <GModel_ParaWire.hxx>
#include <GModel_Plane.hxx>

template<>
template<>
std::shared_ptr<tnbLib::Aft2d_gPlnWireSurface> 
tnbLib::Aft2d_gRegionPlaneSurface::MakeMeshWire<tnbLib::GModel_ParaWire>
(
	const GModel_ParaWire& theWire
	)
{
	auto curves_ptr = 
		std::make_shared<std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>>();
	auto& curves = *curves_ptr;
	curves.reserve(theWire.NbCurves());

	Standard_Integer K = 0;
	for (const auto& x : theWire.Curves())
	{
		Debug_Null_Pointer(x);
		curves.push_back(std::make_shared<Aft2d_gPlnCurveSurface>(x));
	}
	auto wire =
		std::make_shared<Aft2d_gPlnWireSurface>(std::move(curves));

	return std::move(wire);
}

template<>
template<>
std::shared_ptr<tnbLib::GModel_Plane> 
tnbLib::Aft2d_gRegionPlaneSurface::MakeOrignPlane
(
	const std::shared_ptr<Aft2d_gRegionPlaneSurface>& thePlnRegion
)
{
	Debug_Null_Pointer(thePlnRegion);
	Debug_Null_Pointer(thePlnRegion->Outer());
	auto x = thePlnRegion->Outer();

	auto outer =
		Aft2d_gPlnWireSurface::MakeOrignWire<GModel_ParaWire>
		(
			thePlnRegion->Outer()
			);

	std::shared_ptr<std::vector<std::shared_ptr<GModel_ParaWire>>> inners;
	if (thePlnRegion->HasHole())
	{
		Debug_Null_Pointer(thePlnRegion->Inner());
		for (const auto& x : *thePlnRegion->Inner())
		{
			Debug_Null_Pointer(x);
			auto inner = 
				Aft2d_gPlnWireSurface::MakeOrignWire<GModel_ParaWire>(x);
			inners->push_back(std::move(inner));
		}
	}
	auto pln = std::make_shared<GModel_Plane>(std::move(outer), std::move(inners));
	return std::move(pln);
}