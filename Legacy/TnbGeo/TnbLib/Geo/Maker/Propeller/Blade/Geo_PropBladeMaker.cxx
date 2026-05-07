#include <Geo_PropBladeMaker.hxx>

#include <Geo_BladeViews.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Geo_PropBladeMaker::CalcBladeViews()
{
	auto bladeViews = std::make_shared<Geo_BladeViews>();
	Debug_Null_Pointer(bladeViews);

	BladeViewsRef() = bladeViews;

	std::vector<std::shared_ptr<Geo_BladeExpandedView>> expandedViews;
	expandedViews.reserve(NbSections());
	for (Standard_Integer section = 0; section < NbSections(); section++)
	{
		auto sectionQ = AirfoilSection(section);
		Debug_Null_Pointer(sectionQ);

		auto expView = CreateExpandedView(section, *sectionQ);
		expandedViews.push_back(std::move(expView));
	}

	bladeViews->SetExpandedViews(std::move(expandedViews));

	auto unWrappedView = CreateUnWrappedView();
	bladeViews->SetUnWrappedSections(std::move(unWrappedView));

	auto wrappedView = CreateWrappedView();
	bladeViews->SetWrappedSections(std::move(wrappedView));
}