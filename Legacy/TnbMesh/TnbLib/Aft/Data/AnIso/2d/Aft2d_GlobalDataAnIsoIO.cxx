#include <Aft2d_GlobalDataAnIso.hxx>

#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Mesh_QualityMap.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementAnIso>)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_ElementAnIso>)
{
	ar & theElements_;
}