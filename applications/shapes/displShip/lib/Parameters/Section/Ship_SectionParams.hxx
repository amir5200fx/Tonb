#pragma once
#ifndef _Ship_SectionParams_Header
#define _Ship_SectionParams_Header

#include <Ship_Parameter.hxx>

namespace tnbLib
{

	class Ship_SectionParams
	{

		/*Private Data*/

		Ship_Parameter theTightness_;
		Ship_Parameter theDeadrise_;
		Ship_Parameter theSideSlope_;
		Ship_Parameter theFlare_;


	public:

		// default constructor [11/1/2022 Amir]

		Ship_SectionParams()
		{}


		// constructors [11/1/2022 Amir]


		// public functions and operators [11/1/2022 Amir]


		const auto& Tightness() const
		{
			return theTightness_;
		}

		auto& TightnessRef()
		{
			return theTightness_;
		}

		const auto& Deadrise() const
		{
			return theDeadrise_;
		}

		auto& DeadriseRef()
		{
			return theDeadrise_;
		}

		const auto& SideSlope() const
		{
			return theSideSlope_;
		}

		auto& SideSlopeRef()
		{
			return theSideSlope_;
		}

		const auto& Flare() const
		{
			return theFlare_;
		}

		auto& FlareRef()
		{
			return theFlare_;
		}

	};
}

#endif // !_Ship_SectionParams_Header
