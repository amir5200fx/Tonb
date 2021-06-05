#pragma once
inline tnbLib::PtdModel_BladeProfiles::PtdModel_BladeProfiles
(
	const Standard_Integer theIndex,
	const word & theName
)
	: PtdModel_PropEntity(theIndex, theName)
{
	//- empty body
}

inline Standard_Integer tnbLib::PtdModel_BladeProfiles::NbProfiles() const
{
	return (Standard_Integer)theProfiles_.size();
}