#include <Mesh_EdgeAdaptorTypes.hxx>

#include <Mesh2d_Element.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_EdgeToFacetAdaptor)
{
	ar & theFacets_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_EdgeToFacetAdaptor)
{
	ar & theFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_EdgeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_EdgeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Mesh2d_Element>)
{
	ar & theRight_;
	ar & theLeft_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Mesh2d_Element>)
{
	ar & theRight_;
	ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Mesh3d_Facet>)
{
	ar & theRight_;
	ar & theLeft_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Mesh3d_Facet>)
{
	ar & theRight_;
	ar & theLeft_;
}