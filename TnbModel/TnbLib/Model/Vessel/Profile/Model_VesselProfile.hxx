#pragma once
#ifndef _Model_VesselProfile_Header
#define _Model_VesselProfile_Header

#include <memory>
#include <vector>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace modelLib
	{

		template<class ProfileType>
		class VesselProfile
			: public ProfileType
		{

			/*Private Data*/

		protected:

			// constructors [1/18/2023 Payvand]

			template<class... _Types>
			VesselProfile(_Types&&... _Args)
				: ProfileType(_Args...)
			{}

		public:

			// Public functions and operators [1/18/2023 Payvand]

			virtual Standard_Boolean IsDeck() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsKeel() const
			{
				return Standard_False;
			}
		};

		template<class ProfileType>
		Standard_Boolean is_vessel_profile(const std::shared_ptr<ProfileType>& theProfile)
		{
			return (Standard_Boolean)std::dynamic_pointer_cast<VesselProfile<ProfileType>>(theProfile);
		}

		template<class ProfileType>
		auto get_vessel_profile(const std::shared_ptr<ProfileType>& theProfile)
		{
			auto p = std::dynamic_pointer_cast<VesselProfile<ProfileType>>(theProfile);
			return std::move(p);
		}
	}
}

#endif // !_Model_VesselProfile_Header
