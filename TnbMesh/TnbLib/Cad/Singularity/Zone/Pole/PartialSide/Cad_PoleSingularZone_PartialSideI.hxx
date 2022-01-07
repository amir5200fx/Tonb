#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::PoleSingularZone_PartialSide<SurfPln>::ZoneType() const
{
	return Cad_SingularType::pole_partial_side;
}

template<class SurfPln>
inline Standard_Integer
tnbLib::cadLib::PoleSingularZone_PartialSide<SurfPln>::NbHorizons() const
{
	return Standard_Integer(1);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::PoleSingularZone_PartialSide<SurfPln>::curveType>
tnbLib::cadLib::PoleSingularZone_PartialSide<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	return theHorizon_;
}