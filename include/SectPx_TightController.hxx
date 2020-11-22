#pragma once
#ifndef _SectPx_TightController_Header
#define _SectPx_TightController_Header

#include <SectPx_PoleController.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_SegmentController;

	class SectPx_TightController
		: public SectPx_PoleController
	{

		/*Private Data*/

		std::shared_ptr<SectPx_SegmentController> theLeft_;
		std::shared_ptr<SectPx_SegmentController> theRight_;


		//- friend functions and operators

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:


		template<class... _Types>
		SectPx_TightController(_Types&&... _Args)
			: SectPx_PoleController(_Args...)
		{}


		void SetLeft
		(
			const std::shared_ptr<SectPx_SegmentController>& theController
		)
		{
			theLeft_ = theController;
		}

		void SetRight
		(
			const std::shared_ptr<SectPx_SegmentController>& theController
		)
		{
			theRight_ = theController;
		}

	public:

		const auto& LeftController() const
		{
			return theLeft_;
		}

		const auto& RightController() const
		{
			return theRight_;
		}

		virtual short Degree() const = 0;

		TnbSectPx_EXPORT Standard_Integer NbChildMaps() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildMap() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT std::shared_ptr<SectPx_Parent> 
			ChildMap
			(
				const Standard_Integer theIndex
			) const override;

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_TightController);

#endif // !_SectPx_TightController_Header
