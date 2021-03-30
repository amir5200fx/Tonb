#include <Cad3d_TModelManager.hxx>

#include <TModel_Paired.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad3d_TModelManager)
{
	ar & theSurfaces_;
	ar & theEdges_;
	ar & theVertices_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad3d_TModelManager)
{
	ar & theSurfaces_;
	ar & theEdges_;
	ar & theVertices_;
}