#include <Aft3d_GlobalData.hxx>

#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Node.hxx>
#include <Mesh_QualityMap.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft3d_Element>)
{
	ar& theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterElement<tnbLib::Aft3d_Element>)
{
	ar& theElements_;
}