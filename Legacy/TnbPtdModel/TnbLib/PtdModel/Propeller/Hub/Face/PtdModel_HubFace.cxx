#include <PtdModel_HubFace.hxx>

tnbLib::PtdModel_HubFace::PtdModel_HubFace(const Handle(Geom_Surface)& theSurface)
	: PtdModel_Face(theSurface)
{}

tnbLib::PtdModel_HubFace::PtdModel_HubFace(Handle(Geom_Surface)&& theSurface)
	: PtdModel_Face(std::move(theSurface))
{}