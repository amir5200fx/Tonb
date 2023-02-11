#pragma once
#ifndef _Model_DisplNo1ParProfiles_Header
#define _Model_DisplNo1ParProfiles_Header

#include <Model_VesselParProfiles.hxx>

namespace tnbLib
{

	class Model_DisplNo1ParProfiles
		: public Model_VesselParProfiles
	{

		/*Private Data*/

		//std::shared_ptr<Model_ParamProfile> theFlare_;
		std::shared_ptr<Model_ParamProfile> theTightness_;

	public:

		// default constructor [12/21/2022 Payvand]

		Model_DisplNo1ParProfiles()
		{}

		// Public functions and operators [12/21/2022 Payvand]

		/*const auto& Flare() const
		{
			return theFlare_;
		}*/

		const auto& Tightness() const
		{
			return theTightness_;
		}

		/*template<class ProfileType>
		void SetFlare(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theFlare_ = theProfile;
		}

		template<class ProfileType>
		void SetFlare(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theFlare_ = std::move(theProfile);
		}*/

		template<class ProfileType>
		void SetTightness(const std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>& theProfile)
		{
			theTightness_ = theProfile;
		}

		template<class ProfileType>
		void SetTightness(std::shared_ptr<modelLib::vesselLib::KeelProfile<ProfileType>>&& theProfile)
		{
			theTightness_ = std::move(theProfile);
		}

	};
}

#endif // !_Model_DisplNo1ParProfiles_Header
