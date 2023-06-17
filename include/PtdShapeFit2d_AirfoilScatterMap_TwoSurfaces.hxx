#pragma once
#ifndef _PtdShapeFit2d_AirfoilScatterMap_TwoSurfaces_Header
#define _PtdShapeFit2d_AirfoilScatterMap_TwoSurfaces_Header

#include <PtdShapeFit2d_AirfoilScatterMap.hxx>

namespace tnbLib
{

	namespace airfoilLib
	{

		class ScatterMap_TwoSurfaces
			: public PtdShapeFit2d_AirfoilScatterMap
		{

		public:

			using PtdShapeFit2d_ScatterMap::ptList;

		private:

			/*Private Data*/

			std::shared_ptr<ptList> theUpper_;
			std::shared_ptr<ptList> theLower_;


		public:

			// default constructor [4/25/2023 Payvand]

			ScatterMap_TwoSurfaces()
			{}


			// constructors [4/25/2023 Payvand]

			ScatterMap_TwoSurfaces
			(
				const std::shared_ptr<ptList>& theUpper,
				const std::shared_ptr<ptList>& theLower
			)
				: theUpper_(theUpper)
				, theLower_(theLower)
			{}

			ScatterMap_TwoSurfaces
			(
				std::shared_ptr<ptList>&& theUpper,
				std::shared_ptr<ptList>&& theLower
			)
				: theUpper_(std::move(theUpper))
				, theLower_(std::move(theLower))
			{}


			// Public functions and operators [4/25/2023 Payvand]

			const auto& UpperPnts() const
			{
				return theUpper_;
			}

			const auto& LowerPnts() const
			{
				return theLower_;
			}

			auto& UpperPntsRef()
			{
				return theUpper_;
			}

			auto& LowerPntsRef()
			{
				return theLower_;
			}

			Standard_Integer NbRegions() const override;

			std::shared_ptr<ptList> Region(const Standard_Integer theIndex) const override;

			void SetUpperPnts(const std::shared_ptr<ptList>& thePnts);
			void SetUpperPnts(std::shared_ptr<ptList>&& thePnts);
			void SetLowerPnts(const std::shared_ptr<ptList>& thePnts);
			void SetLowerPnts(std::shared_ptr<ptList>&& thePnts);

		};
	}
}


#endif // !_PtdShapeFit2d_AirfoilScatterMap_TwoSurfaces_Header
