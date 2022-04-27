#pragma once
template<class BndEdgeType>
inline Standard_Boolean 
tnbLib::Aft2d_PoleEdgeTemplate<BndEdgeType>::IsPoleSingular() const
{
	return Standard_True;
}