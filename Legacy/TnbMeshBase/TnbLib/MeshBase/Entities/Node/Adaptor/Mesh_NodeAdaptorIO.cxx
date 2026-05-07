#include <Mesh_NodeAdaptor.hxx>

#include <Mesh_NodeAdaptorTypes.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Element.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToEdgeAdaptor)
{
	ar & theEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToEdgeAdaptor)
{
	ar & theEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFacetAdaptor)
{
	ar & theFacets_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFacetAdaptor)
{
	ar & theFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToBoundaryEdgeAdaptor)
{
	ar & theBoundaryEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToBoundaryEdgeAdaptor)
{
	ar & theBoundaryEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToBoundaryFacetAdaptor)
{
	ar & theBoundaryFacets_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToBoundaryFacetAdaptor)
{
	ar & theBoundaryFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToEdgeAdaptor)
{
	ar & theEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToEdgeAdaptor)
{
	ar & theEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToElementAdaptor)
{
	ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToBoundaryEdgeAdaptor)
{
	ar & theBoundaryEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToBoundaryEdgeAdaptor)
{
	ar & theBoundaryEdges_;
}