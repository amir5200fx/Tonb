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

	namespace maker
	{

		// Forward Declarations
		class Profile;

		class CmptProfile
			: public SectPx_Maker
		{

		public:


		private:

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Profile>>
				theProfiles_;

			mutable Geo_ItemCounter theCounter_;


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

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
				const std::shared_ptr<SectPx_Registry>& theRegistry
			)
				: SectPx_Maker(theRegistry)
			{}

			auto NbProfiles() const
			{
				return (Standard_Integer)theProfiles_.size();
			}

			const auto& Profiles() const
			{
				return theProfiles_;
			}


			std::shared_ptr<Profile>
				SelectProfile
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateCustomProfile
				(
					const std::shared_ptr<SectPx_Pnt>& theP0,
					const std::shared_ptr<SectPx_Pnt>& theP1
				);

			Standard_Integer 
				CreateInterplProfile
				(
					const std::shared_ptr<SectPx_Cloud>& theCloud
				);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::CmptProfile);

#endif // !_SectPx_CmptProfileMaker_Header
