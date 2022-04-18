#include <Aft2d_tPlnWireSurface.hxx>

#include <Aft2d_tPlnCurveSurface.hxx>
#include <TModel_ParaCurve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
tnbLib::Entity2d_Box
tnbLib::Aft2d_tPlnWireSurface::CalcBoundingBox
(
	const Aft2d_tPlnCurveSurface& theCurve
)
{
	const auto& c = theCurve.Curve();
	Debug_Null_Pointer(c);
	auto b = c->CalcBoundingBox();
	return std::move(b);
}