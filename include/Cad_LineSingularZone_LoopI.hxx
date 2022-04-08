#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>

template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::LineSingularZone_Loop<SurfPln>::ZoneType() const
{
	return Cad_SingularType::line_loop;
}

template<class SurfPln>
inline tnbLib::word 
tnbLib::cadLib::LineSingularZone_Loop<SurfPln>::ZoneTypeName() const
{
	return LineSingularZone_LoopBase::typeName;
}

template<class SurfPln>
inline Standard_Integer 
tnbLib::cadLib::LineSingularZone_Loop<SurfPln>::NbHorizons() const
{
	return Standard_Integer(4);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::LineSingularZone_Loop<SurfPln>::curveType>
tnbLib::cadLib::LineSingularZone_Loop<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	Debug_If_Condition(NOT INSIDE(theIndex, 0, NbHorizons() - 1));
	return (&theHorizon0_)[theIndex];
}