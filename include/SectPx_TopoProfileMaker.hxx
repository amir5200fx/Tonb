#pragma once
#ifndef _SectPx_TopoProfileMaker_Header
#define _SectPx_TopoProfileMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;
	class SectPx_Pnt;
	class SectPx_Node;
	class SectPx_Cloud;
	class SectPx_FrameRegistry;

	namespace maker
	{

		class TopoProfile
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}

			TopoProfile()
			{}

		public:

			TopoProfile
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theReg
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theReg)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_TopoProfile>
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

			TnbSectPx_EXPORT std::shared_ptr<SectPx_TopoProfile>
				RemoveProfile
				(
					const Standard_Integer theIndex
				);

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_TopoProfile>>
				RetrieveProfiles() const;

			TnbSectPx_EXPORT void RetrieveProfilesTo
			(
				std::vector<std::shared_ptr<SectPx_TopoProfile>>& theProfiles
			) const;

			TnbSectPx_EXPORT void Print(OSstream& out) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::TopoProfile);

#endif // !_SectPx_TopoProfileMaker_Header
