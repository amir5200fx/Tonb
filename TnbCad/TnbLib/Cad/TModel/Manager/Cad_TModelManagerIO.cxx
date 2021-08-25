#include <Cad_TModelManager.hxx>

#include <TModel_Paired.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_TModelManager)
{
	ar & theSurfaces_;
	ar & theEdges_;
	ar & theVertices_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_TModelManager)
{
	ar & theSurfaces_;
	ar & theEdges_;
	ar & theVertices_;
}