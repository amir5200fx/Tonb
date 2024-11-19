#pragma once
#ifndef _NumAlg_NelderMeadInfo_Header
#define _NumAlg_NelderMeadInfo_Header

#include <NumAlg_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class NumAlg_NelderMeadInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		Standard_Integer theMinNbIters_;
		Standard_Integer theMaxNbIters_;


		// private functions and operators [5/6/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theTolerance_;
			ar & theMinNbIters_;
			ar & theMaxNbIters_;
		}

	public:

		static TnbNumAlg_EXPORT const std::string extension;

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbNumAlg_EXPORT const Standard_Integer DEFAULT_MIN_ITERS;
		static TnbNumAlg_EXPORT const Standard_Integer DEFAULT_MAX_ITERS;


		// default constructor [5/6/2022 Amir]

		NumAlg_NelderMeadInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theMinNbIters_(DEFAULT_MIN_ITERS)
			, theMaxNbIters_(DEFAULT_MAX_ITERS)
		{}

		// constructors [5/6/2022 Amir]


		// public functions and operators [5/6/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto MinNbIterations() const
		{
			return theMinNbIters_;
		}

		auto MaxNbIterations() const
		{
			return theMaxNbIters_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetMinNbIterations(const Standard_Integer theNb)
		{
			theMinNbIters_ = theNb;
		}

		void SetMaxNbIterations(const Standard_Integer theNb)
		{
			theMaxNbIters_ = theNb;
		}
	};
}

#endif // !_NumAlg_NelderMeadInfo_Header
