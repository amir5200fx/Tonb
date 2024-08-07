#pragma once
#include <Pnt2d.hxx>
inline Standard_Boolean 
tnbLib::Cad_ParaCurve::IsGap() const
{
	return Standard_False;
}

inline Standard_Boolean 
tnbLib::Cad_ParaCurve::IsDegenerated() const
{
	return Standard_False;
}

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