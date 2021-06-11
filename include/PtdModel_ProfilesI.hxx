#pragma once
inline tnbLib::PtdModel_Profiles::PtdModel_Profiles
(
	const Standard_Integer theIndex,
	const word & theName
)
	: PtdModel_Entity(theIndex, theName)
{
	//- empty body
}

inline Standard_Integer tnbLib::PtdModel_Profiles::NbProfiles() const
{
	return (Standard_Integer)theProfiles_.size();
}