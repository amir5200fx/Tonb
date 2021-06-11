#pragma once
inline tnbLib::PtdModel_Face::PtdModel_Face()
{
	//- empty body
}

inline tnbLib::PtdModel_Face::PtdModel_Face
(
	const Handle(Geom_Surface)& theSurface
)
	: theSurface_(theSurface)
{
	//- empty body
}

inline tnbLib::PtdModel_Face::PtdModel_Face
(
	Handle(Geom_Surface) && theSurface
)
	: theSurface_(std::move(theSurface))
{
	//- empty body
}

inline void tnbLib::PtdModel_Face::SetSurface(const Handle(Geom_Surface)& s)
{
	theSurface_ = s;
}

inline void tnbLib::PtdModel_Face::SetSurface(Handle(Geom_Surface) && s)
{
	theSurface_ = std::move(s);
}