#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::PoleSingularZone_WholeSide<SurfPln>::ZoneType() const
{
	return Cad_SingularType::pole_whole_side;
}

template<class SurfPln>
inline Standard_Integer 
tnbLib::cadLib::PoleSingularZone_WholeSide<SurfPln>::NbHorizons() const
{
	return Standard_Integer(1);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::PoleSingularZone_WholeSide<SurfPln>::curveType>
tnbLib::cadLib::PoleSingularZone_WholeSide<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	return theHorizon_;
}