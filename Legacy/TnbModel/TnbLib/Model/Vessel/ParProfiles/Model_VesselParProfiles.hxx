#pragma once
#ifndef _Model_VesselParProfiles_Header
#define _Model_VesselParProfiles_Header

#include <Model_VesselProfiles.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [12/21/2022 Payvand]

	class Model_ParamProfile;

	class Model_VesselParProfiles
	{

		/*Private Data*/

		std::shared_ptr<Model_ParamProfile> theDeck_;
		std::shared_ptr<Model_ParamProfile> theButtock_;
		std::shared_ptr<Model_ParamProfile> theKeel_;
		std::shared_ptr<Model_ParamProfile> theDepth_;

		std::shared_ptr<Model_ParamProfile> theDeadrise_;
		std::shared_ptr<Model_ParamProfile> theSideSlope_;

		//std::vector<std::shared_ptr<Model_ParamProfile>> theSections_;

	public:

		// default constructor [12/21/2022 Payvand]

		Model_VesselParProfiles()
		{}


		// constructors [12/21/2022 Payvand]


		// Public functions and operators [12/21/2022 Payvand]

		const auto& Deck() const
		{
			return theDeck_;
		}

		const auto& Buttock() const
		{
			return theButtock_;
		}

		const auto& Keel() const
		{
			return theKeel_;
		}

		const auto& Depth() const
		{
			return theDepth_;
		}

		const auto& Deadrise() const
		{
			return theDeadrise_;
		}

		const auto& SideSlope() const
		{
			return theSideSlope_;
		}

		/*const auto& Sections() const
		{
			return theSections_;
		}*/

		template<class ProfileType>
		void SetDeck(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theDeck_ = theProfile;
		}

		template<class ProfileType>
		void SetDeck(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theDeck_ = std::move(theProfile);
		}

		template<class ProfileType>
		void SetButtock(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theButtock_ = theProfile;
		}

		template<class ProfileType>
		void SetButtock(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theButtock_ = std::move(theProfile);
		}

		template<class ProfileType>
		void SetKeel(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theKeel_ = theProfile;
		}

		template<class ProfileType>
		void SetKeel(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theKeel_ = std::move(theProfile);
		}

		template<class ProfileType>
		void SetDepth(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theDepth_ = theProfile;
		}

		template<class ProfileType>
		void SetDepth(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theDepth_ = std::move(theProfile);
		}

		template<class ProfileType>
		void SetDeadrise(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theDeadrise_ = theProfile;
		}

		template<class ProfileType>
		void SetDeadrise(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theDeadrise_ = std::move(theProfile);
		}

		template<class ProfileType>
		void SetSideSlope(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theSideSlope_ = theProfile;
		}

		template<class ProfileType>
		void SetSideSlope(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theSideSlope_ = std::move(theProfile);
		}

		/*void SetSections(const std::vector<std::shared_ptr<Model_ParamProfile>>& theProfiles)
		{
			theSections_ = theProfiles;
		}

		void SetSections(std::vector<std::shared_ptr<Model_ParamProfile>>&& theProfiles)
		{
			theSections_ = std::move(theProfiles);
		}*/

	};
}

#endif // !_Model_VesselParProfiles_Header
