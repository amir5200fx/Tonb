#pragma once
#ifndef _Geo_BladeViews_Header
#define _Geo_BladeViews_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [4/29/2022 Amir]
	class Geo_BladeExpandedView;
	class Geo_WrappedBladeSection;
	class Geo_UnWrappedBladeSection;

	class Geo_BladeViews
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Geo_BladeExpandedView>> theExpandedViews_;
		std::vector<std::shared_ptr<Geo_WrappedBladeSection>> theWrappedSections_;
		std::vector<std::shared_ptr<Geo_UnWrappedBladeSection>> theUnWrappedSections_;


		// private functions and operators [4/29/2022 Amir]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		// default constructor [4/29/2022 Amir]

		Geo_BladeViews()
		{}


		// constructors [4/29/2022 Amir]
		


		// public functions and operators [4/29/2022 Amir]

		const auto& ExpandedViews() const
		{
			return theExpandedViews_;
		}

		const auto& WrappedSections() const
		{
			return theWrappedSections_;
		}

		const auto& UnWrappedSections() const
		{
			return theUnWrappedSections_;
		}

		inline void SetExpandedViews(std::vector<std::shared_ptr<Geo_BladeExpandedView>>&&);
		inline void SetWrappedSections(std::vector<std::shared_ptr<Geo_WrappedBladeSection>>&&);
		inline void SetUnWrappedSections(std::vector<std::shared_ptr<Geo_UnWrappedBladeSection>>&&);

	};
}

#include <Geo_BladeViewsI.hxx>

#endif // !_Geo_BladeViews_Header
