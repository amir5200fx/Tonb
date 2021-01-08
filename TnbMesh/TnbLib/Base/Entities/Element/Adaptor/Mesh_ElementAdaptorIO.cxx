#include <Mesh_ElementAdaptorTypes.hxx>

#include <Mesh3d_Element.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh2d_Element.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_ElementAdaptor)
{
	ar & theNeighbors_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_ElementAdaptor)
{
	ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_ElementAdaptor)
{
	ar & theNeighbors_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_ElementAdaptor)
{
	ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_FacetElementAdaptor)
{
	ar & theLeftElement_;
	ar & theRightElement_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_FacetElementAdaptor)
{
	ar & theLeftElement_;
	ar & theRightElement_;
}