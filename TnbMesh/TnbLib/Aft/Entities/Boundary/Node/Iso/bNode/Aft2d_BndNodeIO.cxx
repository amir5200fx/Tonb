#include <Aft2d_BndNode.hxx>

#include <Aft2d_BndEdge.hxx>
#include <Aft2d_Element.hxx>
#include <MeshBase_Tools.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_BndNode);


template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_Edge>)
{
	//ar & theEdges_;
	//MeshBase_Tools::Save(theEdges_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToEdgeAdaptor<tnbLib::Aft2d_Edge>)
{
	//ar & theEdges_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_Element>)
{
	//ar & theElements_;
	//MeshBase_Tools::Save(theElements_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToElementAdaptor<tnbLib::Aft2d_Element>)
{
	//ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdge>)
{
	//ar & theBoundaryEdges_;
	//MeshBase_Tools::Save(theBoundaryEdges_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_NodeToBoundaryEdgeAdaptor<tnbLib::Aft2d_BndEdge>)
{
	//ar & theBoundaryEdges_;
}