#pragma once
#ifndef _SectPx_WeightController_Header
#define _SectPx_WeightController_Header

#include <SectPx_PoleController.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;

	namespace sectPxLib
	{

		// Forward Declarations
		class Pole_Corner;

		class WeightController
			: public SectPx_PoleController
		{

			/*Private Data*/


			std::weak_ptr<SectPx_Par> theWeight_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbSectPx_EXPORT);


			WeightController()
			{}

		public:

			static TnbSectPx_EXPORT const char* typeName_;


			TnbSectPx_EXPORT WeightController
			(
				const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
			);

			TnbSectPx_EXPORT WeightController
			(
				std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
			);

			TnbSectPx_EXPORT WeightController
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
			);

			TnbSectPx_EXPORT WeightController
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
			);


			const auto& Weight() const
			{
				return theWeight_;
			}

			TnbSectPx_EXPORT void SetWeight
			(
				const std::shared_ptr<SectPx_Par>& theWeight
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean
				HasChild
				(
					const std::shared_ptr<SectPx_Child>& thePar
				) const override;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> 
				RetrieveChildren() const override;

			TnbSectPx_EXPORT sectPxLib::poleControllerType PoleType() const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::WeightController);

#endif // !_SectPx_WeightController_Header
