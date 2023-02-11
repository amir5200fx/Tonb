#pragma once
#ifndef _Model_CtrlNet_Header
#define _Model_CtrlNet_Header

#include <Pnt3d.hxx>

#include <vector>

namespace tnbLib
{

	class Model_CtrlNet
	{

		/*private Data*/

		std::vector<std::vector<Pnt3d>> theCoords_;

	public:

		// default constructor [12/20/2022 Payvand]

		Model_CtrlNet()
		{}

		// constructors [12/20/2022 Payvand]


		// public functions and operators [12/20/2022 Payvand]

		const auto& Coords() const
		{
			return theCoords_;
		}

		auto& CoordsRef()
		{
			return theCoords_;
		}

		void SetCoords(const std::vector<std::vector<Pnt3d>>& theCoords)
		{
			theCoords_ = theCoords;
		}

		void SetCoords(std::vector<std::vector<Pnt3d>>&& theCoords)
		{
			theCoords_ = std::move(theCoords);
		}
	};
}

#endif // !_Model_CtrlNet_Header
