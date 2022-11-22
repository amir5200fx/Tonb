#pragma once
#ifndef _Ship_Profiles_Header
#define _Ship_Profiles_Header

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [11/2/2022 Amir]
	class Ship_Profile;

	class Ship_Profiles
	{

		/*Private Data*/

		std::shared_ptr<Ship_Profile> theDeck_;
		std::shared_ptr<Ship_Profile> theButtock_;

		std::vector<std::shared_ptr<Ship_Profile>> theFlares_;
		std::vector<std::shared_ptr<Ship_Profile>> theSections_;

	public:

		// default constructor [11/2/2022 Amir]

		Ship_Profiles()
		{}

		// constructors [11/2/2022 Amir]


		// public functions and operators [11/2/2022 Amir]

		const auto& Deck() const
		{
			return theDeck_;
		}

		const auto& Buttock() const
		{
			return theButtock_;
		}

		const auto& Flares() const
		{
			return theFlares_;
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		void SetDeck(const std::shared_ptr<Ship_Profile>& theProfile)
		{
			theDeck_ = theProfile;
		}

		void SetButtock(const std::shared_ptr<Ship_Profile>& theProfile)
		{
			theButtock_ = theProfile;
		}

		void SetFlares(const std::vector<std::shared_ptr<Ship_Profile>>& theProfiles)
		{
			theFlares_ = theProfiles;
		}

		void SetFlares(std::vector<std::shared_ptr<Ship_Profile>>&& theProfiles)
		{
			theFlares_ = std::move(theProfiles);
		}

		void SetSections(const std::vector<std::shared_ptr<Ship_Profile>>& theProfiles)
		{
			theSections_ = theProfiles;
		}

		void SetSections(std::vector<std::shared_ptr<Ship_Profile>>&& theProfiles)
		{
			theSections_ = std::move(theProfiles);
		}
	};
}

#endif // !_Ship_Profiles_Header
