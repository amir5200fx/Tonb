#pragma once
inline void tnbLib::PtdModel_BladeView::SetExpandedViews
(
	std::vector<std::shared_ptr<PtdModel_BladeExpandedView>>&& views
)
{
	theExpandedViews_ = std::move(views);
}

inline void tnbLib::PtdModel_BladeView::SetWrappedSections
(
	std::vector<std::shared_ptr<PtdModel_WrappedBladeSection>>&& theSections
)
{
	theWrappedSections_ = std::move(theSections);
}

inline void tnbLib::PtdModel_BladeView::SetUnWrappedSections
(
	std::vector<std::shared_ptr<PtdModel_UnWrappedBladeSection>>&& theSections
)
{
	theUnWrappedSections_ = std::move(theSections);
}

inline void tnbLib::PtdModel_BladeView::SetFace(std::shared_ptr<PtdModel_BladeFace>&& face)
{
	theFace_ = std::move(face);
}

inline void tnbLib::PtdModel_BladeView::SetBack(std::shared_ptr<PtdModel_BladeFace>&& face)
{
	theBack_ = std::move(face);
}