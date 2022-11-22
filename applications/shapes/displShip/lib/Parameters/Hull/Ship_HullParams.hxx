#pragma once
#ifndef _Ship_HullParams_Header
#define _Ship_HullParams_Header

#include <Ship_SectionParams.hxx>

namespace tnbLib
{

	class Ship_HullParams
	{

		/*private Data*/

		Ship_SectionParams theAftSection_;
		Ship_SectionParams theMidSection_;
		Ship_SectionParams theFwdSection_;

		Ship_Parameter theMaxAreaLocation_;
		Ship_Parameter theFwdFullness_;
		Ship_Parameter theAftFullness_;

	public:

		// default constructor [11/1/2022 Amir]

		Ship_HullParams()
		{}


		// constructors [11/1/2022 Amir]


		// public functions and operators [11/1/2022 Amir]

		const auto& AftSection() const
		{
			return theAftSection_;
		}

		auto& AftSectionRef()
		{
			return theAftSection_;
		}

		const auto& MidSection() const
		{
			return theMidSection_;
		}

		auto& MidSectionRef()
		{
			return theMidSection_;
		}

		const auto& FwdSection() const
		{
			return theFwdSection_;
		}

		auto& FwdSectionRef()
		{
			return theFwdSection_;
		}

		const auto& MaxAreaLocation() const
		{
			return theMaxAreaLocation_;
		}

		auto& MaxAreaLocationRef()
		{
			return theMaxAreaLocation_;
		}

		const auto& FwdFullness() const
		{
			return theFwdFullness_;
		}

		auto& FwdFullnessRef()
		{
			return theFwdFullness_;
		}

		const auto& AftFullness() const
		{
			return theAftFullness_;
		}

		auto& AftFullnessRef()
		{
			return theAftFullness_;
		}
	};
}

#endif // !_Ship_HullParams_Header
