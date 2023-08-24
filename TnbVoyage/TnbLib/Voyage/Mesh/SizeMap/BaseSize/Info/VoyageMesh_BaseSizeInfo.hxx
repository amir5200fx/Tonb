#pragma once
#ifndef _VoyageMesh_BaseSizeInfo_Header
#define _VoyageMesh_BaseSizeInfo_Header

#include <Voyage_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class VoyageMesh_BaseSizeInfo
	{

		/*Private Data*/

		Standard_Real theMaxDeviation_;
		Standard_Real theGrowthRate_;

		Standard_Real theAngle_;


		// Private functions and operators [8/15/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theMaxDeviation_;
			ar& theGrowthRate_;
			ar& theAngle_;
		}

	public:

		static TnbVoyage_EXPORT Standard_Real DEFAULT_MAX_DEVIATION;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_GROWTH_RATE;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_ANGLE;

		// default constructor [8/15/2023 aamir]

		VoyageMesh_BaseSizeInfo()
			: theMaxDeviation_(DEFAULT_MAX_DEVIATION)
			, theGrowthRate_(DEFAULT_GROWTH_RATE)
			, theAngle_(DEFAULT_ANGLE)
		{}

		// constructors [8/15/2023 aamir]

		// Public functions and operators [8/15/2023 aamir]

		auto MaxDeviation() const { return theMaxDeviation_; }
		auto GrowthRate() const { return theGrowthRate_; }
		auto Angle() const { return theAngle_; }

		void SetMaxDeviation(const Standard_Real theValue) { theMaxDeviation_ = theValue; }
		void SetGrowthRate(const Standard_Real theValue) { theGrowthRate_ = theValue; }
		void SetAngle(const Standard_Real theValue) { theAngle_ = theValue; }

	};
}

#endif // !_VoyageMesh_BaseSizeInfo_Header
