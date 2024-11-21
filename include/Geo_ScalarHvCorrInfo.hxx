#pragma once
#ifndef _Geo_ScalarHvCorrInfo_Header
#define _Geo_ScalarHvCorrInfo_Header

#include <Geo_Module.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Geo_ScalarHvCorrInfo
	{

		/*Private Data*/

		Standard_Real theFactor_;

		Standard_Integer theMaxNbIter_;

	public:

		static TnbGeo_EXPORT const Standard_Real DEFAULT_FACTOR;
		static TnbGeo_EXPORT const Standard_Integer DEFAULT_MAX_NB_ITERS;

		// default constructor [5/30/2022 Amir]

		Geo_ScalarHvCorrInfo()
			: theFactor_(DEFAULT_FACTOR)
			, theMaxNbIter_(DEFAULT_MAX_NB_ITERS)
		{}

		// constructors [5/30/2022 Amir]


		// public functions and operators [5/30/2022 Amir]

		auto Factor() const
		{
			return theFactor_;
		}

		auto MaxNbIters() const
		{
			return theMaxNbIter_;
		}

		void SetFactor(const Standard_Real theFactor)
		{
			theFactor_ = theFactor;
		}

		void SetMaxNbIters(const Standard_Integer theMaxIters)
		{
			theMaxNbIter_ = theMaxIters;
		}
	};
}

#endif // !_Geo_ScalarHvCorrInfo_Header
