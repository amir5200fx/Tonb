#pragma once
#ifndef _Geo_NormalizePts_Header
#define _Geo_NormalizePts_Header

#include <Geo_Module.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	template<class Point>
	class Geo_NormalizePts
		: public Global_Done
	{

		/*Private Data*/

		const std::vector<Point>& thePts_;


		// results [5/28/2022 Amir]

		std::vector<Point> theNormalized_;


		auto& NormalizedRef()
		{
			return theNormalized_;
		}

	public:

		// default constructor [5/28/2022 Amir]


		// constructors [5/28/2022 Amir]

		explicit Geo_NormalizePts(const std::vector<Point>& thePoints)
			: thePts_(thePoints)
		{}


		// public functions and operators [5/28/2022 Amir]

		const auto& Points() const
		{
			return thePts_;
		}

		const auto& Normalized() const
		{
			return theNormalized_;
		}

		void Perform();
	};
}

#endif // !_Geo_NormalizePts_Header
