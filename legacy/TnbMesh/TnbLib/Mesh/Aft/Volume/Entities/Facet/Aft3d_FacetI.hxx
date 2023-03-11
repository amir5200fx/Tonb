#pragma once

inline
void tnbLib::legLib::Aft3d_Facet::SetIsCavity(const Standard_Boolean isIt)
{
	isCavity_ = isIt;
}

inline 
void tnbLib::legLib::Aft3d_Facet::SetAsNotCavity()
{
	SetIsCavity(Standard_False);
}

inline
void tnbLib::legLib::Aft3d_Facet::SetAsCavity()
{
	SetIsCavity(Standard_True);
}