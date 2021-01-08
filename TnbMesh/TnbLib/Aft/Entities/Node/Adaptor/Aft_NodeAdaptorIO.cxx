#include <Aft_NodeAdaptorTypes.hxx>

#include <Aft_Nodes.hxx>
#include <Aft_Edges.hxx>
#include <Aft_Facets.hxx>
#include <Aft_Elements.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeAnIsoAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeAnIsoAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeSurfaceAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh2d_NodeToFrontEdgeSurfaceAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontEdgeAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontEdgeAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontEdgeAnIsoAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontEdgeAnIsoAdaptor)
{
	ar & theFrontEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontFacetAdaptor)
{
	ar & theFrontFacets_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontFacetAdaptor)
{
	ar & theFrontFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontFacetAnIsoAdaptor)
{
	ar & theFrontFacets_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh3d_NodeToFrontFacetAnIsoAdaptor)
{
	ar & theFrontFacets_;
}