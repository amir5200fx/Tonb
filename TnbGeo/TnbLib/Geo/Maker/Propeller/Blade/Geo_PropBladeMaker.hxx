#pragma once
#ifndef _Geo_PropBladeMaker_Header
#define _Geo_PropBladeMaker_Header

#include <Geo2d_AirfoilSectionFwd.hxx>
#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [5/6/2022 Amir]
	class Geo_UnWrappedBladeSection;
	class Geo_WrappedBladeSection;
	class Geo_BladeExpandedView;

	class Geo_BladeViews;

	class Geo_PropBladeMaker
	{

		/*Private Data*/

		std::shared_ptr<Geo_BladeViews> theViews_;


		// private functions and operators [5/6/2022 Amir]

		auto& BladeViewsRef()
		{
			return theViews_;
		}


		void CalcBladeViews();

	protected:

		/*default constructor*/

		Geo_PropBladeMaker()
		{}


		// constructors [5/6/2022 Amir]


		// protected functions and operators [5/6/2022 Amir]

		virtual std::shared_ptr<Geo_BladeExpandedView> CreateExpandedView(const Standard_Integer sect, const Geo2d_AirfoilSection&) const = 0;

		virtual std::vector<std::shared_ptr<Geo_UnWrappedBladeSection>> CreateUnWrappedView() const = 0;
		virtual std::vector<std::shared_ptr<Geo_WrappedBladeSection>> CreateWrappedView() const = 0;

	public:

		// public functions and operators [5/6/2022 Amir]

		virtual Standard_Integer NbSections() const = 0;

		virtual std::shared_ptr<Geo2d_AirfoilSection> AirfoilSection(const Standard_Integer theIndex) const = 0;

		const auto& BladeViews() const
		{
			return theViews_;
		}
	};
}

#endif // !_Geo_PropBladeMaker_Header
