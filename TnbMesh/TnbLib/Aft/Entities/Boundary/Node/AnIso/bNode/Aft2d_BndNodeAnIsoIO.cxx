#include <Aft2d_BndNodeAnIso.hxx>

#include <Aft2d_BndEdgeAnIso.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Aft2d_ElementAnIso.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdgeAnIso>)
{
	//ar & theBoundaryEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdgeAnIso>)
{
	//ar & theBoundaryEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_EdgeAnIso>)
{
	//ar & theEdges_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_EdgeAnIso>)
{
	//ar & theEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_ElementAnIso>)
{
	//ar & theElements_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_ElementAnIso>)
{
	//ar & theElements_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_BndNodeAnIso);