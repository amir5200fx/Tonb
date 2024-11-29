#pragma once
#ifndef _Voyage_AdaptPath_Info_Header
#define _Voyage_AdaptPath_Info_Header

#include <Voyage_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Voyage_AdaptPath_Info
	{

		/*Private Data*/

		Standard_Real theTargetAngle_;

		Standard_Integer theNbLevels_;
		Standard_Integer theNbSamples_;

		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& theTargetAngle_;
			ar& theNbLevels_;
			ar& theNbSamples_;
		}

	public:

		static TnbVoyage_EXPORT const Standard_Integer DEFAULT_NB_SAMPLES;
		static TnbVoyage_EXPORT const Standard_Integer DEFAULT_NB_LEVELS;

		static TnbVoyage_EXPORT const Standard_Real DEFAULT_TARGET_ANGLE;

		// default constructor

		TnbVoyage_EXPORT Voyage_AdaptPath_Info();

		// constructors

		Voyage_AdaptPath_Info
		(
			const Standard_Real theTargetAngle,
			const Standard_Integer theNbLevels,
			const Standard_Integer theNbSamples
		)
			: theTargetAngle_(theTargetAngle)
			, theNbLevels_(theNbLevels)
			, theNbSamples_(theNbSamples)
		{}

		// Public functions and operators

		auto TargetAngle() const { return theTargetAngle_; }

		auto NbLevels() const { return theNbLevels_; }
		auto NbSamples() const { return theNbSamples_; }

		void SetTargetAngle(const Standard_Real theAngle) { theTargetAngle_ = theAngle; }

		void SetNbLevels(const Standard_Integer theNbLevels) { theNbLevels_ = theNbLevels; }
		void SetNbSamples(const Standard_Integer theNbSamples) { theNbSamples_ = theNbSamples; }
	};
}

#endif