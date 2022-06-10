#pragma once
#ifndef _SectPx_TightController_Deg2_Header
#define _SectPx_TightController_Deg2_Header

#include <SectPx_TightController.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class TightController_Deg2
			: public SectPx_TightController
		{

			/*Private Data*/

			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_TightController>(*this);
			}

		public:

			static TnbSectPx_EXPORT const short degree_;
			static TnbSectPx_EXPORT const char* typeName_;


			//- default constructor
			TightController_Deg2()
			{}

			//- constructors

			TnbSectPx_EXPORT TightController_Deg2
			(
				const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
			);

			TnbSectPx_EXPORT TightController_Deg2
			(
				std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
			);

		 	TnbSectPx_EXPORT TightController_Deg2
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
			);

			TnbSectPx_EXPORT TightController_Deg2
			(
				const Standard_Integer theIndex,
				std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
			);

			TnbSectPx_EXPORT TightController_Deg2
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
			);

			TnbSectPx_EXPORT TightController_Deg2
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
			);


			//- functions and operators

			TnbSectPx_EXPORT short Degree() const override;

			TnbSectPx_EXPORT void SetLeft
			(
				const std::shared_ptr<SectPx_SegmentController>& theController
			);

			TnbSectPx_EXPORT void SetRight
			(
				const std::shared_ptr<SectPx_SegmentController>& theController
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::TightController_Deg2);

#endif // !_SectPx_TightController_Deg2_Header
