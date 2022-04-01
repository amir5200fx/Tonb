#pragma once
#ifndef _Cad2d_MergeCurvesInfo_Header
#define _Cad2d_MergeCurvesInfo_Header

#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Cad2d_MergeCurvesInfo
	{

		/*Private Data*/

		Standard_Real theTolerance_;
		Standard_Real theRadius_;


		// private functions and operators [3/22/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theTolerance_;
			ar& theRadius_;
		}

	public:

		static TnbCad2d_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbCad2d_EXPORT const Standard_Real DEFAULT_RADIUS;

		// default constructor [3/21/2022 Amir]

		Cad2d_MergeCurvesInfo()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theRadius_(DEFAULT_RADIUS)
		{}

		// constructors [3/21/2022 Amir]

		Cad2d_MergeCurvesInfo
		(
			const Standard_Real theTolerance, 
			const Standard_Real theRadius
		)
			: theTolerance_(theTolerance)
			, theRadius_(theRadius)
		{}

		// public functions and operators [3/21/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetRadius(const Standard_Real theRadius)
		{
			theRadius_ = theRadius;
		}
	};
}

#endif // !_Cad2d_MergeCurvesInfo_Header
