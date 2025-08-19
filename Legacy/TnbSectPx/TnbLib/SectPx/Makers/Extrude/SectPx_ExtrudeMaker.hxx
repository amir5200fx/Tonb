#pragma once
#ifndef _SectPx_ExtrudeMaker_Header
#define _SectPx_ExtrudeMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_ExtrProfile;
	class SectPx_ShapeRegistry;

	namespace maker
	{

		class Extrude
			: public SectPx_Maker<SectPx_ShapeRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_ShapeRegistry>>(*this);
			}


			Extrude()
			{}

		public:

			explicit Extrude
			(
				const std::shared_ptr<SectPx_ShapeRegistry>& theRegistry
			)
				: SectPx_Maker<SectPx_ShapeRegistry>(theRegistry)
			{}


			TnbSectPx_EXPORT std::shared_ptr<SectPx_ExtrProfile>
				SelectProfile
				(
					const Standard_Integer theIndex
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateUniform
				(
					const std::shared_ptr<SectPx_Par>& theX0,
					const std::shared_ptr<SectPx_Par>& theX1,
					const std::shared_ptr<SectPx_Par>& theValue
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateLinear
				(
					const std::shared_ptr<SectPx_Par>& theX0,
					const std::shared_ptr<SectPx_Par>& theX1,
					const std::shared_ptr<SectPx_Par>& theValue0,
					const std::shared_ptr<SectPx_Par>& theValue1
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateThreePoint
				(
					const std::shared_ptr<SectPx_Par>& theX0,
					const std::shared_ptr<SectPx_Par>& theX1,
					const std::shared_ptr<SectPx_Par>& theX2,
					const std::shared_ptr<SectPx_Par>& theValue0,
					const std::shared_ptr<SectPx_Par>& theValue1,
					const std::shared_ptr<SectPx_Par>& theValue2
				) const;

			TnbSectPx_EXPORT Standard_Integer
				CreateFivePoint
				(
					const std::shared_ptr<SectPx_Par>& theX0,
					const std::shared_ptr<SectPx_Par>& theX1,
					const std::shared_ptr<SectPx_Par>& theX2,
					const std::shared_ptr<SectPx_Par>& theX3,
					const std::shared_ptr<SectPx_Par>& theX4,
					const std::shared_ptr<SectPx_Par>& theValue0,
					const std::shared_ptr<SectPx_Par>& theValue1,
					const std::shared_ptr<SectPx_Par>& theValue2,
					const std::shared_ptr<SectPx_Par>& theValue3,
					const std::shared_ptr<SectPx_Par>& theValue4
				) const;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_ExtrProfile>
				RemoveProfile
				(
					const Standard_Integer theIndex
				) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Extrude);

#endif // !_SectPx_ExtrudeMaker_Header
