#include <Aft_ElementAdaptorTypes.hxx>

#include <Aft_Nodes.hxx>
#include <Aft_Edges.hxx>
#include <Aft_Elements.hxx>
#include <Aft_Facets.hxx>
#include <MeshBase_Tools.hxx>
#include <Mesh_IO.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_ElementAdaptor)
{
	//ar & theNeighbors_;
	//MeshBase_Tools::Save(theNeighbors_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_ElementAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_ElementAnIsoAdaptor)
{
	//ar & theNeighbors_;
	//MeshBase_Tools::Save(theNeighbors_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_ElementAnIsoAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_ElementAdaptor)
{
	//ar & theNeighbors_;
	//MeshBase_Tools::Save(theNeighbors_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_ElementAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_ElementAnIsoAdaptor)
{
	//ar & theNeighbors_;
	//MeshBase_Tools::Save(theNeighbors_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_ElementAnIsoAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_ElementSurfaceAdaptor)
{
	//ar & theNeighbors_;
	//MeshBase_Tools::Save(theNeighbors_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_ElementSurfaceAdaptor)
{
	//ar & theNeighbors_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_FacetAdaptor)
{
	//ar & theLeftElement_;
	//ar & theRightElement_;
	//MeshBase_Tools::Save(std::make_pair(theLeftElement_, theRightElement_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_FacetAdaptor)
{
	//ar & theLeftElement_;
	//ar & theRightElement_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_FacetAnIsoAdaptor)
{
	//ar & theLeftElement_;
	//ar & theRightElement_;
	//MeshBase_Tools::Save(std::make_pair(theLeftElement_, theRightElement_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_FacetAnIsoAdaptor)
{
	//ar & theLeftElement_;
	//ar & theRightElement_;
}