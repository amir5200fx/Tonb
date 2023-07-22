#pragma once
#ifndef _VoyageFun_ProfiledCalmResist_Header
#define _VoyageFun_ProfiledCalmResist_Header

#include <VoyageFun_CalmResist.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/11/2023 Payvand]

	class Voyage_Profile;

	class VoyageFun_ProfiledCalmResist
		: public VoyageFun_CalmResist
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Profile> theProfile_;

	public:

		// default constructor [7/11/2023 Payvand]


		// constructors [7/11/2023 Payvand]

		VoyageFun_ProfiledCalmResist(const std::shared_ptr<Voyage_Profile>& theProfile)
			: theProfile_(theProfile)
		{}

		VoyageFun_ProfiledCalmResist(std::shared_ptr<Voyage_Profile>&& theProfile)
			: theProfile_(std::move(theProfile))
		{}

		// Public functions and operators [7/11/2023 Payvand]

		const auto& Profile() const { return theProfile_; }

		void SetProfile(const std::shared_ptr<Voyage_Profile>& theProfile) { theProfile_ = theProfile; }
		void SetProfile(std::shared_ptr<Voyage_Profile>&& theProfile) { theProfile_ = std::move(theProfile); }

	};
}

#endif // !_VoyageFun_ProfiledCalmResist_Header
