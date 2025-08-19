#include <Cad_gApprxPlnWireSurface.hxx>

#include <Aft2d_gPlnWireSurface.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gPlnCurveSurface>>
tnbLib::Cad_gApprxPlnWireSurface::RetrieveCurves
(
	const Aft2d_gPlnWireSurface& theWire
)
{
	auto curves = theWire.Curves();
	return std::move(curves);
}