#include <Aft2d_BoundaryOfPlane.hxx>

#include <Geo2d_MetricPrcsr.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Aft2d_Element.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_BoundaryOfPlane)
{
	ar & boost::serialization::base_object<Aft_BoundaryOfPlane_Base<Aft2d_SegmentEdge>>(*this);

	ar & theMetricPrscr_;
	ar & theInfo_;

	ar & thePlane_;

	ar & theSegments_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_BoundaryOfPlane)
{
	ar & boost::serialization::base_object<Aft_BoundaryOfPlane_Base<Aft2d_SegmentEdge>>(*this);

	ar & theMetricPrscr_;
	ar & theInfo_;

	ar & thePlane_;

	ar & theSegments_;
}