#include <Aft2d_GlobalData.hxx>

#include <Aft2d_Node.hxx>
#include <Aft2d_Element.hxx>
#include <Mesh_QualityMap.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_Element>)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft2d_Element>)
{
	ar & theElements_;
}