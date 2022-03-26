#include <Aft2d_gRegionPlaneSurface.hxx>

#include <Aft2d_gPlnWireSurface.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <GModel_ParaWire.hxx>

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