#include <Aft2d_tPatch.hxx>

#include <Aft2d_tPlnRegionSurface.hxx>
#include <TModel_Surface.hxx>

namespace tnbLib
{

	template<>
	std::shared_ptr<Aft2d_tPlnRegionSurface> Aft2d_tPatch::GetPlane() const
	{
		auto This =
			std::dynamic_pointer_cast<Aft2d_tPatch>
			(
				std::const_pointer_cast<TModel_Entity>(this->shared_from_this())
				);
		auto plane = Aft2d_tPlnRegionSurface::MakePlane(This);
		return std::move(plane);
	}
}