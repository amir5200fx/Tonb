#pragma once
#ifndef _Model_CorneredSectionVessel_Header
#define _Model_CorneredSectionVessel_Header

#include <Model_SectionVessel.hxx> 

namespace tnbLib
{

	class Model_CorneredSectionVessel
		: public Model_SectionVessel
	{

		/*Private Data*/

		Standard_Integer theCorner_;

	public:

		// default constructor [12/21/2022 Payvand]

		Model_CorneredSectionVessel()
		{}

		// constructors [12/21/2022 Payvand]

		Model_CorneredSectionVessel(const std::vector<Pnt3d>& thePnts)
			: Model_SectionVessel(thePnts)
		{}

		Model_CorneredSectionVessel(std::vector<Pnt3d>&& thePnts)
			: Model_SectionVessel(std::move(thePnts))
		{}


		// Public functions and operators [12/21/2022 Payvand]

		auto CornerId() const
		{
			return theCorner_;
		}

		Pnt3d Corner() const;

		void SetCornerId(const Standard_Integer theId)
		{
			theCorner_ = theId;
		}

	};
}

#endif // !_Model_CorneredSectionVessel_Header

