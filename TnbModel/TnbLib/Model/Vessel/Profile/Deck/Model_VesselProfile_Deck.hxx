#pragma once
#ifndef _Model_VesselProfile_Deck_Header
#define _Model_VesselProfile_Deck_Header

#include <Model_VesselProfile.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		namespace vesselLib
		{

			template<class ProfileType>
			class DeckProfile
				: public VesselProfile<ProfileType>
			{

				/*Private Data*/

			public:

				// constructors [1/18/2023 Payvand]

				template<class... _Types>
				DeckProfile(_Types&&... _Args)
					: VesselProfile<ProfileType>(_Args...)
				{}


				// Public functions and operators [1/18/2023 Payvand]

				Standard_Boolean IsDeck() const override
				{
					return Standard_True;
				}

			};

			template<class ProfileType>
			Standard_Boolean is_deck_profile(const std::shared_ptr<ProfileType>& theProfile)
			{
				return (Standard_Boolean)std::dynamic_pointer_cast<DeckProfile<ProfileType>>(theProfile);
			}

			template<class ProfileType>
			auto get_deck_profile(const std::shared_ptr<ProfileType>& theProfile)
			{
				auto p = std::dynamic_pointer_cast<DeckProfile<ProfileType>>(theProfile);
				return std::move(p);
			}
		}
	}
}

#endif // !_Model_VesselProfile_Deck_Header
