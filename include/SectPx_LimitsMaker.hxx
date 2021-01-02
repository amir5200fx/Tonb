#pragma once
#ifndef _SectPx_LimitsMaker_Header
#define _SectPx_LimitsMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Limits;
	class SectPx_FrameRegistry;

	namespace maker
	{

		class Limits
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}


			Limits()
			{}

		public:

			explicit Limits
			(
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Limits>
				SelectLimits
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateLimits
				(
					const std::shared_ptr<SectPx_Par>& theP0, 
					const std::shared_ptr<SectPx_Par>& theP1
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Limits> 
				RemoveLimits
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Limits);

#endif // !_SectPx_LimitsMaker_Header
