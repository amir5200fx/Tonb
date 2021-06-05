#pragma once
inline tnbLib::PtdModel_BladeFace::PtdModel_BladeFace()
{
	//- empty body
}

inline tnbLib::PtdModel_BladeFace::PtdModel_BladeFace
(
	const Handle(Geom_Surface)& theSurface
)
	: theSurface_(theSurface)
{
	//- empty body
}

inline tnbLib::PtdModel_BladeFace::PtdModel_BladeFace
(
	Handle(Geom_Surface) && theSurface
)
	: theSurface_(std::move(theSurface))
{
	//- empty body
}

inline void tnbLib::PtdModel_BladeFace::SetSurface(const Handle(Geom_Surface)& s)
{
	theSurface_ = s;
}

inline void tnbLib::PtdModel_BladeFace::SetSurface(Handle(Geom_Surface) && s)
{
	theSurface_ = std::move(s);
}