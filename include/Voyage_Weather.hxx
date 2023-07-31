#pragma once
#ifndef _Voyage_Weather_Header
#define _Voyage_Weather_Header

#include <Voyage_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/15/2023 Payvand]
	class Voyage_Wave;
	class Voyage_Wind;
	class Voyage_Current;

	class Voyage_Weather
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Wave> theWave_;
		std::shared_ptr<Voyage_Wind> theWind_;
		std::shared_ptr<Voyage_Current> theCurrent_;


		// Private functions and operators [7/15/2023 Payvand]

		TNB_SERIALIZATION(TnbVoyage_EXPORT);

	public:

		// default constructor [7/15/2023 Payvand]

		Voyage_Weather()
		{}

		// constructors [7/15/2023 Payvand]


		// Public functions and operators [7/15/2023 Payvand]

		const auto& Wave() const { return theWave_; }
		const auto& Wind() const { return theWind_; }
		const auto& Current() const { return theCurrent_; }

		void SetWave(const std::shared_ptr<Voyage_Wave>& theWave) { theWave_ = theWave; }
		void SetWave(std::shared_ptr<Voyage_Wave>&& theWave) { theWave_ = std::move(theWave); }
		void SetWind(const std::shared_ptr<Voyage_Wind>& theWind) { theWind_ = theWind; }
		void SetWind(std::shared_ptr<Voyage_Wind>&& theWind) { theWind_ = std::move(theWind); }
		void SetCurrent(const std::shared_ptr<Voyage_Current>& theCurrent) { theCurrent_ = theCurrent; }
		void SetCurrent(std::shared_ptr<Voyage_Current>&& theCurrent) { theCurrent_ = std::move(theCurrent); }

	};

}

#endif // !_Voyage_Weather_Header
