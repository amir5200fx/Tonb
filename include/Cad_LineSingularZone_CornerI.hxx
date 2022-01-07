#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::LineSingularZone_Corner<SurfPln>::ZoneType() const
{
	return Cad_SingularType::line_corner;
}

template<class SurfPln>
inline Standard_Integer 
tnbLib::cadLib::LineSingularZone_Corner<SurfPln>::NbHorizons() const
{
	return Standard_Integer(2);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::LineSingularZone_Corner<SurfPln>::curveType>
tnbLib::cadLib::LineSingularZone_Corner<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbHorizons() - 1));
	return (&theHorizon0_)[theIndex];
}