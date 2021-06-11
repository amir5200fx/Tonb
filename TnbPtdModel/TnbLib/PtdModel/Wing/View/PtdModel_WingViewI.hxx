#pragma once
inline void tnbLib::PtdModel_WingView::SetExpandedViews(std::vector<std::shared_ptr<PtdModel_WingExpandedView>>&& views)
{
	theExpandedViews_ = std::move(views);
}

inline void tnbLib::PtdModel_WingView::SetWrappedSections(std::vector<std::shared_ptr<PtdModel_WrappedWingSection>>&& theSections)
{
	theWrappedSections_ = std::move(theSections);
}