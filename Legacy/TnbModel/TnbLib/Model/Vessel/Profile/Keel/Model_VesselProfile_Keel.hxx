#pragma once
#ifndef _Model_VesselProfile_Keel_Header
#define _Model_VesselProfile_Keel_Header

#include <Model_VesselProfile.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		namespace vesselLib
		{

			template<class ProfileType>
			class KeelProfile
				: public VesselProfile<ProfileType>
			{

				/*Private Data*/

			public:

				// constructors [1/18/2023 Payvand]

				template<class... _Types>
				KeelProfile(_Types&&... _Args)
					: VesselProfile<ProfileType>(_Args...)
				{}


				// Public functions and operators [1/18/2023 Payvand]

				Standard_Boolean IsKeel() const override
				{
					return Standard_True;
				}

			};

			template<class ProfileType>
			Standard_Boolean is_keel_profile(const std::shared_ptr<ProfileType>& theProfile)
			{
				return (Standard_Boolean)std::dynamic_pointer_cast<KeelProfile<ProfileType>>(theProfile);
			}

			template<class ProfileType>
			auto get_keel_profile(const std::shared_ptr<ProfileType>& theProfile)
			{
				auto p = std::dynamic_pointer_cast<KeelProfile<ProfileType>>(theProfile);
				return std::move(p);
			}
		}
	}
}

#endif // !_Model_VesselProfile_Keel_Header
