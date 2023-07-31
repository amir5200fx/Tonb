#pragma once
#ifndef _VoyageField_BackgroundCurrent_Header
#define _VoyageField_BackgroundCurrent_Header

#include <VoyageField_Current.hxx>
#include <VoyageGeo_VelocityBackgroundFwd.hxx>

#include <memory>

namespace tnbLib
{

	class VoyageField_BackgroundCurrent
		: public VoyageField_Current
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_VelocityBackground> theBack_;

	public:

		// default constructor [7/22/2023 Payvand]

		// constructors [7/22/2023 Payvand]

		VoyageField_BackgroundCurrent(const std::shared_ptr<VoyageGeo_VelocityBackground>& theBack)
			: theBack_(theBack)
		{}

		VoyageField_BackgroundCurrent(std::shared_ptr<VoyageGeo_VelocityBackground>&& theBack)
			: theBack_(std::move(theBack))
		{}


		// Public functions and operators [7/22/2023 Payvand]

		const auto& Background() const { return theBack_; }

		TnbVoyage_EXPORT std::shared_ptr<Voyage_Current> 
			Value(const Pnt2d& theCoord) const override;

	};
}

#endif // !_VoyageField_BackgroundCurrent_Header
