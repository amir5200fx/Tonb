#include <PtdModel_BladeView.hxx>

#include <PtdModel_BladeFace.hxx>
#include <PtdModel_BladeExpandedView.hxx>
#include <PtdModel_WrappedBladeSection.hxx>
#include <PtdModel_UnWrappedBladeSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeView)
{
	ar & theExpandedViews_;
	ar & theWrappedSections_;
	ar & theUnWrappedSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeView)
{
	ar & theExpandedViews_;
	ar & theWrappedSections_;
	ar & theUnWrappedSections_;
}