#include <Aft2d_BndNodeSurface.hxx>

#include <Aft2d_BndEdgeSurface.hxx>
#include <Aft2d_ElementSurface.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_BndNodeSurface);

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_EdgeSurface>)
{}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_EdgeSurface>)
{}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_ElementSurface>)
{}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_ElementSurface>)
{}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdgeSurface>)
{}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdgeSurface>)
{}