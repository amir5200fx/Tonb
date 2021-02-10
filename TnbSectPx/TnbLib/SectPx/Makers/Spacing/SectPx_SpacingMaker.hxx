#pragma once
#ifndef _SectPx_SpacingMaker_Header
#define _SectPx_SpacingMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Spacing;
	class SectPx_Limits;
	class SectPx_ShapeRegistry;

	namespace maker
	{

		class Spacing
			: public SectPx_Maker<SectPx_ShapeRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_ShapeRegistry>>(*this);
			}


			Spacing()
			{}

		public:

			explicit Spacing
			(
				const std::shared_ptr<SectPx_ShapeRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_ShapeRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_Spacing>
				SelectSpacing
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateUniform
				(
					const std::shared_ptr<SectPx_Limits>& theLimits,
					const Standard_Integer n
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Spacing>
				RemoveSpacing
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Spacing);

#endif // !_SectPx_SpacingMaker_Header
