#include <Aft_EdgeAdaptorTypes.hxx>

#include <Aft2d_Element.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Aft3d_Node.hxx>
#include <Aft3d_NodeAnIso.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_FacetAnIso.hxx>
#include <Aft3d_Element.hxx>
#include <Aft3d_ElementAnIso.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_EdgeAnIso.hxx>
#include <MeshBase_Tools.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_EdgeToFacetAdaptor)
{
	//ar & theFacets_;
	//MeshBase_Tools::Save(theFacets_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_EdgeToFacetAdaptor)
{
	//ar & theFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_EdgeToFacetAnIsoAdaptor)
{
	//ar & theFacets_;
	//MeshBase_Tools::Save(theFacets_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_EdgeToFacetAnIsoAdaptor)
{
	//ar & theFacets_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_EdgeToElementAdaptor)
{
	//ar & theElements_;
	//MeshBase_Tools::Save(theElements_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_EdgeToElementAdaptor)
{
	//ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_EdgeToElementAnIsoAdaptor)
{
	//ar & theElements_;
	//MeshBase_Tools::Save(theElements_, ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_EdgeToElementAnIsoAdaptor)
{
	//ar & theElements_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_Element>)
{
	//ar & theRight_;
	//ar & theLeft_;

	//MeshBase_Tools::Save(std::make_pair(theLeft_, theRight_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_Element>)
{
	//ar & theRight_;
	//ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_ElementAnIso>)
{
	//ar & theRight_;
	//ar & theLeft_;

	//MeshBase_Tools::Save(std::make_pair(theLeft_, theRight_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_ElementAnIso>)
{
	//ar & theRight_;
	//ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_ElementSurface>)
{
	//ar & theRight_;
	//ar & theLeft_;

	//MeshBase_Tools::Save(std::make_pair(theLeft_, theRight_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft2d_ElementSurface>)
{
	//ar & theRight_;
	//ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft3d_Facet>)
{
	//ar & theRight_;
	//ar & theLeft_;

	//MeshBase_Tools::Save(std::make_pair(theLeft_, theRight_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft3d_Facet>)
{
	//ar & theRight_;
	//ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft3d_FacetAnIso>)
{
	//ar & theRight_;
	//ar & theLeft_;

	//MeshBase_Tools::Save(std::make_pair(theLeft_, theRight_), ar);
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeAdaptor<tnbLib::Aft3d_FacetAnIso>)
{
	//ar & theRight_;
	//ar & theLeft_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_EdgeToFrontFacetAdaptor<tnbLib::Aft3d_Facet>)
{
	// empty body [12/18/2022 Payvand]
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_EdgeToFrontFacetAdaptor<tnbLib::Aft3d_Facet>)
{
	// empty body [12/18/2022 Payvand]
}