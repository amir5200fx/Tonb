#pragma once
#ifndef _SectPx_CmptProfileMaker_Header
#define _SectPx_CmptProfileMaker_Header

#include <SectPx_Maker.hxx>
#include <Geo_ItemCounter.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_CmptProfile;
	class SectPx_Pnt;
	class SectPx_Cloud;
	class SectPx_FrameRegistry;

	namespace maker
	{

		// Forward Declarations
		class Profile;

		class CmptProfile
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

		public:


		private:

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Profile>>
				theProfiles_;

			mutable Geo_ItemCounter theCounter_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

			auto& Counter() const
			{
				return theCounter_;
			}

			void AddProfile
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Profile>&& theProfile
			);

		protected:

			CmptProfile()
			{}

		public:

			CmptProfile
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}

			auto NbProfiles() const
			{
				return (Standard_Integer)theProfiles_.size();
			}

			const auto& Profiles() const
			{
				return theProfiles_;
			}


			TnbSectPx_EXPORT std::shared_ptr<Profile>
				SelectProfile
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateCustomProfile
				(
					const std::shared_ptr<SectPx_Pnt>& theP0,
					const std::shared_ptr<SectPx_Pnt>& theP1
				);

			TnbSectPx_EXPORT Standard_Integer
				CreateExtruderCustomProfile
				(
					const std::shared_ptr<SectPx_Pnt>& theP0,
					const std::shared_ptr<SectPx_Pnt>& theP1
				);

			TnbSectPx_EXPORT Standard_Integer
				CreateInterplProfile
				(
					const std::shared_ptr<SectPx_Cloud>& theCloud
				);

			void RemoveProfile(const Standard_Integer theIndex);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::CmptProfile);

#endif // !_SectPx_CmptProfileMaker_Header
