#include <PtdModel_BladeFace.hxx>

tnbLib::PtdModel_BladeFace::PtdModel_BladeFace(const Handle(Geom_Surface)& theGeometry)
	: PtdModel_Face(theGeometry)
{}

tnbLib::PtdModel_BladeFace::PtdModel_BladeFace(Handle(Geom_Surface)&& theGeometry)
	: PtdModel_Face(std::move(theGeometry))
{}