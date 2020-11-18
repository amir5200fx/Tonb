#pragma once
#ifndef _SectPx_PoleController_Header
#define _SectPx_PoleController_Header

#include <SectPx_Controller.hxx>
#include <SectPx_PoleControllerType.hxx>
#include <SectPx_PolesFwd.hxx>

namespace tnbLib
{

	class SectPx_PoleController
		: public SectPx_Controller
	{


		/*Private Data*/

		std::shared_ptr<sectPxLib::Pole_Corner> theCorner_;


		//- private functions and operators

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		SectPx_PoleController()
		{}

		TnbSectPx_EXPORT SectPx_PoleController
		(
			const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
		);

		TnbSectPx_EXPORT SectPx_PoleController
		(
			std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
		);

		TnbSectPx_EXPORT SectPx_PoleController
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
		);

		TnbSectPx_EXPORT SectPx_PoleController
		(
			const Standard_Integer theIndex,
			std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
		);

		TnbSectPx_EXPORT SectPx_PoleController
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<sectPxLib::Pole_Corner>& theCorner
		);

		TnbSectPx_EXPORT SectPx_PoleController
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<sectPxLib::Pole_Corner>&& theCorner
		);

	public:

		const auto& Corner() const
		{
			return theCorner_;
		}

		TnbSectPx_EXPORT Standard_Boolean IsOnPole() const override;

		virtual sectPxLib::poleControllerType PoleType() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_PoleController);

#endif // !_SectPx_PoleController_Header
