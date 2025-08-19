#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class SurfPln>
inline tnbLib::Cad_SingularType 
tnbLib::cadLib::PoleSingularZone_Corner<SurfPln>::ZoneType() const
{
	return Cad_SingularType::pole_corner;
}

template<class SurfPln>
inline tnbLib::word 
tnbLib::cadLib::PoleSingularZone_Corner<SurfPln>::ZoneTypeName() const
{
	return PoleSingularZone_Corner::typeName;
}

template<class SurfPln>
inline Standard_Integer 
tnbLib::cadLib::PoleSingularZone_Corner<SurfPln>::NbHorizons() const
{
	return Standard_Integer(1);
}

template<class SurfPln>
inline std::shared_ptr<typename tnbLib::cadLib::PoleSingularZone_Corner<SurfPln>::curveType>
tnbLib::cadLib::PoleSingularZone_Corner<SurfPln>::Horizon(const Standard_Integer theIndex) const
{
	return theHorizon_;
}