#pragma once
template<class CurveType>
inline Standard_Boolean 
tnbLib::Cad_LineSingularCurve<CurveType>::HasSubcurves() const
{
	return (Standard_Boolean)ProjPars().size();
}