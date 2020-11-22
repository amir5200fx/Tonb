#pragma once
#ifndef _SectPx_Pole_Slider_Header
#define _SectPx_Pole_Slider_Header

#include <SectPx_InterPole.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		// Forward Declarations
		class Pnt_GeoField;

		class Pole_Slider
			: public SectPx_InterPole
		{

			/*Private Data*/

			std::shared_ptr<Pnt_GeoField> thePnt_;


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			Pole_Slider()
			{}

			Pole_Slider(const std::shared_ptr<Pnt_GeoField>& thePnt)
				: thePnt_(thePnt)
			{}

			TnbSectPx_EXPORT Pole_Slider
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pnt_GeoField>& thePnt
			);

			TnbSectPx_EXPORT Pole_Slider
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pnt_GeoField>& thePnt
			);


			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			Standard_Boolean IsSlider() const override
			{
				return Standard_True;
			}

			SectPx_PoleType Type() const override
			{
				return SectPx_PoleType::slider;
			}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Pnt>
				Pnt() const override;

			void SetPnt
			(
				const std::shared_ptr<Pnt_GeoField>& thePnt
			)
			{
				thePnt_ = thePnt;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::Pole_Slider);

#endif // !_SectPx_Pole_Slider_Header