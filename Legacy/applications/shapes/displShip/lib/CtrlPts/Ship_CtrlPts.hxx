#pragma once
#ifndef _Ship_SectionCtrlPts_Header
#define _Ship_SectionCtrlPts_Header

#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	class Ship_SectionCtrlPts
	{

		/*Private Data*/

		std::vector<Pnt3d> theQs_;

	public:

		// default constructor [10/31/2022 Amir]

		Ship_SectionCtrlPts()
		{}


		// constructors [10/31/2022 Amir]

		explicit Ship_SectionCtrlPts(const std::vector<Pnt3d>& theQs)
			: theQs_(theQs)
		{}

		Ship_SectionCtrlPts(std::vector<Pnt3d>&& theQs)
			: theQs_(std::move(theQs))
		{}


		// public functions and operators [10/31/2022 Amir]

		const auto& Qs() const
		{
			return theQs_;
		}

		void SetQs(const std::vector<Pnt3d>& theQs)
		{
			theQs_ = theQs;
		}

		void SetQs(std::vector<Pnt3d>&& theQs)
		{
			theQs_ = std::move(theQs);
		}
	};
}

#endif // !_Ship_SectionCtrlPts_Header
