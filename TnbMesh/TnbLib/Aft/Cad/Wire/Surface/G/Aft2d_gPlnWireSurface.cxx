#include <Aft2d_gPlnWireSurface.hxx>

#include <Aft2d_gPlnCurveSurface.hxx>
#include <GModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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