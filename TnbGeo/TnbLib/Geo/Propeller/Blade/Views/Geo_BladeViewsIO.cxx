#include <Geo_BladeViews.hxx>

#include <Geo_BladeExpandedView.hxx>
#include <Geo_WrappedBladeSection.hxx>
#include <Geo_UnWrappedBladeSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo_BladeViews)
{
	ar & theExpandedViews_;
	ar & theWrappedSections_;
	ar & theUnWrappedSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo_BladeViews)
{
	ar & theExpandedViews_;
	ar & theWrappedSections_;
	ar & theUnWrappedSections_;
}