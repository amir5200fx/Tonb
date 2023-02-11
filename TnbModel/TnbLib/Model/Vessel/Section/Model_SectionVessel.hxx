#pragma once
#ifndef _Model_SectionVessel_Header
#define _Model_SectionVessel_Header

#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	class Model_SectionVessel
	{

		/*Private Data*/

		std::vector<Pnt3d> thePoints_;

	public:

		// default constructor [12/21/2022 Payvand]

		Model_SectionVessel()
		{}


		// constructors [12/21/2022 Payvand]

		Model_SectionVessel(const std::vector<Pnt3d>& thePnts)
			: thePoints_(thePnts)
		{}

		Model_SectionVessel(std::vector<Pnt3d>&& thePnts)
			: thePoints_(std::move(thePnts))
		{}


		// Public functions and operators [12/21/2022 Payvand]

		virtual Standard_Boolean HasCorner() const
		{
			return Standard_False;
		}

		const auto& Points() const
		{
			return thePoints_;
		}

		auto& PointsRef()
		{
			return thePoints_;
		}

		void SetPoints(const std::vector<Pnt3d>& thePnts)
		{
			thePoints_ = thePnts;
		}

		void SetPoints(std::vector<Pnt3d>&& thePnts)
		{
			thePoints_ = std::move(thePnts);
		}

	};
}

#endif // !_Model_SectionVessel_Header
