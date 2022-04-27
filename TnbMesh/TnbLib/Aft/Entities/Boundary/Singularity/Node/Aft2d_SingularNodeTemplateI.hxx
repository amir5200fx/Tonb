#pragma once
template<class BndNodeType>
inline Standard_Boolean 
tnbLib::Aft2d_SingularNodeTemplate<BndNodeType>::IsPole() const
{
	return Standard_False;
}

template<class BndNodeType>
inline Standard_Boolean
tnbLib::Aft2d_SingularNodeTemplate<BndNodeType>::IsLine() const
{
	return Standard_False;
}

template<class BndNodeType>
inline Standard_Boolean 
tnbLib::Aft2d_SingularNodeTemplate<BndNodeType>::IsSingular() const
{
	return Standard_True;
}