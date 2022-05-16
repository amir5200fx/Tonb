#pragma once
#include <Pnt2d.hxx>
inline tnbLib::Pnt2d 
tnbLib::Cad_ParaCurve::FirstCoord() const
{
	auto p = Value(FirstParameter());
	return std::move(p);
}

inline tnbLib::Pnt2d 
tnbLib::Cad_ParaCurve::LastCoord() const
{
	auto p = Value(LastParameter());
	return std::move(p);
}