#include <Aft2d_GlobalDataSurface.hxx>

#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Mesh_QualityMap.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementSurface>)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementSurface>)
{
	ar & theElements_;
}