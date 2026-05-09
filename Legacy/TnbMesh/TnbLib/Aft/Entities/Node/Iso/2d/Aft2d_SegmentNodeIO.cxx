#include <Aft2d_SegmentNode.hxx>

#include <Aft2d_PlnCurve.hxx>
#include <Aft2d_Element.hxx>

typedef tnbLib::Mesh_BndNodeGeomAdaptor<tnbLib::Aft2d_PlnCurve, void, tnbLib::Mesh_BndNode_Position_Segment>
bndNodeGeomAdaptor;

template<>
TNB_SAVE_IMPLEMENTATION(bndNodeGeomAdaptor)
{
	ar & theCurve_;
}

template<>
TNB_LOAD_IMPLEMENTATION(bndNodeGeomAdaptor)
{
	ar & theCurve_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SegmentNode);