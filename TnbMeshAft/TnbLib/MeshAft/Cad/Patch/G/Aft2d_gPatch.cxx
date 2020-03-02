#include <Aft2d_gPatch.hxx>

#include <Aft2d_gPlnRegionSurface.hxx>
#include <GModel_Surface.hxx>

namespace tnbLib
{

	template<>
	std::shared_ptr<Aft2d_gPlnRegionSurface> Aft2d_gPatch::GetPlane() const
	{
		auto This =
			std::dynamic_pointer_cast<Aft2d_gPatch>
			(
				std::const_pointer_cast<GModel_Entity>(this->shared_from_this())
				);
		auto plane = Aft2d_gPlnRegionSurface::MakePlane(This);
		return std::move(plane);
	}
}