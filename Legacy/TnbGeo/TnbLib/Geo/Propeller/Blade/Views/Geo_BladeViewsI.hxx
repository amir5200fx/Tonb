#pragma once
inline void tnbLib::Geo_BladeViews::SetExpandedViews
(
	std::vector<std::shared_ptr<Geo_BladeExpandedView>>&& views
)
{
	theExpandedViews_ = std::move(views);
}

inline void tnbLib::Geo_BladeViews::SetWrappedSections
(
	std::vector<std::shared_ptr<Geo_WrappedBladeSection>>&& views
)
{
	theWrappedSections_ = std::move(views);
}

inline void tnbLib::Geo_BladeViews::SetUnWrappedSections
(
	std::vector<std::shared_ptr<Geo_UnWrappedBladeSection>>&& views
)
{
	theUnWrappedSections_ = std::move(views);
}