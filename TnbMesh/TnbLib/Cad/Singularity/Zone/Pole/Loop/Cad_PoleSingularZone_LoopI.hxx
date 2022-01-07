#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::PoleSingularZone_Loop<SurfPln>::ZoneType() const
{
	return Cad_SingularType::pole_loop;
}

template<class SurfPln>
inline Standard_Integer 
tnbLib::cadLib::PoleSingularZone_Loop<SurfPln>::NbHorizons() const
{
	return Standard_Integer(4);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::PoleSingularZone_Loop<SurfPln>::curveType>
tnbLib::cadLib::PoleSingularZone_Loop<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbHorizons() - 1));
	return (&theHorizon0_)[theIndex];
}